/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_new_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:08:47 by toshota           #+#    #+#             */
/*   Updated: 2023/12/11 12:01:35 by toshota          ###   ########.fr       */
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
	return (true);
}

bool	check_identifier(char *identifier)
{
	int	i;

	i = 0;
	if (ft_isalpha(identifier[i]) == false && identifier[i] != '_')
	{
		ft_putstr_fd("bash: export: '", STDERR_FILENO);
		ft_putstr_fd(identifier, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		return (false);
	}
	while (identifier[i])
	{
		if (ft_isalnum(identifier[i]) == false && identifier[i] != '_'
			&& is_append_properly_written \
			(identifier[i], identifier[i + 1]) == false)
		{
			ft_putstr_fd("bash: export: '", STDERR_FILENO);
			ft_putstr_fd(identifier, STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			return (false);
		}
		i++;
	}
	return (true);
}

void	add_new_value(char *added_value, t_env **env)
{
	char	*added_value_without_plus;

	if (check_identifier(added_value) == false)
		return ;
	added_value_without_plus = omit_c(added_value, '+');
	*env = ft_nodelast(*env);
	ft_nodeadd_back(env, check_malloc(ft_nodenew(added_value_without_plus)));
	ft_nodenext(env);
	free(added_value_without_plus);
}
