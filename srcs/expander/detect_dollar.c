/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjia <cjia@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:02:58 by yoshimurahi       #+#    #+#             */
/*   Updated: 2023/12/20 15:42:34 by cjia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "minishell.h"
#include "pipex.h"


// 文字列中のi番目の文字を付け加える
char    *add_ith_c(char *str, char add, int ith)
{
    char    add_str[2];
    char    *before;
    char    *before_w_add;
    char    *after;
    char    *ret;

    add_str[0] = add;
    add_str[1] = '\0';
    before = check_malloc(ft_substr(str, 0, ith));
    after = check_malloc(ft_substr(str, ith, ft_strlen(str)));
    before_w_add = check_malloc(ft_strjoin(before, add_str));
    ret = check_malloc(ft_strjoin(before_w_add, after));
    return (free(before), free(after), free(before_w_add), ret);
}



// 文字列中のi番目の文字を消す
char    *omit_ith_c(char *str, int ith)
{
    char    *before;
    char    *after;
    char    *ret;

    before = check_malloc(ft_substr(str, 0, ith));
    after = check_malloc(ft_substr(str, ith + 1, ft_strlen(str)));
    ret = check_malloc(ft_strjoin(before, after));
    return (free(before), free(after), ret);
}



char *move_to_first(char *str, char c)
//クオートを空白かstr「０」の後ろに移動させる
{
	int		i;
	int		frags;
	char	*tmp;
	char	*tmp2;

	i = 0;
	frags = 0;

	tmp2 = NULL;
	i = ft_strlen(str) - 1;
	while(str[i] != '\0' && i >= 0)
	{
		if (str[i] == c && frags == 0  && i > 0)
			frags = 1;
		else if(str[i] == c && frags == 1 && i > 0)
		{
			tmp = omit_ith_c(str, i);
			i--;
			while(str[i])//str[0]はまだ考えていない
			{
				if(i >= 0 && str[i - 1] == ' ')
				{
					tmp2 =  add_ith_c(tmp, '"', i);
					i--;
					free(tmp);
					free(str);
					str = tmp2;
					break;
				}
				i--;
			}
			frags = 0;
		}
		i--;
	}

	if(tmp2 == NULL)
		return (str);
	free(str);
	str = ft_strdup(tmp2);
	return (str);
}



char *move_to_last(char *str, char c)
//クオートを空白かNULLの前に移動させる
{
	int		i;
	int		frags;
	char	*tmp;
	char	*tmp2;

	i = 0;
	frags = 0;
	tmp2 = NULL;
	while(str && str[i] != '\0')
	{
		if (str[i] == c && frags == 0)
			frags = 1;
		else if (str[i] == c && frags == 1)
		{
			tmp = omit_ith_c(str, i);
			i++;
			while(str[i])
			{
				if(str[i] == ' ' || i >= 0)
				{
					tmp2 =  add_ith_c(tmp, '"', i);
					i++;
					free(tmp);
					free(str);
					str = tmp2;
					break;
				}
				i++;
			}
			frags = 0;
		}
		i++;
	}
	if(tmp2 == NULL)
		return (str);
	free(str);
	str = ft_strdup(tmp2);
	return (str);
}



bool  	search_space_quote_incre(char *str, int *i, char c)//後ろに空白があるかつもっと前にクオートがあるか（この時、先にクオートが来てはならない）、または前から見て最初のクオートか、。
{
  int		j;
  int 		frag;

  j = *i + 1;
  while(str[j])
  {
	if(str[j] && str[j] == '"')
		return (false);
	if (str[j] && str[j] == ' ')
	{
		frag = 1;
		while (str[j])
		{
			if (str[j] == c)
				return (true);
			j++;
		}
	}
	j++;
  }
  if(frag == 0)
	  return (true);
	return (false);
}



bool  	search_space_quote_decre(char *str, int *i, char c)//前に空白があるかつもっと前にクオートがあるか（この時、先にクオートが来てはならない）、または前から見て最初のクオートか、。
{
	int		j;
	int 		frag;

	j = *i - 1;
	frag = 0;
	while(str[j] && str[j] != str[0])
	{
		if(str[j] && str[j] == '"')
			return (false);
		if (str[j] && str[j] == ' ' && frag == 0)
		{
			frag = 1;
			while (str[j] && j != 0)
			{
				if (str[j] == c)
					return (true);
				j--;
			}
		}
		j--;
	}
	if(frag == 0)
		return (true);
	return (false);
}


bool 	first_quote(char *str, int *i)
{
	int		j;
	int	 	num;

	j = *i;
	num = 0;
	while (str[num])
	{
		if (str[num] == '"')
		{
			if(num == j)
				return (true);
			else
				return (false);
		}
		num++;
	}
	return (false);
}

bool	last_quote(char *str, int *i)
{
	int		j;
	int	 	num;

	j = *i;
	num = 0;
	num = ft_strlen(str) - 1;
	while (str[num] && num != 0)
	{
		if (str[num] == '"')
		{
			if(num == j)
				return (true);
			else
				return (false);
		}
		num--;
	}
	return (false);
}





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
	if (str[*j] == '"' && *frags == 0 && str[*j + 1] != '"')
	{
		if ((*j > 0 && str[*j - 1] == ' ') || first_quote(str, j) || search_space_quote_decre(str, j, '"'))//出現条件→前に空白がある、またはstr「０」、または（前に空白があるかつもっと前にクオートがあるか（この時、先にクオートが来てはならない）、または前から見て最初のクオートか、。フラグ０なので、前のクオートはフラグ１だった）
			(*j) += char_to_tmp(tmp, str[(*j)]);
		else
			(*j) += 1;
		(*frags) = 1;
	}
	else if (str[*j] == '"' && *frags == 1 && str[*j + 1] != '"')
	{
		if (str[(*j) + 1] == ' ' || str[(*j) + 1] == '\0' || last_quote(str, j) || search_space_quote_incre(str, j, '"'))//追加で、文字ある場合、後に空白があり、かつ空白の後にクオートがある時にこのクオートを出現させるこの時、先にクオートが来たら弾く。もうひとつ。クオートの後の文字がある時、その後がクオートなしかつ終端文字なら出現させる
			(*j) += char_to_tmp(tmp, str[(*j)]);
		else
			(*j) += 1;
		(*frags) = 0;
	}
	else if (str[*j] == '"' && str[*j + 1] == '"')
		(*j) += 2;
}

void	handle_single_quotes(char **tmp, char *str, int *j, int *frags)
{
	char	*tmp2;
	char	*tmp3;

	if (str[*j] == '\'' && *frags == 0 && str[*j + 1] != '\'')
	{
		tmp2 = check_malloc(ft_substr(str, *j + 1,
					strlen_between_c(str + *j, '\'')));
		tmp3 = check_malloc(ft_strjoin("\'", tmp2));
		free(tmp2);
		tmp2 = check_malloc(ft_strjoin(tmp3, "\'"));
		free(tmp3);
		tmp3 = check_malloc(ft_strjoin(*tmp, tmp2));
		free(tmp2);
		if (*tmp)
			free(*tmp);
		*tmp = tmp3;
		(*j) = (*j) + strlen_between_c(str + *j, '\'') + 2;
	}
	else if (str[*j] == '\'' && str[*j + 1] == '\'')
		(*j) += 2;
}

char	*detect_dollar(char *str, char **envp, t_tools *tools)
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

	if (ft_strchr(tmp, '\'') || ft_strchr(tmp, '\"') )//""の中に
	{
		tmp = move_to_first(tmp, '"');
		tmp = move_to_last(tmp, '"');
	}
	return (tmp);
}
