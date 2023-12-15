/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjia <cjia@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:15:47 by toshota           #+#    #+#             */
/*   Updated: 2023/12/15 12:39:14 by cjia             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "define.h"
# include "pipex.h"

int		exec_echo(char **cmd, t_pipex *pipex);
int		exec_cd(char **cmd, t_env **env, t_pipex *pipex);
int		exec_pwd(t_pipex *pipex);
int		exec_unset(char **cmd, t_env **env);
int		exec_env(t_env **env, t_pipex *pipex);
int		exec_exit(char **cmd, t_pipex *pipex);

// exec_builtin.c
bool	is_match(char *s1, char *s2);
bool	is_cmd_builtin(char *cmd);
char	**split_wo_enclosed_str(char *str, char splitter);
int		exec_builtin(t_env **env, t_pipex *pipex, int cmd_i);

// exec_export
int		exec_export(char **cmd, t_env **env, t_pipex *pipex);
void	show_env(t_env **env, t_pipex *pipex);
void	add_new_value(char *added_value, t_env **env);
void	update_value(char *added, t_env **env);
bool	update_envp(t_env **env, char *varname, char *new_data);
t_env	*get_old_env_to_be_updated(char *added, t_env *env);
bool	check_identifier(char *identifier);
bool	is_under_bar(char *cmd);
bool	is_node_first(t_env *node);
bool	is_node_last(t_env *node);

#endif
