/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:14:49 by toshota           #+#    #+#             */
/*   Updated: 2023/11/18 01:16:18 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	all_free_tab(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		ptr[i] = NULL;
		i++;
	}
	free(ptr);
	ptr = NULL;
}

void	put_error(char *err_msg)
{
	write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
}

char	*ft_strrnchr(const char *s, int c, int n)
{
	char	ch;
	size_t	i;
	int		count;

	ch = (char)c;
	i = ft_strlen(s);
	count = 0;
	while (i >= 0 && i > ft_strlen(s) - n)
	{
		if (s[i] == ch)
		{
			if (count == n)
				return ((char *)&s[i]);
			else
				count++;
		}
		i--;
	}
	return (0);
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
	int	cmd_count;
	int	arg_i;

	cmd_count = 0;
	arg_i = 0;
	while (argv[arg_i])
	{
		if (is_cmd(argv, arg_i))
			cmd_count++;
		arg_i++;
	}
	return (cmd_count);
}
