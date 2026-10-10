/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naperisw <naperisw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:26:50 by kbecker           #+#    #+#             */
/*   Updated: 2026/02/01 18:50:55 by naperisw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define ERR_WRONG_INPUT "Error: No arguments allowed!\n"
# define ERR_MSG "Error"

# define EXIT_CODE_CMD_NOT_FOUND 127
# define EXIT_CODE_PERMISSION_DENIED 126

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include "../libft/libft.h"
# include "./text_formatting.h"
# include "../env/env.h"
# include "../parsing/parsing.h"
# include "./builtin.h"
# include "./external.h"

typedef struct s_shell
{
	int			error_exists;
	t_env		*env;
	pid_t		pid;
	t_command	*commands;
	int			number_commands;
	int			is_interactive;
	int			last_status;
}	t_shell;

//error_handling.c
void		set_error(t_shell *shell, char *err_msg);
int			set_shell_error(t_shell *shell, int err_no,
				char *cmd_name, char *arg);
int			show_indiv_error(t_shell *shell, char *cmd_name,
				char *arg, char *err_msg);

//check_input.c
int			check_input(t_shell *shell, int argc, char **argv);

//shell_init.c
void		init_shell(t_shell *shell, int argc, char **argv, char **envp);

//shell_free.c
void		free_shell(t_shell *shell);

//error_handling.c
void		set_error(t_shell *shell, char *err_msg);

//last_cmd_handling.c
void		update_last_command(t_shell *shell, t_command *cmd);

//parse_env_handling.c
void		check_env_vars(t_shell *shell);
char		*expand_var(t_shell *shell, char *start, char **end);

//üarse_rebuild_args.c
void		rebuild_args_after_expansion(t_command *cmd);

//read_input.c
int			read_input(t_shell *shell);

//prompt.c - display prompt
char		*display_prompt(t_shell *shell);

//signal.c - signal handling //Ctrl+C
void		init_signals(t_shell *shell);
void		signal_handler(int sig);

//execute commands and clean
int			exec_and_cleanup(t_shell *shell);

#endif
