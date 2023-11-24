/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:39:21 by toshota           #+#    #+#             */
/*   Updated: 2023/11/24 11:39:21 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	exec_exit(t_pipex_data *pipex_data)
{

	// ./minishellのプロセスが1つであるのときexitを実行したときはEXIT_MSGを出力する．
	// ./minishellのプロセスが1つでないときにexitを実行したときは"exit"を出力する．
	ft_putendl_fd("exit", pipex_data->outfile_fd);
	return (exit(0), true);
}
