<p align="center">
 <img width="480" alt="minishell" src="https://github.com/JIA0010/minishell/assets/103044771/0051d502-083f-41fb-817b-dfbae963a337">
</p>

**Minishell is one of the [42](https://42tokyo.jp/) projects.**  
**It is a reimplementation of [bash](https://www.gnu.org/software/bash/)🐚**


---

# Description
<p align="center">
  <img width=375 src="https://github.com/JIA0010/minishell/assets/103044771/bc6ec802-b928-46b9-9b97-1464de5ff6cd">
  <img width=350 src="https://github.com/JIA0010/minishell/assets/103044771/6a86318f-09f3-46b3-a9f1-2aa328f6dbc6">
</p>

We implemented the main features of bash.
* Search and launch the right executable (e.g. **`./a.out`, `/bin/ls`** ..)
* builtins: **`echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`**
* File I/O management by redirection: **`>`, `>>`, `<`, `<<`**
* interprocess communication by [pipes](https://github.com/tobeshota/pipex.git): **`|`**
* signal: **`Ctrl-C`, `Ctrl-D`, `Ctrl-\`**
* expand environment variables with/without single/double quotes (e.g. **`$PWD`, `"$PATH"`, `'$HOME'`** ..)
* expand exit status: **`$?`**
* expand wildcards: **`*`**
* control operators: **`;`, `&&`, `||`**

# Usage
### Requirements
- [ ] `readline` (It is used where the shell accepts commands)
```shell
brew install readline
```

### Installation
Clone this repository.
```shell
git clone https://github.com/tobeshota/minishell.git
```
Change directory to this repository.
```shell
cd minishell
```
Compile to create an executable file: `minishell`.
```shell
make
```
Execute.
```shell
./minishell
```
