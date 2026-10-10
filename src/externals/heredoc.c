/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naperisw <naperisw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 19:46:33 by naperisw          #+#    #+#             */
/*   Updated: 2026/02/01 18:20:15 by naperisw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_parent(pid_t pid, int read_fd, t_shell *shell)
{
	int	status;

	if (waitpid(pid, &status, 0) < 0)
	{
		perror("waitpid");
		close(read_fd);
		shell->last_status = 1;
		init_signals(shell);
		return (EXIT_FAILURE);
	}
	update_last_status(shell, status);
	init_signals(shell);
	if (shell->last_status == 128 + SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		close(read_fd);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static void	heredoc_child_loop(t_shell *shell, t_redirect *redirect,
			int write_end)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("minishell: warning: here-document"
				" delimited by end-of-file (wanted `", STDERR_FILENO);
			ft_putstr_fd(redirect->filename, STDERR_FILENO);
			ft_putendl_fd("')", STDERR_FILENO);
			close(write_end);
			exit(EXIT_SUCCESS);
		}
		if (ft_strcmp(line, redirect->filename) == 0)
		{
			free(line);
			close(write_end);
			exit(EXIT_SUCCESS);
		}
		write_heredoc_line(shell, redirect, write_end, line);
	}
}

static void	heredoc_child(t_shell *shell, t_redirect *redirect, int fd[2])
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	close(fd[0]);
	heredoc_child_loop(shell, redirect, fd[1]);
	exit(EXIT_SUCCESS);
}

int	handle_heredoc(t_redirect *redirect, t_shell *shell)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return (perror("pipe"), shell->last_status = 1, EXIT_FAILURE);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		close_pipe(fd);
		init_signals(shell);
		return (shell->last_status = 1, EXIT_FAILURE);
	}
	if (pid == 0)
		heredoc_child(shell, redirect, fd);
	close(fd[1]);
	if (heredoc_parent(pid, fd[0], shell))
		return (EXIT_FAILURE);
	redirect->heredoc_fd = fd[0];
	return (EXIT_SUCCESS);
}

int	prepare_heredoc(t_shell *shell)
{
	t_command	*cmd;
	t_redirect	*redirect;

	cmd = shell->commands;
	while (cmd)
	{
		redirect = cmd->redirects;
		while (redirect)
		{
			if (redirect->type == REDIRECT_HEREDOC)
			{
				if (handle_heredoc(redirect, shell) != EXIT_SUCCESS)
					return (EXIT_FAILURE);
			}
			redirect = redirect->next;
		}
		cmd = cmd->next;
	}
	return (EXIT_SUCCESS);
}
