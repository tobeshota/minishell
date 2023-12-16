/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_str_according_to_splitter.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 18:23:43 by toshota           #+#    #+#             */
/*   Updated: 2023/12/16 18:32:36 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/* nodeに空白までの文字列を格納する */
void	nodeadd_from_0_to_i(t_env **node_cmd, char *str, int i)
{
	t_env	*new;
	char	*content;
	char	*content_wo_quotas;

	content = check_malloc(ft_substr(str, 0, i));
	content_wo_quotas = omit_encloser_in_bos_and_eos(content);
	new = ft_nodenew(content_wo_quotas);
	free(content);
	free(content_wo_quotas);
	if (*node_cmd == NULL)
		*node_cmd = new;
	else
		ft_nodeadd_back(node_cmd, new);
}

void	split_str_according_to_splitter(char **str, t_env **node_cmd, int i)
{
	nodeadd_from_0_to_i(node_cmd, *str, i);
	*str += ft_strlen(ft_nodelast(*node_cmd)->content) + SPLITTER;
}
