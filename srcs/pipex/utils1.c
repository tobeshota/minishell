/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:14:49 by toshota           #+#    #+#             */
/*   Updated: 2023/12/03 00:24:58 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	put_error(char *err_msg)
{
	write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
}

size_t	strlen_until_c(char *str, char c)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0' && str[len] != c)
		len++;
	return (len);
}

int	get_cmd_count(char **argv)
{
	int		cmd_count;
	int		arg_i;
	int		ret;
	char	*argv_wo_param;

	cmd_count = 0;
	arg_i = 0;
	while (argv[arg_i])
	{
		argv_wo_param = check_malloc \
		(ft_substr(argv[arg_i], 0, strlen_until_c(argv[arg_i], ' ')));
		ret = is_cmd(argv, arg_i);
		if (ret == true)
			cmd_count++;
		else if (ret == NOT_FOUND)
		{
			put_error("-minishell: ");
			put_error(argv_wo_param);
			put_error(": command not found\n");
		}
		arg_i++;
		free(argv_wo_param);
	}
	return (cmd_count);
}

size_t	get_larger(size_t n1, size_t n2)
{
	if (n1 > n2)
		return (n1);
	return (n2);
}

void	get_order(t_env *node)
{
	t_env	*test;

	test = node;
	while (node)
	{
		node->order = 1;
		while (test->next)
		{
			if (ft_strncmp(node->content, test->content,
					get_larger(ft_strlen(node->content),
						ft_strlen(test->content))) > 0)
				node->order++;
			ft_nodenext(&test);
		}
		if (ft_strncmp(node->content, test->content,
				get_larger(ft_strlen(node->content),
					ft_strlen(test->content))) > 0)
			node->order++;
		node = node->next;
		ft_nodefirst(&test);
	}
}
