/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard_utils3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobeshota <tobeshota@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 00:00:00 by toshota           #+#    #+#             */
/*   Updated: 2026/02/28 17:34:44 by tobeshota        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

bool	del_node(t_env **expanded)
{
	t_env	*next;

	if (is_node_only_one(*expanded) == true)
		return (ft_nodedelone(expanded), false);
	else if (is_node_last(*expanded) == true)
		return (unset_last_node(expanded), true);
	else if (is_node_first(*expanded) == true)
		return (unset_first_node(expanded, NULL), true);
	next = (*expanded)->next;
	unset_middle_node(*expanded);
	*expanded = next;
	return (true);
}
