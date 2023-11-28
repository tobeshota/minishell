/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_new_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:08:47 by toshota           #+#    #+#             */
/*   Updated: 2023/11/28 23:16:16 by toshota          ###   ########.fr       */
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

static bool	check_identifier(char *identifier)
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

static size_t	strlen_without_c(char *str, char c)
{
	int	i;
	int	len_without_c;

	i = 0;
	len_without_c = 0;
	while (str[i])
	{
		if (str[i] != c)
			len_without_c++;
		i++;
	}
	return (len_without_c);
}

static char	*omit_c(char *str, char c)
{
	char	*str_without_c;
	int		i;

	str_without_c = (char *)check_malloc(malloc(sizeof(char)
				* (strlen_without_c(str, c) + 1)));
	i = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			str_without_c[i] = str[i];
			i++;
		}
		else
			str++;
	}
	return (str_without_c);
}

void	add_new_value(char *added_value, t_env **env)
{
	int		max_order;
	char	*added_value_without_plus;

	if (check_identifier(added_value) == false)
		return ;
	added_value_without_plus = omit_c(added_value, '+');
	max_order = ft_nodesize(*env);
	*env = ft_nodelast(*env);
	ft_nodeadd_back(env, check_malloc(ft_nodenew(added_value_without_plus)));
	ft_nodenext(env);
	(*env)->order = max_order + 1;
	free(added_value_without_plus);
}
