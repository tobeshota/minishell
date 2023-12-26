/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshimurahiro <yoshimurahiro@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 18:21:04 by yoshimurahi       #+#    #+#             */
/*   Updated: 2023/12/26 18:22:21 by yoshimurahi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "minishell.h"
#include "pipex.h"

void	add_double_auote_frag0(char *str, int *j, char **tmp, int *frags)
{
	if ((*j > 0 && str[*j - 1] == ' ') || str[(*j) + 1] == '\t'
		|| first_quote(str, j, '"')
		|| search_space_quote_decre(str, j, '"'))
		(*j) += char_to_tmp(tmp, str[(*j)]);
	else
		(*j) += 1;
	(*frags) = 1;
}

void	add_double_auote_frag1(char *str, int *j, char **tmp, int *frags)
{
	if (str[(*j) + 1] == ' ' || str[(*j) + 1] == '\t'
		|| str[(*j) + 1] == '\0' || last_quote(str, j, '"')
		|| search_space_quote_incre(str, j, '"'))
		(*j) += char_to_tmp(tmp, str[(*j)]);
	else
		(*j) += 1;
	(*frags) = 0;
}

char	*add_single_quote(char *str, int *j, int num, char **tmp)
{
	int		i;
	char	*tmp2;
	char	*tmp3;

	i = (*j) + num + 1;
	tmp2 = check_malloc(ft_substr(str, *j + 1, num));
	tmp3 = tmp2;
	if ((*j > 0 && str[*j - 1] == ' ') || str[(*j) + 1] == '\t'
		|| first_quote(str, j, '\'') || search_space_quote_decre(str, j, '\''))
	{
		tmp3 = check_malloc(ft_strjoin("\'", tmp2));
		free(tmp2);
		tmp2 = tmp3;
	}
	if (str[(*j) + num + 2] == ' ' || str[(*j) + num + 2] == '\t'
		|| str[num + 2] == '\0' || last_quote(str, &i, '\'')
		|| search_space_quote_incre(str, j, '\''))
	{
		tmp2 = check_malloc(ft_strjoin(tmp3, "\'"));
		free(tmp3);
	}
	tmp3 = check_malloc(ft_strjoin(*tmp, tmp2));
	if (*tmp)
		free(*tmp);
	return (free(tmp2), tmp3);
}

void	handle_double_quotes(char **tmp, char *str, int *j, int *frags)
{
	if (((str[*j - 1] == ' ' && str[*j + 2] == '\0')
			|| (str[*j - 1] == ' ' && str[*j + 2] == ' '))
		&& str[*j] == '"' && str[*j + 1] == '"')
		(*j) += str_to_tmp(tmp, "\"\"");
	else if (str[*j] == '"' && *frags == 0)
		add_double_auote_frag0(str, j, tmp, frags);
	else if (str[*j] == '"' && *frags == 1)
		add_double_auote_frag1(str, j, tmp, frags);
	else if (str[*j] == '"' && str[*j + 1] == '"')
	{
		if (str[*j - 1] == '\'')
			char_to_tmp(tmp, '\'');
		(*j) += 2;
	}
}

void	handle_single_quotes(char **tmp, char *str, int *j, int *frags)
{
	int		num;

	num = strlen_between_c(str + *j, '\'');
	if (((str[*j - 1] == ' ' && str[*j + 2] == '\0')
			|| (str[*j - 1] == ' ' && str[*j + 2] == ' '))
		&& str[*j] == '\'' && str[*j + 1] == '\'')
		(*j) += str_to_tmp(tmp, "\"\"");
	else if (str[*j] == '\'' && *frags == 0)
	{
		*tmp = add_single_quote(str, j, num, tmp);
		(*j) = (*j) + num + 2;
	}
	else if (str[*j] == '\'' && str[*j + 1] == '\'')
	{
		if (str[*j - 1] == '\'')
			char_to_tmp(tmp, '\'');
		(*j) += 2;
	}
}
