<p align="center">
 <img width="480" alt="minishell" src="https://github.com/JIA0010/minishell/assets/103044771/654d1135-1a55-4d8b-9969-674b95791d04">
</p>

**minishell is one of the [42](https://42tokyo.jp/) projects.**  
**It is a reimplementation of `bash`.**
---

# Description
<p align="center">
  <img width=375 src="https://github.com/JIA0010/minishell/assets/103044771/bc6ec802-b928-46b9-9b97-1464de5ff6cd">
  <img width=350 src="https://github.com/JIA0010/minishell/assets/103044771/6a86318f-09f3-46b3-a9f1-2aa328f6dbc6">
</p>


We implemented the following bash functions in c language.

We learned how the shell works through implementation.
* Search and launch the right executable (e.g. **`./a.out`, `/bin/ls`** ..)
* builtins: **`echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`**
* File I/O management by redirection: **`>`, `>>`, `<`, `<<`**
* interprocess communication by pipes: **`|`**
* signal: **`Ctrl-C`, `Ctrl-D`, `Ctrl-\`**
* expand environment variables (e.g. **`$PWD`, `$PATH`** ..)
* expand exit status: **`$?`**
* expand wildcards: **`*`**
* control operators: **`;`, `&&`, `||`**
