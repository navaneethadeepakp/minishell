/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naperisw <naperisw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 14:44:37 by naperisw          #+#    #+#             */
/*   Updated: 2026/02/01 18:06:02 by naperisw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXTERNAL_H
# define EXTERNAL_H

# include <stdio.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include "../libft/libft.h"

extern volatile int	g_sig;

// single external command
void	external_executed(t_shell *shell, t_command *cmd);

//  pipes
void	execute_pipes(t_shell *shell);
void	close_pipe(int pipe_fd[2]);
void	exec_pipe_child(t_shell *shell, t_command *cmd,
			int prev_fd, int pipe_fd[2]);

// heredoc
int		prepare_heredoc(t_shell *shell);
void	close_heredoc_fd(t_command *cmd);
int		redirect_heredoc(t_redirect *redirect);
void	write_heredoc_line(t_shell *shell, t_redirect *redirect,
			int write_end, char *line);

// redirects
int		redirects_apply(t_command *cmd);

// status helpers(pipes + externals)
void	update_last_status(t_shell *shell, int status);
void	update_status_and_print(t_shell *shell, int status);

// argv + path helpers
int		is_builtin(t_command *cmd);
int		get_path_and_argv(t_shell *shell, t_command *cmd,
			char ***argv, char **path);

// fd restore
void	restore_fds(int in, int out);

#endif