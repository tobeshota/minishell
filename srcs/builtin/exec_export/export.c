/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:39:21 by toshota           #+#    #+#             */
/*   Updated: 2023/11/29 11:10:09 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	*omit_quotes(char *str)
{
	char	*str_without_quotes;
	char	*tmp;

	str_without_quotes = omit_c(str, '\'');
	tmp = str_without_quotes;
	str_without_quotes = omit_c(str_without_quotes, '\"');
	free(tmp);
	tmp = str_without_quotes;
	str_without_quotes = omit_c(str_without_quotes, '`');
	free(tmp);
	return (str_without_quotes);
}

int	exec_export(char **cmd, t_env **env, t_pipex *pipex)
{
	int		i;
	char	*added_without_quotes;

	i = 1;
	if (cmd[i])
	{
		while (cmd[i])
		{
			added_without_quotes = omit_quotes(cmd[i]);
			if (get_old_env_to_be_updated(added_without_quotes, *env) == NULL)
				add_new_value(added_without_quotes, env);
			else
				update_value(added_without_quotes, env);
			ft_nodefirst(env);
			free(added_without_quotes);
			i++;
		}
	}
	else
	{
		show_env(env, pipex);
	}
	return (ft_nodefirst(env), true);
}
