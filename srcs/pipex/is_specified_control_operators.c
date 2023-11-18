/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_specified_control_operators.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:14:49 by toshota           #+#    #+#             */
/*   Updated: 2023/11/18 16:16:31 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_specified_semicolon(char *str)
{
	return (ft_strlen(str) == ft_strlen(";") && (!ft_strncmp(str, ";",
				ft_strlen(str))));
}

int	is_specified_pipe(char *str)
{
	return (ft_strlen(str) == ft_strlen("|") && (!ft_strncmp(str, "|",
				ft_strlen(str))));
}

int	is_specified_pipe_pipe(char *str)
{
	return (ft_strlen(str) == ft_strlen("||") && (!ft_strncmp(str, "||",
				ft_strlen(str))));
}

int	is_specified_ampersant(char *str)
{
	return (ft_strlen(str) == ft_strlen("&") && (!ft_strncmp(str, "&",
				ft_strlen(str))));
}

int	is_specified_apersant_ampersant(char *str)
{
	return (ft_strlen(str) == ft_strlen("&&") && (!ft_strncmp(str, "&&",
				ft_strlen(str))));
}
