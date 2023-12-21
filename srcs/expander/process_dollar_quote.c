/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_dollar_quote.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjia <cjia@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:02:58 by yoshimurahi       #+#    #+#             */
/*   Updated: 2023/12/21 15:04:29 by cjia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "minishell.h"
#include "pipex.h"

int	char_to_tmp(char **tmp, char c)
{
	char	*tmp2;
	char	*tmp3;

	tmp2 = check_malloc(char_to_str(c));
	tmp3 = check_malloc(ft_strjoin(*tmp, tmp2));
	free(*tmp);
	*tmp = tmp3;
	free(tmp2);
	return (1);
}

int	str_to_tmp(char **tmp, char *str)
{
	char	*tmp2;
	char	*tmp3;

	tmp2 = check_malloc(ft_strdup(str));
	tmp3 = check_malloc(ft_strjoin(*tmp, tmp2));
	free(*tmp);
	*tmp = tmp3;
	free(tmp2);
	return (2);
}

void	handle_double_quotes(char **tmp, char *str, int *j, int *frags)
{
	if(((str[*j - 1] == ' ' &&  str[*j + 2] == '\0') || (str[*j - 1] == ' ' &&  str[*j + 2] == ' ')) && str[*j] == '"' && str[*j + 1] == '"')
		(*j) += str_to_tmp(tmp, "\"\"");
	else if (str[*j] == '"' && *frags == 0 && str[*j + 1] != '"')
	{
		if ((*j > 0 && str[*j - 1] == ' ') || first_quote(str, j, '"') || search_space_quote_decre(str, j, '"'))
			(*j) += char_to_tmp(tmp, str[(*j)]);
		else
			(*j) += 1;
		(*frags) = 1;
	}
	else if (str[*j] == '"' && *frags == 1 && str[*j + 1] != '"')
	{
		if (str[(*j) + 1] == ' ' || str[(*j) + 1] == '\0' || last_quote(str, j, '"') || search_space_quote_incre(str, j, '"'))
			(*j) += char_to_tmp(tmp, str[(*j)]);
		else
			(*j) += 1;
		(*frags) = 0;
	}
	else if (str[*j] == '"' && str[*j + 1] == '"')
	{
		if(str[*j - 1] == '\'')
			char_to_tmp(tmp, '\'');
		(*j) += 2;
	}
}

void	handle_single_quotes(char **tmp, char *str, int *j, int *frags)
{
	char	*tmp2;
	char	*tmp3;
	int 		i;
	int 		num;

	num = strlen_between_c(str + *j, '\'');
	i = (*j) + num + 1;
	if(((str[*j - 1] == ' ' &&  str[*j + 2] == '\0') || (str[*j - 1] == ' ' &&  str[*j + 2] == ' ')) && str[*j] == '\'' && str[*j + 1] == '\'')
		(*j) += str_to_tmp(tmp, "\"\"");
	else if (str[*j] == '\'' && *frags == 0 && str[*j + 1] != '\'')
	{
		tmp2 = check_malloc(ft_substr(str, *j + 1,
					num));
		tmp3 = tmp2;
		if ((*j > 0 && str[*j - 1] == ' ') || first_quote(str, j, '\'')
				|| search_space_quote_decre(str, j, '\''))
		{
			tmp3 = check_malloc(ft_strjoin("\'", tmp2));
			free(tmp2);
			tmp2 = tmp3;
		}
		if (str[(*j) + num + 2] == ' '
				|| str[num + 2] == '\0'
				|| last_quote(str, &i, '\'')
				|| search_space_quote_incre(str, j, '\''))
		{
			tmp2 = check_malloc(ft_strjoin(tmp3, "\'"));
			free(tmp3);
		}
		tmp3 = check_malloc(ft_strjoin(*tmp, tmp2));
		free(tmp2);
		if (*tmp)
			free(*tmp);
		*tmp = tmp3;
		(*j) = (*j) + num + 2;
	}
	else if (str[*j] == '\'' && str[*j + 1] == '\'')
	{
		if(str[*j - 1] == '\'')
			char_to_tmp(tmp, '\'');
		(*j) += 2;
	}
}

char	*process_dollar_quote(char *str, char **envp, t_tools *tools)
{
	int		j;
	int		frags;
	char	*tmp;

	j = 0;
	frags = 0;
	tmp = check_malloc(ft_strdup("\0"));
	while (str[j])
	{
		j += handle_digit_after_dollar(j, str);
		if (str[j] == '"')
			handle_double_quotes(&tmp, str, &j, &frags);
		else if (str[j] == '\'' && frags == 0)
			handle_single_quotes(&tmp, str, &j, &frags);
		else if (str[j] == '$' && str[j + 1] == '?')
			j += question_mark(&tmp, tools);
		else if (str[j] == '$' && str[j + 1] == '$')
			j += str_to_tmp(&tmp, "$$");
		else if (title(str, j) == true)
			j += loop_if_dollar_sign(envp, str, &tmp, j);
		else
			j += char_to_tmp(&tmp, str[j]);
	}
	if (ft_strchr(tmp, '\'') || ft_strchr(tmp, '\"'))
	{
		tmp = move_to_first(tmp, '"', '\'');
		tmp = move_to_last(tmp, '"', '\'');
		tmp = move_to_first(tmp, '\'', '"');
		tmp = move_to_last(tmp, '\'', '"');
	}
	return (tmp);
}
