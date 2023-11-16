/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:14:49 by toshota           #+#    #+#             */
/*   Updated: 2023/11/13 16:57:55 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

// infile	< の直後のファイル
char	*get_infile(char **argv)
{
	int		arg_i;

	arg_i = 0;
	// argvに < が来るまで探す
	while(argv[arg_i])
	{
		// < の次にある文字列を infile とする
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
		// > または >> の次にある文字列を outfile とする
		if(is_specified_outfile_overwriting(argv[arg_i]) || is_specified_outfile_apend(argv[arg_i]))
			return argv[arg_i + 1];
		arg_i++;
	}
	return NOT_SPECIFIED;
}
