/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:14:49 by toshota           #+#    #+#             */
/*   Updated: 2023/11/06 17:28:34 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	is_infile_valid(char *infile)
{
	int	fd;

	if (infile == NOT_SPECIFIED)
		fd = open_file(HERE_DOC_FILE_PATH, INFILE_HERE_DOC);
	else
		fd = open_file(infile, INFILE);
	check_close(close(fd));
	if (fd == -1)
		return (FALSE);
	return (TRUE);
}

static int	is_outfile_valid(char *infile, char *outfile)
{
	int	fd;

	if (infile == NOT_SPECIFIED)
		fd = open_file(outfile, OUTFILE_HERE_DOC);
	else
		fd = open_file(outfile, OUTFILE);
	check_close(close(fd));
	if (fd == -1)
		return (FALSE);
	return (TRUE);
}

static int	is_argv_valid(int argc, char **argv)
{
	if (is_outfile_valid(get_infile(argv), get_outfile(argv)) == FALSE)
		return (FALSE);
	if (is_infile_valid(get_infile(argv)) == FALSE)
		return (FALSE);
	return (TRUE);
}

void	check_arg(int argc, char **argv)
{
	if (is_argv_valid(argc, argv) == FALSE)
		exit(1);
}
