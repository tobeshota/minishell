/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:14:49 by toshota           #+#    #+#             */
/*   Updated: 2023/11/01 17:35:25 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


static int	is_specified_infile(char *str)
{
	return (ft_strlen(str) == ft_strlen("<") && (!ft_strncmp(str, "<", ft_strlen(str))));
}

static int	is_specified_outfile_overwriting(char *str)
{
	return (ft_strlen(str) == ft_strlen(">") && (!ft_strncmp(str, ">", ft_strlen(str))));
}

static int	is_specified_outfile_apend(char *str)
{
	return (ft_strlen(str) == ft_strlen(">>") && (!ft_strncmp(str, ">>", ft_strlen(str))));
}


// infile	< の直後のファイル
char	*get_infile(char **argv)
{
	int		arg_i;

	arg_i = 0;
	// argvに < が来るまで探す
	while(argv[arg_i])
	{
		// < の次にある文字列をinfileとする
		if(is_specified_infile(argv[arg_i]))
			return argv[arg_i + 1];
		arg_i++;
	}
	return NOT_SPECIFIED;
}

// outfile	> または >> の直後のファイル
char	*get_outfile(char **argv)
{
	int arg_i;

	arg_i = 0;
	// argvに > または >> が来るまで探す
	while(argv[arg_i])
	{
		// >の次にある文字列をinfileとする
		if(is_specified_outfile_overwriting(argv[arg_i]) || is_specified_outfile_apend(argv[arg_i]))
			return argv[arg_i + 1];
		arg_i++;
	}
	return NOT_SPECIFIED;
}
