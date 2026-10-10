/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naperisw <naperisw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 16:00:41 by kbecker           #+#    #+#             */
/*   Updated: 2026/02/01 17:53:03 by naperisw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define PARSE_ERR_MSG "Parsing Error: "

# include "../libft/libft.h"
# include "../includes/text_formatting.h"
# include "redirect.h"
# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>

typedef struct s_command
{
	int					idx;
	char				*command_line;
	char				*command_name;
	char				**args;
	int					number_args;
	t_redirect			*redirects;
	struct s_command	*prev;
	struct s_command	*next;
}	t_command;

//parse_args.c
char		**parse_arguments(char *cmd_line, int *n_of_args);
char		**copy_args(t_command *cmd, char **src, int no_of_args,
				int no_of_redirects);
int			set_args(t_command *cmd, char **args, int no_of_args, int *status);
int			no_of_arguments(char *cmd_line);
void		free_args(char **args, int i);

//parse_free.c
void		free_token(char **token);
void		free_commands(t_command *cmd);

//parse_command.c
int			get_no_of_commands(t_command *cmd);
char		*get_command_line(char **input_ptr);
t_command	*create_command(t_command *prev_cmd, char *cmd_line,
				int idx, int *status);

//parse_input.c
t_command	*parse_input(char *input, int *status);
t_command	*get_first_cmd(t_command *cmd);

//parse_redirect.c
int			extract_redirects(t_command *cmd, char **args,
				int no_of_args, int *status);
char		*remove_quotes(const char *s);
int			has_quotes_heredoc(const char *s);

//parse_token.c
char		*find_end_of_token(char *str, char *quote_char);

//parse_utils.c
char		*skip_spaces(char *str);
char		*get_token(char *start, char *end);

//parsing_suntax_error.c
int			ends_with_pipe(char	*str);
int			handle_syntax_error(t_command *cmd, char *input,
				char *ptr, int *status);

#endif
