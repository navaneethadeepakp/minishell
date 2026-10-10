/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naperisw <naperisw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:11:45 by naperisw          #+#    #+#             */
/*   Updated: 2026/01/05 14:24:50 by naperisw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	wait_for_pipe(pid_t last_pid, t_shell *shell)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (last_pid != -1)
	{
		waitpid(last_pid, &status, 0);
		update_status_and_print(shell, status);
	}
	while (wait(NULL) > 0)
		;
	init_signals(shell);
}

static void	update_parent_fd(int *prev_fd, int pipe_fd[2], int has_next)
{
	if (*prev_fd != -1)
	{
		close(*prev_fd);
		*prev_fd = -1;
	}
	if (has_next)
	{
		close(pipe_fd[1]);
		*prev_fd = pipe_fd[0];
	}
}

static pid_t	setup_pipe_and_fork(int has_pipe, int pipe_fd[2], int prev_fd)
{
	pid_t	pid;

	if (has_pipe && pipe(pipe_fd) == -1)
	{
		perror("pipe");
		if (prev_fd != -1)
			close(prev_fd);
		return (-1);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		if (prev_fd != -1)
			close(prev_fd);
		if (has_pipe)
			close_pipe(pipe_fd);
		return (-1);
	}
	return (pid);
}

static int	fork_one_cmd(t_shell *shell, t_command *cmd,
			int *prev_fd, pid_t *last_pid)
{
	int		pipe_fd[2];
	pid_t	pid;

	pid = setup_pipe_and_fork(cmd->next != NULL, pipe_fd, *prev_fd);
	if (pid < 0)
		return (1);
	if (pid == 0)
		exec_pipe_child(shell, cmd, *prev_fd, pipe_fd);
	else
		close_heredoc_fd(cmd);
	if (!cmd->next)
		*last_pid = pid;
	update_parent_fd(prev_fd, pipe_fd, cmd->next != NULL);
	return (0);
}

void	execute_pipes(t_shell *shell)
{
	t_command	*cmd;
	int			prev_fd;
	pid_t		last_pid;

	cmd = shell->commands;
	prev_fd = -1;
	last_pid = -1;
	while (cmd)
	{
		if (fork_one_cmd(shell, cmd, &prev_fd, &last_pid))
		{
			if (prev_fd != -1)
				close (prev_fd);
			return ;
		}
		cmd = cmd->next;
	}
	if (prev_fd != -1)
		close(prev_fd);
	wait_for_pipe(last_pid, shell);
}
