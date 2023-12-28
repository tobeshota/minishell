/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_new_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:08:47 by toshota           #+#    #+#             */
/*   Updated: 2023/12/28 16:19:57 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static bool	is_append_properly_written(char current_c, char next_c)
{
	if (current_c == '+')
	{
		if (next_c == '=')
			return (true);
		return (false);
	}
	return (false);
}

static void	put_identifier_error(char *identifier)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(identifier, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

bool	check_identifier(char *identifier, t_pipex *pipex)
{
	int	i;

	i = 0;
	if (ft_isalpha(identifier[i]) == false && identifier[i] != '_')
	{
		*pipex->error_num = 1;
		return (put_identifier_error(identifier), false);
	}
	while (identifier[i] && identifier[i] != '=')
	{
		if (ft_isalnum(identifier[i]) == false && identifier[i] != '_' && \
			!is_append_properly_written(identifier[i], identifier[i + 1]))
		{
			*pipex->error_num = 1;
			return (put_identifier_error(identifier), false);
		}
		i++;
	}
	return (true);
}

bool	add_new_value(char *added_value, t_env **env, t_pipex *pipex)
{
	char	*added_value_without_plus;

	if (check_identifier(added_value, pipex) == false)
		return (false);
	added_value_without_plus = omit_c(added_value, '+');
	*env = ft_nodelast(*env);
	ft_nodeadd_back(env, check_malloc(ft_nodenew(added_value_without_plus)));
	ft_nodenext(env);
	free(added_value_without_plus);
	return (true);
}
