/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjia <cjia@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:12:33 by yoshimurahi       #+#    #+#             */
/*   Updated: 2023/12/08 13:11:43 by cjia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_token(char *str, int i, t_lexer **lexer_list)
{
	int	token_type;

	token_type = get_token_type(str, i);
	if (token_type == NONE)
		return (0);
	if (token_type == GREAT_GREAT || token_type == LESS_LESS
		|| token_type == AND_AND || token_type == OR_OR)
	{
		if (!add_node(NULL, token_type, lexer_list))
			return (-1);
		return (2);
	}
	else
	{
		if (!add_node(NULL, token_type, lexer_list))
			return (-1);
		return (1);
	}
}

int	check_token(char *str, int i)
{
	int	token_type;

	token_type = get_token_type(str, i);
	if (token_type == NONE)
		return (0);
	if (token_type == GREAT_GREAT || token_type == LESS_LESS
		|| token_type == AND_AND || token_type == OR_OR)
	{
		return (2);
	}
	else
	{
		return (1);
	}
}
