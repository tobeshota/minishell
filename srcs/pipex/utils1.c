/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:14:49 by toshota           #+#    #+#             */
/*   Updated: 2023/12/05 17:34:30 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	put_error(char *err_msg)
{
	write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
}

void	put_error_w_cmd(char *cmd, char *error_msg)
{
	put_error("-minishell: ");
	put_error(cmd);
	put_error(": ");
	put_error(error_msg);
	put_error("\n");
}

void	put_error_w_cmd_filename(char *cmd, char *file,
		char *error_msg)
{
	g_global.error_num = 1;
	if (file == NULL)
		return put_error_w_cmd(cmd, error_msg);
	else
	{
		put_error("-minishell: ");
		put_error(cmd);
		put_error(": ");
		put_error(file);
		put_error(": ");
		put_error(error_msg);
		put_error("\n");
	}
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
