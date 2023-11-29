/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:36:07 by toshota           #+#    #+#             */
/*   Updated: 2023/11/29 13:32:20 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static bool is_node_last(t_env *node)
{
	return node->next == NULL;
}

static bool is_node_first(t_env *node)
{
	return node->prev == NULL;
}


/*
[]──[]──[]
*/
// 削除対象となるものを探し，あれば削除する．なければ正常終了する
int	exec_unset(char **cmd, t_env **env)
{
	int		i;
	t_env	*unseted_env;

	i = 0;
	while (cmd[++i])
	{
		if (check_identifier(cmd[i]) == false)
			continue ;
		unseted_env = get_old_env_to_be_updated(cmd[i], *env);
		if (unseted_env == false)
			continue ;
		/* どこのものを消すかによってパスの繋げ方を変える */
		// 最後の環境変数を削除する場合，削除する前のenvのnextをNULLにする
		if (is_node_last(unseted_env) == true)
			unseted_env->prev->next = NULL;
		// 最初の環境変数を削除する場合，削除する次のenvのprevをNULLにする
		if (is_node_first(unseted_env) == true)
			unseted_env->next->prev = NULL;
		// 途中の環境変数を削除する場合，削除する前のenvのnextを削除する次のenvのprevにする
		else
		{
			unseted_env->prev->next = unseted_env->next;
			unseted_env->next->prev = unseted_env->prev;
		}
		ft_nodedelone(&unseted_env);
		ft_nodefirst(env);
	}
	return (true);
}
