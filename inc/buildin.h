/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:15:47 by toshota           #+#    #+#             */
/*   Updated: 2023/11/20 14:31:13 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDIN_H
# define BUILDIN_H

# include "define.h"
# include "pipex.h"

int		execve_echo(char **cmd_with_parameter, t_pipex_data *pipex_data);
int		execve_cd(char **cmd_with_parameter, char ***envp);
int		execve_pwd(char **envp, t_pipex_data *pipex_data);
int		execve_export(char **cmd_with_parameter, char ***envp);
int		execve_unset(char ***envp);
int		execve_env(char **envp, t_pipex_data *pipex_data);
int		execve_exit(void);

// execve_builtin.c
bool	is_cmd_builtin(char *cmd);
int		execve_builtin(char *cmd, char **cmd_with_parameter, char ***envp,
			t_pipex_data *pipex_data);

#endif
