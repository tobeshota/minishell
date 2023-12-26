/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_dollar_quote.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshimurahiro <yoshimurahiro@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:02:58 by yoshimurahi       #+#    #+#             */
/*   Updated: 2023/12/26 18:22:30 by yoshimurahi      ###   ########.fr       */
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

char	*move_to_first_and_last(char *tmp)
{
	if (ft_strchr(tmp, '\'') || ft_strchr(tmp, '\"'))
	{
		tmp = move_to_first(tmp, '"', '\'');
		tmp = move_to_last(tmp, '"', '\'');
		tmp = move_to_first(tmp, '\'', '"');
		tmp = move_to_last(tmp, '\'', '"');
	}
	return (tmp);
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
		else if (check_conditions(str, j) == true)
			j += loop_if_dollar_sign(envp, str, &tmp, j);
		else
			j += char_to_tmp(&tmp, str[j]);
	}
	tmp = move_to_first_and_last(tmp);
	return (tmp);
}
