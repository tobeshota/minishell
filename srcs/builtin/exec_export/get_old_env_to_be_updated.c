/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_old_env_to_be_updated.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:29:27 by toshota           #+#    #+#             */
/*   Updated: 2023/12/11 12:01:39 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static char	*get_added_identifier_for_old_env_to_be_updated(char *added)
{
	if (ft_strnstr(added, "+=", ft_strlen(added)))
		return (check_malloc \
		(ft_substr(added, 0, ft_strchr(added, '+') - added)));
	else
		return (check_malloc \
		(ft_substr(added, 0, ft_strchr(added, '=') - added)));
}

t_env	*get_old_env_to_be_updated(char *added, t_env *env)
{
	char	*added_identifier;
	char	*env_identifier;
	t_env	*old_env;

	added_identifier = get_added_identifier_for_old_env_to_be_updated(added);
	while (true)
	{
		env_identifier = (char *)check_malloc(malloc(sizeof(char)
					* (strlen_until_c(env->content, '=') + 1)));
		ft_strlcpy(env_identifier, env->content, \
		strlen_until_c(env->content, '=') + 1);
		if (is_match(added_identifier, env_identifier))
		{
			old_env = env;
			return (free(added_identifier), free(env_identifier),
				ft_nodefirst(&env), old_env);
		}
		if (env->next == NULL)
			break ;
		ft_nodenext(&env);
		free(env_identifier);
	}
	return (free(added_identifier), free(env_identifier), ft_nodefirst(&env),
		NULL);
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

char	*omit_c(char *str, char c)
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

char	*omit_str(char *str, char *omit)
{
	char	*tmp;
	char	*result;

	result = check_malloc(ft_strdup(str));
	while (*omit)
	{
		tmp = result;
		result = omit_c(result, *omit);
		free(tmp);
		omit++;
	}
	return (result);
}
