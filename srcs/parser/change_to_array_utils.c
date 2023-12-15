/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_to_array_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjia <cjia@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 11:16:27 by cjia              #+#    #+#             */
/*   Updated: 2023/12/15 11:32:26 by cjia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

char	*token_to_char(t_tokens token)
{
	if (token == PIPE)
		return ("|");
	else if (token == GREAT)
		return (">");
	else if (token == GREAT_GREAT)
		return (">>");
	else if (token == LESS)
		return ("<");
	else if (token == LESS_LESS)
		return ("<<");
	else if (token == SEMICOLON)
		return (";");
	else if (token == AND_AND)
		return ("&&");
	else if (token == OR_OR)
		return ("||");
	else
		return ("");
}

char	*process_str_concat(char *tmpstr, char *str)
{
	char	*result;

	result = check_malloc(ft_strjoin(tmpstr, str));
	return (result);
}

int	process_redirection_str(char **tmparray, t_simple_cmds *tmp, int i)
{
	int		k;
	char	*tmpstr;

	k = 0;
	tmpstr = NULL;
	if (tmp->str && tmp->str[k])
	{
		tmparray[i] = process_str_concat(tmpstr, tmp->str[k]);
		while (tmp->str[k + 1])
		{
			tmpstr = check_malloc(ft_strjoin(tmparray[i], " "));
			free(tmparray[i]);
			tmparray[i] = check_malloc(ft_strjoin(tmpstr, tmp->str[k + 1]));
			free(tmpstr);
			k++;
		}
		i++;
	}
	return (i);
}

int	process_redirections(char **tmparray, t_simple_cmds *tmp, int i)
{
	t_lexer	*tmp2;

	tmp2 = tmp->redirections;
	while (tmp2 && tmp2->token != PIPE && tmp2->token != AND_AND
		&& tmp2->token != OR_OR && tmp2->token != SEMICOLON)
	{
		tmparray[i++] = ft_strdup(token_to_char(tmp2->token));
		if (tmp2->str)
		{
			tmparray[i++] = ft_strdup(tmp2->str);
		}
		tmp2 = tmp2->next;
	}
	if (tmp2 && (tmp2->token == PIPE || tmp2->token == AND_AND
			|| tmp2->token == OR_OR || tmp2->token == SEMICOLON))
	{
		tmparray[i++] = ft_strdup(token_to_char(tmp2->token));
	}
	return (i);
}
