/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:15:47 by toshota           #+#    #+#             */
/*   Updated: 2023/11/22 11:59:31 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "define.h"
# include "pipex.h"

int		exec_echo(char **cmd, t_pipex_data *pipex_data);
int		exec_cd(char **cmd, char ***envp);
int		exec_pwd(char **envp, t_pipex_data *pipex_data);
int		exec_export(char **cmd, char ***envp);
int		exec_unset(char ***envp);
int		exec_env(char **envp, t_pipex_data *pipex_data);
int		exec_exit(void);

// exec_builtin.c
bool	is_cmd_builtin(char *cmd);
int		exec_builtin(char ***envp, t_pipex_data *pipex_data, int cmd_i);

#endif
