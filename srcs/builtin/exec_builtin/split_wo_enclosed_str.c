/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_wo_enclosed_str.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 21:10:43 by toshota           #+#    #+#             */
/*   Updated: 2023/12/16 18:32:39 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static bool	are_there_any_str_to_be_stored_in_node_left(char *str)
{
	return (str[0] != '\0');
}

char	**split_wo_enclosed_str(char *str, char splitter)
{
	t_env	*node_cmd;
	char	**cmd;
	int		i;

	i = -1;
	node_cmd = NULL;
	if (ft_strchr(str, '\'') == NULL && ft_strchr(str, '\"') == NULL)
		return (check_malloc(ft_split(str, splitter)));
	while (str[++i])
	{
		if (str[i] == splitter)
		{
			split_str_according_to_splitter(&str, &node_cmd, i);
			i = -1;
		}
		else if (str[i] == '\'' || str[i] == '\"')
		{
			split_str_according_to_encloser(&str, &node_cmd, i);
			i = -1;
		}
	}
	if (are_there_any_str_to_be_stored_in_node_left(str))
		nodeadd_from_0_to_i(&node_cmd, str, i);
	cmd = node_to_array(node_cmd);
	return (ft_nodeclear(&node_cmd), cmd);
}
