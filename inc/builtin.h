/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobeshota <tobeshota@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:15:47 by toshota           #+#    #+#             */
/*   Updated: 2023/11/27 11:36:10 by tobeshota        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "define.h"
# include "pipex.h"

int		exec_echo(char **cmd, t_pipex *pipex);
int		exec_cd(char **cmd, t_env **env);
int		exec_pwd(t_pipex *pipex);
int		exec_export(char **cmd, t_env **env, t_pipex *pipex);
int		exec_unset(char **cmd, t_env **env);
int		exec_env(t_env **env, t_pipex *pipex);
int		exec_exit(char **cmd, t_pipex *pipex);

// exec_builtin.c
bool	is_match(char *s1, char *s2);
bool	is_cmd_builtin(char *cmd);
int		exec_builtin(t_env **env, t_pipex *pipex, int cmd_i);

#endif
