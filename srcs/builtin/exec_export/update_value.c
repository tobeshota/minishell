/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:30:49 by toshota           #+#    #+#             */
/*   Updated: 2023/11/28 23:39:29 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static char	*get_added_identifier_for_update_value(t_env *old_env, char *added)
{
	if (ft_strchr(old_env->content, '='))
		return (check_malloc \
		(ft_substr(added, 0, ft_strchr(added, '+') - added)));
	else
		return (check_malloc \
		(ft_substr(added, 0, ft_strchr(added, '+') - added - ft_strlen("="))));
}

void	update_value(char *added, t_env **env)
{
	t_env	*old_env;
	char	*added_identifier;
	char	*tmp;

	if (ft_strchr(added, '=') == NULL)
		return ;
	old_env = get_old_env_to_be_updated(added, *env);
	if (ft_strnstr(added, "+=", ft_strlen(added)))
	{
		added_identifier = \
		get_added_identifier_for_update_value(old_env, added);
		tmp = old_env->content;
		old_env->content = \
		check_malloc(ft_strjoin(old_env->content, added + \
		(ft_strlen(added_identifier) + ft_strlen("+="))));
		free(added_identifier);
	}
	else
	{
		tmp = old_env->content;
		old_env->content = check_malloc(ft_strdup(added));
	}
	free(tmp);
}
