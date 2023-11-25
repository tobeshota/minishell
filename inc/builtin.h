/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:15:47 by toshota           #+#    #+#             */
/*   Updated: 2023/11/25 21:02:32 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "define.h"
# include "pipex.h"

int		exec_echo(char **cmd, t_pipex_data *pipex_data);
int		exec_cd(char **cmd, t_env **env_node);
int		exec_pwd(t_pipex_data *pipex_data);
int		exec_export(char **cmd, char ***envp);
int		exec_unset(char ***envp);
int		exec_env(char **envp, t_pipex_data *pipex_data);
int		exec_exit(char	**cmd, t_pipex_data *pipex_data);

// exec_builtin.c
bool	is_match(char *s1, char *s2);
bool	is_cmd_builtin(char *cmd);
int		exec_builtin(char ***envp, t_pipex_data *pipex_data, int cmd_i, t_env **env_node);

#endif
