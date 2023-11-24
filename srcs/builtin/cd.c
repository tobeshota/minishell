/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:39:21 by toshota           #+#    #+#             */
/*   Updated: 2023/11/24 18:04:01 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static bool	get_path_from_cmd_arg(char **path_ptr, char **cmd, char ***envp)
{
	char *tmp;

	if (cmd[1] == NULL || is_match(cmd[1], "~") || is_match(cmd[1], "~/"))
	{
		*path_ptr = getenv("HOME");
		if(check_getenv(*path_ptr) == false)
			return (free(*path_ptr), false);
		*path_ptr = check_malloc(ft_strdup(*path_ptr));
		return true;
	}
	else if (cmd[1][0] == '~')
	{
		*path_ptr = getenv("HOME");
		if(check_getenv(*path_ptr) == false)
			return (free(*path_ptr), false);
		*path_ptr = check_malloc(ft_strdup(*path_ptr));
		tmp = *path_ptr;
		*path_ptr = \
		check_malloc(ft_strjoin(*path_ptr, cmd[1] + ft_strlen("~")));
		free(tmp);
	}
	else
		*path_ptr = check_malloc(ft_strdup(cmd[1]));
	return (true);
}

static bool update_env(char ***envp, char *varname, char *new_data)
{
	int env_i;

	env_i = 0;
	while(ft_strncmp(envp[0][env_i], varname, ft_strlen(varname)))
		env_i++;
	if(is_path_found(envp[0][env_i]) == false)
		return false;
	envp[0][env_i] = check_malloc(ft_strjoin(varname, new_data));
ft_printf(">> %s\n", envp[0][env_i]);
	return true;
}

static bool	is_path_alreadly_absollute_path(char *path)
{
	return (path[0] == '/' && (path[1] == '\0' || ft_strchr(&path[1], '/')));
}

int	get_down_count_from_cwd(char *relative_path)
{
	int	down_count_from_pwd;

	down_count_from_pwd = 0;
	while (ft_strnstr(relative_path, "../", ft_strlen(relative_path)))
	{
		down_count_from_pwd++;
		relative_path += ft_strlen("../");
	}
	// 最後だけ..が考えられる cd ..
	if (ft_strnstr(relative_path, "..", ft_strlen("..")))
	{
		down_count_from_pwd++;
		relative_path += ft_strlen("..");
	}
	return (down_count_from_pwd);
}

// 引数として渡ってくる**pwd_path: "/Users/tobeshota/workspace/42/minishell/"
char	*down_cwd(char *cwd, int down_count_from_cwd)
{
	int		delete_len_for_cwd;

	while(down_count_from_cwd)
	{
		if (!ft_strncmp(cwd, "PWD=/", ft_strlen(cwd)))
			break;
		else
		{
			delete_len_for_cwd = ft_strlen(cwd) - ft_strlen(ft_strrchr(cwd, '/'));
			ft_strlcpy(cwd, cwd, delete_len_for_cwd+1);
		}
		down_count_from_cwd--;
	}
	return cwd;
}

char	*down_passed_path(char *passed_path, int down_count_from_cwd)
{
	int	delete_len_for_passed_path_ptr;

	while(down_count_from_cwd)
	{
		if (!ft_strncmp(passed_path, "..", ft_strlen(passed_path)))
		{
			ft_strlcpy(passed_path, "", 1);
		}
		else
		{
			delete_len_for_passed_path_ptr = ft_strlen(passed_path) - ft_strlen(ft_strchr(passed_path, '/'));
			ft_strlcpy(passed_path, passed_path + delete_len_for_passed_path_ptr + 1, ft_strlen(passed_path));
		}
		down_count_from_cwd--;
	}
	return passed_path;
}

bool	change_current_directory(char ***envp, int env_i, char *path)
{
	int		down_count_from_cwd;
	char	*tmp;

	// cdの引数として渡ってくるpathの末尾が/終わりの場合，末尾の/を取る
	if (ft_strncmp(path, "/", ft_strlen(path)) && path[ft_strlen(path) - 1] == '/')
		ft_strlcpy(path, path, ft_strlen(path));
	if (is_path_alreadly_absollute_path(path))
	{
		tmp = path;
		path = check_malloc(ft_strjoin("PWD=", path));
		ft_strlcpy(envp[0][env_i], path, ft_strlen(path) + 1);
	}
	else
	{
		// カレントディレクトリとlsが対応しないため↓の is_file_exist(path) の結果が適切に出ない問題をどうにかする！
		if (is_file_exist(path) == false)
			return (put_error("-bash: cd: "), put_error(path), put_error(": No such file or directory\n"), free(path), true);
		down_count_from_cwd = get_down_count_from_cwd(path);
		envp[0][env_i] = down_cwd(envp[0][env_i], down_count_from_cwd);
		path = down_passed_path(path, down_count_from_cwd);
		// pathに何か文字が残っていたら/を加えたのちにつなげる
		if (ft_strlen(path))
		{
			tmp = path;
			path = ft_strjoin("/", path);
			free(tmp);
		}
		tmp = path;
		path = check_malloc(ft_strjoin(envp[0][env_i], path));
		ft_strlcpy(envp[0][env_i], path, ft_strlen(path) + 1);
		if (!ft_strncmp(envp[0][env_i], "PWD=", ft_strlen(envp[0][env_i])))
			ft_strlcpy(envp[0][env_i], "PWD=/", ft_strlen("PWD=/") + 1);
	}
	return (free(path), free(tmp), true);
}


int	exec_cd(char **cmd, char ***envp)
{
	char	*path;
	char	*wd;

	if (get_path_from_cmd_arg(&path, cmd, envp) == false)
		return (free(path), false);
	if (is_match(path, ".") || is_match(path, "./"))
		return (free(path), true);
	if (is_file_exist(path) == false)
	{
		put_error("-bash: cd: ");
		put_error(path);
		put_error(": No such file or directory\n");
		return (free(path), true);
	}
	if (chdir(path) == -1)
		return (free(path), false);


	/* env記載のPWD=を書き換える！ */
	// wd = getenv("PWD");	/* getenv();は現在のenvから値をとっている．そのためchdir();実行後のgetenv("PWD");は実行前のものと変わっていない */
	// if(check_getenv(wd) == false)
	// 	return (free(path), false);
	// update_env(envp, "PWD=", wd);

	int env_i;

	env_i = 0;
	while(ft_strncmp(envp[0][env_i], "PWD=", ft_strlen("PWD=")))
		env_i++;
	if(is_path_found(envp[0][env_i]) == false)
		return false;
	return (change_current_directory(envp, env_i, path));
}
