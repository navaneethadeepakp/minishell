/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naperisw <naperisw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 23:36:41 by naperisw          #+#    #+#             */
/*   Updated: 2026/01/09 19:07:09 by naperisw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipe(int pipe_fd[2])
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

static void	close_child_fd(int prev_fd, int pipe_fd[2], int has_next)
{
	if (prev_fd != -1)
		close(prev_fd);
	if (has_next)
		close_pipe(pipe_fd);
}

static void	setup_pipe_fd(t_command *cmd, int prev_fd, int pipe_fd[2])
{
	if (prev_fd != -1 && dup2(prev_fd, STDIN_FILENO) == -1)
	{
		close_child_fd(prev_fd, pipe_fd, cmd->next != NULL);
		exit(EXIT_FAILURE);
	}
	if (cmd->next && dup2(pipe_fd[1], STDOUT_FILENO) == -1)
	{
		close_child_fd(prev_fd, pipe_fd, cmd->next != NULL);
		exit(EXIT_FAILURE);
	}
	close_child_fd(prev_fd, pipe_fd, cmd->next != NULL);
	if (redirects_apply(cmd) != EXIT_SUCCESS)
		exit(EXIT_FAILURE);
}

static void	exec_pipe_command(t_shell *shell, t_command *cmd)
{
	char		**argv;
	char		*path;
	int			ret;
	struct stat	st;

	ret = get_path_and_argv(shell, cmd, &argv, &path);
	if (ret != 0)
		exit(ret);
	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		errno = EISDIR;
		perror(cmd->command_name);
		free(path);
		free_token(argv);
		exit(EXIT_CODE_PERMISSION_DENIED);
	}
	execve(path, argv, shell->env->env_entries);
	perror(cmd->command_name);
	free(path);
	free_token(argv);
	if (errno == EACCES || errno == ENOEXEC || errno == EISDIR)
		exit(EXIT_CODE_PERMISSION_DENIED);
	exit(EXIT_CODE_CMD_NOT_FOUND);
}

void	exec_pipe_child(t_shell *shell, t_command *cmd,
						int prev_fd, int pipe_fd[2])
{
	int	ret;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	setup_pipe_fd(cmd, prev_fd, pipe_fd);
	if (is_builtin(cmd))
	{
		ret = builtin_executed(shell, cmd);
		if (ret == EXIT_SHELL)
			exit(shell->last_status);
		exit(ret);
	}
	exec_pipe_command(shell, cmd);
}
