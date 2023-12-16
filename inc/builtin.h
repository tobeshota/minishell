/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:15:47 by toshota           #+#    #+#             */
/*   Updated: 2023/12/16 22:40:55 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "define.h"
# include "pipex.h"

int		exec_echo(char **cmd, t_pipex *pipex);
int		exec_cd(char **cmd, t_env **env, t_pipex *pipex);
int		exec_pwd(t_pipex *pipex);
int		exec_unset(char **cmd, t_env **env, t_pipex *pipex);
int		exec_env(t_env **env, t_pipex *pipex);
int		exec_exit(char **cmd, t_pipex *pipex);

// exec_builtin.c
bool	is_match(char *s1, char *s2);
bool	is_cmd_builtin(char *cmd);
int		exec_builtin(t_env **env, t_pipex *pipex, int cmd_i);

// exec_export
int		exec_export(char **cmd, t_env **env, t_pipex *pipex);
void	show_env(t_env **env, t_pipex *pipex);
void	add_new_value(char *added_value, t_env **env, t_pipex *pipex);
void	update_value(char *added, t_env **env);
bool	update_envp(t_env **env, char *varname, char *new_data);
t_env	*get_old_env_to_be_updated(char *added, t_env *env);
bool	check_identifier(char *identifier, t_pipex *pipex);
bool	is_under_bar(char *cmd);
bool	is_node_first(t_env *node);
bool	is_node_last(t_env *node);

// split_wo_enclosed_str
#define SPLITTER 1
#define ENCLOSER 1
#define BEGINNING_OF_ENCLOSER 1
#define END_OF_ENCLOSER 1

char	**split_wo_enclosed_str(char *str, char splitter);
void	split_str_according_to_encloser(char **str, t_env **node_cmd, int i);
void	split_str_according_to_splitter(char **str, t_env **node_cmd, int i);
char	*omit_encloser_in_bos_and_eos(char *str);
void	nodeadd_from_0_to_i(t_env **node_cmd, char *str, int i);

#endif
