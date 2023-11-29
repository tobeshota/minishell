/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:36:07 by toshota           #+#    #+#             */
/*   Updated: 2023/11/29 11:36:05 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

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
		unseted_env->prev->next = unseted_env->next->prev;
		ft_nodedelone(&unseted_env);
		ft_nodefirst(env);
	}
	return (true);
}
