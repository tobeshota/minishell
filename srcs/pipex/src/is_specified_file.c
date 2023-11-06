/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_specified_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:31:16 by toshota           #+#    #+#             */
/*   Updated: 2023/11/06 17:34:54 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_specified_infile(char *str)
{
	return (ft_strlen(str) == ft_strlen("<") && (!ft_strncmp(str, "<",
				ft_strlen(str))));
}

int	is_specified_here_doc(char **argv)
{
	return (ft_strlen(argv[0]) == ft_strlen("<<") && (!ft_strncmp(argv[0], "<<",
				ft_strlen(argv[0]))));
}

int	is_specified_outfile_overwriting(char *str)
{
	return (ft_strlen(str) == ft_strlen(">") && (!ft_strncmp(str, ">",
				ft_strlen(str))));
}

int	is_specified_outfile_apend(char *str)
{
	return (ft_strlen(str) == ft_strlen(">>") && (!ft_strncmp(str, ">>",
				ft_strlen(str))));
}
