/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshota <toshota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:32:48 by toshota           #+#    #+#             */
/*   Updated: 2023/11/16 16:09:36 by toshota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static void get_envp_for_debug(char ***envp)
{
*envp = ft_split("NVM_RC_VERSION= \
TERM_PROGRAM=vscode \
PYENV_ROOT=/Users/tobeshota/.pyenv \
NVM_CD_FLAGS= \
TERM=xterm-256color \
SHELL=/bin/bash \
TMPDIR=/var/folders/6h/j5146jk15y58jkw6l65v684r0000gn/T/ \
CONDA_SHLVL=0 \
TERM_PROGRAM_VERSION=1.84.2 \
ORIGINAL_XDG_CURRENT_DESKTOP=undefined \
MallocNanoZone=0 \
NVM_DIR=/Users/tobeshota/.nvm \
USER=tobeshouta \
COMMAND_MODE=unix2003 \
CONDA_EXE=/Users/tobeshota/anaconda3/bin/conda \
SSH_AUTH_SOCK=/private/tmp/com.apple.launchd.tUhcHRa0j9/Listeners \
__CF_USER_TEXT_ENCODING=0x1F5:0x1:0xE \
_CE_CONDA= \
PATH=/Library/Frameworks/Python.framework/Versions/3.6/bin:/opt/homebrew/opt/node@18/bin:/usr/local/Qt-5.15.10/bin:/opt/homebrew/opt/pyqt@5/5 5.15.7_2/bin:/opt/homebrew/opt/qt@5/bin:/Users/tobeshota/.nodebrew/current/bin:/Users/tobeshota/.pyenv/shims:/Users/tobeshota/.pyenv/bin:/Library/Frameworks/Python.framework/Versions/3.10/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/opt/X11/bin:/Library/Frameworks/Python.framework/Versions/3.6/bin:/Users/tobeshota/anaconda3/condabin:/opt/homebrew/opt/node@18/bin:/Users/tobeshota/.cargo/bin:/usr/local/Qt-5.15.10/bin:/opt/homebrew/opt/pyqt@5/5 5.15.7_2/bin:/opt/homebrew/opt/qt@5/bin:/Users/tobeshota/.nodebrew/current/bin:/Users/tobeshota/.pyenv/bin:/Library/Frameworks/Python.framework/Versions/3.10/bin:/Users/tobeshota/workspace/command:/Users/tobeshota/workspace/command \
LaunchInstanceID=4C3A25E0-D525-4249-A7DF-6528E2911523 \
AWS_DEFAULT_REGION=ap-northeast-1 \
__CFBundleIdentifier=com.microsoft.VSCode \
PWD=/Users/tobeshota/Desktop/pipex_for_minishell \
AWS_SECRET_ACCESS_KEY=M1nw55yKHTbB1A1+Jf17KAdVQ/lz2yHCLEOXf2lz \
LANG=ja_JP.UTF-8 \
VSCODE_GIT_ASKPASS_EXTRA_ARGS=--ms-enable-electron-run-as-node \
XPC_FLAGS=0x0 \
_CE_M= \
XPC_SERVICE_NAME=0 \
AWS_ACCESS_KEY_ID=AKIAUY7DXFBZM43SNCUM \
SHLVL=2 \
PYENV_SHELL=bash \
HOME=/Users/tobeshota \
VSCODE_GIT_ASKPASS_MAIN=/Applications/Visual Studio Code.app/Contents/Resources/app/extensions/git/dist/askpass-main.js \
CONDA_PYTHON_EXE=/Users/tobeshota/anaconda3/bin/python \
LOGNAME=tobeshouta \
VSCODE_GIT_IPC_HANDLE=/var/folders/6h/j5146jk15y58jkw6l65v684r0000gn/T/vscode-git-76a6b084d4.sock \
VSCODE_GIT_ASKPASS_NODE=/Applications/Visual Studio Code.app/Contents/Frameworks/Code Helper (Plugin).app/Contents/MacOS/Code Helper (Plugin) \
GIT_ASKPASS=/Applications/Visual Studio Code.app/Contents/Resources/app/extensions/git/dist/askpass.sh \
DISPLAY=/private/tmp/com.apple.launchd.ZmbSY2nNV3/org.xquartz:0 \
SECURITYSESSIONID=186a3 \
COLORTERM=truecolor \
_=./pipex \
OLDPWD=/Users/tobeshota/Desktop/pipex_for_minishell/src \
", '\n');
}

// 引数として，「変数展開された」，「コマンドとオプションが一つにまとまった(by parser)」文字列がくる
// 文字列の中には「｜」や「<<」，「>>」が入ることもある
// 最後の文字列が「>>」であるとき，outfileを追記モードで開く
// 最初の文字列が「<<」であるとき，infileを追記も
/*

■終了ステータス
【1】異常終了
・存在しない入力ファイルを渡された
・open()，close()，read()，fork()，dup()，execve()，unlink()，wait()に失敗した
【0】正常終了

*/
int	pipex(int argc, char **argv, char **envp)
{
	t_pipex_data	pipex_data;

	get_pipex_data(argc, argv, envp, &pipex_data);
	do_pipe(envp, &pipex_data);
	end_pipex(&pipex_data);
	return (0);
}


// >> ファイルが生成される問題をなんとかする！
int	main(int argc, char **argv, char **envp)
{
// argv = ft_split("< infile cat | cat > outfile", ' ');
argc = 6;
argv = (char **)malloc(sizeof(char *) * (argc + 1));
argv[0] = ft_strdup("<");
argv[1] = ft_strdup("infile");
argv[2] = ft_strdup("cat");
argv[3] = ft_strdup("|");
argv[4] = ft_strdup("cat -n");
argv[5] = ft_strdup(">");
argv[6] = ft_strdup("outfile");
argv[7] = NULL;

// argv[0] = ft_strdup("sort infile");
// argv[1] = NULL;



get_envp_for_debug(&envp);
	pipex(argc, argv, envp);
free(argv);
free(envp);
	return 0;
}

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q pipex");
// }
