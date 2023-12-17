/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshimurahiro <yoshimurahiro@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:39:54 by yoshimurahi       #+#    #+#             */
/*   Updated: 2023/12/18 01:55:58 by yoshimurahi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "minishell.h"
#include "pipex.h"

// 文字列中の囲い文字で囲われた文字列の文字数を取得する
int strlen_between_c(char *str, char c)
{
    char *str_after_1st_c;
    char *str_after_2nd_c;

    str_after_1st_c = ft_strchr(str, c) + 1;
    str_after_2nd_c = ft_strchr(str_after_1st_c, c);
    return str_after_2nd_c - str_after_1st_c;
}

size_t	strlen_until_c_expansion(char *str, char c)
{
	size_t	len;

	len = 1;
	while (str[len] != '\0')
	{
		if(str[len] != c)
			return (len);
		len++;
	}
	return (len);
}


int find_matching_quote_expansion(char *str, int j, char **tmp, char **envp)
{
	char *tmp2;
	char *tmp3;
	char *tmp4;
	char *tmp5;
	int 	num;
	int		num2;
	int		endpoint;
	int 	num_tmp = 0;
	
	tmp4 = NULL;
		num = 0;
	 	if(str[j] == '"')
		{
			endpoint = strlen_between_c(str + j, '"');
			tmp2 = check_malloc(ft_substr(str, j + 1, endpoint));
			num = loop_if_dollar_sign(envp, tmp2, &tmp4, 0);
			tmp4 = check_malloc(ft_strjoin("\"" , tmp4));
			tmp4 = check_malloc(ft_strjoin(tmp4, "\""));
			tmp3 = check_malloc(ft_strjoin(*tmp, tmp4));
			free(*tmp);
			*tmp = tmp3;
			free(tmp2);
		}
		j += num;
	return (endpoint + 2);
}

char	*detect_dollar(char *str, char **envp, t_tools *tools)
{
	int		j;
	int 	endpoint;
	int 	num;
	int 	frags;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	char	*tmp4;

	j = 0;
	frags = 0;
	tmp = check_malloc(ft_strdup("\0"));
	while (str[j])
	{
		j += handle_digit_after_dollar(j, str);
		if(str[j] == '"')
		{
			if(frags == 0 && str[j + 1] != '"')
			{
				tmp2 = check_malloc(char_to_str(str[j++]));
				tmp3 = check_malloc(ft_strjoin(tmp, tmp2));
				free(tmp);
				tmp = tmp3;
				free(tmp2);
				frags = 1;
			}
			else if(frags == 1)
			{
				tmp2 = check_malloc(char_to_str(str[j++]));
				tmp3 = check_malloc(ft_strjoin(tmp, tmp2));
				free(tmp);
				tmp = tmp3;
				free(tmp2);
				frags = 0;
			}
			else
				j += 2;
		}
		else if(str[j] == '\'' && frags == 0)
		{
			if(str[j + 1] != '\'')
			{
				endpoint = strlen_between_c(str + j, '\'');
				tmp2 = check_malloc(ft_substr(str, j + 1, endpoint));
				tmp3 = check_malloc(ft_strjoin("\'", tmp2));
				free(tmp2);
				tmp2 = check_malloc(ft_strjoin(tmp3, "\'"));
				free(tmp3);
				tmp3 = check_malloc(ft_strjoin(tmp, tmp2));
				free(tmp2);
				if(tmp)
					free(tmp);
				tmp = tmp3;
				j =  j + endpoint + 2;
			}
			else
				j += 2;
		}
		else if (str[j] == '$' && str[j + 1] == '?')
			j += question_mark(&tmp, tools);
		else if (str[j] == '$' && str[j + 1] == '$')
		{
			tmp2 = check_malloc(ft_strdup("$$"));
			tmp3 = check_malloc(ft_strjoin(tmp, tmp2));
			free(tmp);
			tmp = tmp3;
			free(tmp2);
			j += 2;
		}
		else if (title(str, j) == true)
			j += loop_if_dollar_sign(envp, str, &tmp, j);
		else
		{
			tmp2 = check_malloc(char_to_str(str[j++]));
			tmp3 = check_malloc(ft_strjoin(tmp, tmp2));
			free(tmp);
			tmp = tmp3;
			free(tmp2);
		}
	}
	return (tmp);
}

void	ft_nodefirst_for_t_simple_cmds(t_simple_cmds **node)
{
	if (node == NULL || *node == NULL)
		return ;
	while ((*node)->prev != NULL)
		*node = (*node)->prev;
}

void	free_old_str(t_tools *tools)
{
	while (tools->simple_cmds->str)
	{
		all_free_tab(tools->simple_cmds->str);
		tools->simple_cmds->str = NULL;
		if (tools->simple_cmds->next == NULL)
			break ;
		tools->simple_cmds = tools->simple_cmds->next;
	}
	ft_nodefirst_for_t_simple_cmds(&tools->simple_cmds);
}

bool		check_case_herecoc(char **str, int i)
{
	char *tmp;

	if(str[i + 1] &&is_match(str[i], "<<") == true && str[i + 1] != (void *)'\0')
	{
		tmp = check_malloc(ft_strdup(str[i]));
		free(str[i]);
		str[i] = tmp;
		tmp = check_malloc(ft_strdup(str[i + 1]));
		free(str[i + 1]);
		str[i + 1] = tmp;
		return (true);
	}	
	return (false);
}

char	**expander(t_tools *tools, char **str, char **envp)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (str[i] != NULL)
	{

		if(check_case_herecoc(str, i) == true)
			i++;
		else if (str[i][find_dollar(str[i])] != '\0')
		{
			tmp = detect_dollar(str[i], envp, tools);
			free(str[i]);
			str[i] = tmp;
		}
		i++;
	}
	free_old_str(tools);
	return (str);
}
