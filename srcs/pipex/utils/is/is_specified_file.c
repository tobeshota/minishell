/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_specified_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshimurahiro <yoshimurahiro@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:31:16 by toshota           #+#    #+#             */
/*   Updated: 2023/11/30 15:41:12 by yoshimurahi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	is_specified_infile(char *str)
{
	return (ft_strlen(str) == ft_strlen("<") && (!ft_strncmp(str, "<",
				ft_strlen(str))));
}

bool	is_specified_here_doc(char *str)
{
	return (ft_strlen(str) == ft_strlen("<<") && (!ft_strncmp(str, "<<",
				ft_strlen(str))));
}

bool	is_specified_outfile_overwriting(char *str)
{
	return (ft_strlen(str) == ft_strlen(">") && (!ft_strncmp(str, ">",
				ft_strlen(str))));
}

bool	is_specified_outfile_apend(char *str)
{
	return (ft_strlen(str) == ft_strlen(">>") && (!ft_strncmp(str, ">>",
				ft_strlen(str))));
}

bool	is_specified_operators(char *str)
{
	return (is_specified_infile(str) || is_specified_here_doc(str)
		|| is_specified_outfile_overwriting(str)
		|| is_specified_outfile_apend(str) || is_specified_semicolon(str)
		|| is_specified_pipe(str) || is_specified_pipe_pipe(str)
		|| is_specified_ampersant(str) || is_specified_apersant_ampersant(str));
}
