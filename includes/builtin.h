/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbecker <kbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 16:32:45 by kbecker           #+#    #+#             */
/*   Updated: 2026/02/02 12:27:35 by kbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# define EXIT_SHELL -1

# define BUILTIN_NOT_FOUND -2

# define CMD_EXIT "exit"
# define CMD_CD "cd"
# define CMD_ECHO "echo"
# define CMD_ENV "env"
# define CMD_EXPORT "export"
# define CMD_PWD "pwd"
# define CMD_UNSET "unset"

# define OPTION_N "-n"

# define MSG_DECLARE_X "declare -x "
# define ERR_TOO_MANY_ARGS "too many arguments"
# define ERR_NOT_A_VALID_ID "not a valid identifier"

typedef struct s_shell		t_shell;
typedef struct s_command	t_command;

//builtins.c
int			builtin_executed(t_shell *shell, t_command *cmd);

//builtin/cd.c
int			builtin_cd(t_shell *shell, t_command *cmd);

//builtin_echo.c
int			builtin_echo(t_shell *shell, t_command *cmd);

//builtin/env.c
int			builtin_env(t_shell *shell, t_command *cmd);

//builtin_exit.c
int			builtin_exit(t_shell *shell, t_command *cmd);

//builtin/export.c
int			builtin_export(t_shell *shell, t_command *cmd);

//builtin/pwd.c
int			builtin_pwd(t_shell *shell, t_command *cmd);

//builtin/unset.c
int			builtin_unset(t_shell *shell, t_command *cmd);

#endif