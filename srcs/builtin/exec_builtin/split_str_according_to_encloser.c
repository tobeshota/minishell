/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_str_according_to_encloser.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 18:28:39 by toshota           #+#    #+#             */
/*   Updated: 2023/12/16 18:33:10 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static bool	does_encloser_exist(char *str)
{
	return (ft_strchr(str, '\'') || ft_strchr(str, '\"'));
}

char	*omit_encloser_in_bos_and_eos(char *str)
{
	char	*result;
	char	encloser;

	result = (char *)check_malloc(malloc(sizeof(char) * (ft_strlen(str) + 1)));
	if (does_encloser_exist(str) == false)
	{
		ft_strlcpy(result, str, (ft_strlen(str) + 1));
	}
	else
	{
		encloser = str[ft_strlen(str) - 1];
		ft_strlcpy(result, str, (ft_strchr(str, encloser) - str) + 1);
		ft_strlcpy(result + ft_strlen(result), \
		ft_strchr(str, encloser) + BEGINNING_OF_ENCLOSER, \
		ft_strlen(ft_strchr(str, encloser)) - END_OF_ENCLOSER);
	}
	return (result);
}

/* nodeに今指しているポインタから次の囲い文字までの文字列を格納する */
static void	nodeadd_upto_next_encloser(t_env **node_cmd, char *str,
		char encloser)
{
	t_env	*new;
	int		len_upto_next_encloser;
	char	*content;
	char	*content_wo_quotas;

	len_upto_next_encloser = \
		ft_strchr(ft_strchr(str, encloser) + ENCLOSER, encloser) - str;
	content = check_malloc(ft_substr(str, 0, len_upto_next_encloser
				+ ENCLOSER));
	content_wo_quotas = omit_encloser_in_bos_and_eos(content);
	new = ft_nodenew(content_wo_quotas);
	free(content);
	free(content_wo_quotas);
	if (*node_cmd == NULL)
		*node_cmd = new;
	else
		ft_nodeadd_back(node_cmd, new);
}

void	split_str_according_to_encloser(char **str, t_env **node_cmd, int i)
{
	char	encloser;

	encloser = str[0][i];
	nodeadd_upto_next_encloser(node_cmd, *str, encloser);
	*str += ft_strlen(ft_nodelast(*node_cmd)->content) + BEGINNING_OF_ENCLOSER
		+ END_OF_ENCLOSER;
	while (**str && **str == ' ')
		(*str)++;
}
