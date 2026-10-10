/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbecker <kbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 21:38:50 by naperisw          #+#    #+#             */
/*   Updated: 2026/01/16 14:01:28 by kbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_last_status(t_shell *shell, int status)
{
	if (WIFEXITED(status))
		shell->last_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->last_status = 128 + WTERMSIG(status);
}

void	update_status_and_print(t_shell *shell, int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		else if (WTERMSIG(status) == SIGQUIT)
			write(STDERR_FILENO, "Quit (core dumped)\n", 19);
	}
	update_last_status(shell, status);
}

static void	run_exec_child(char *path, char **argv, t_command *cmd,
				t_shell *shell)
{
	struct stat	st;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (redirects_apply(cmd) != EXIT_SUCCESS)
	{
		free(path);
		free_token(argv);
		exit (EXIT_FAILURE);
	}
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

void	run_child_process(char *path, char **argv, t_command *cmd,
		t_shell *shell)
{
	pid_t	pid;
	int		status;
	int		ret;

	update_last_command(shell, cmd);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		shell->last_status = 1;
		return ;
	}
	if (pid == 0)
		run_exec_child(path, argv, cmd, shell);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	ret = waitpid(pid, &status, 0);
	while (ret == -1 && errno == EINTR)
		ret = waitpid(pid, &status, 0);
	if (ret == -1)
		return (perror("waitpid"), shell->last_status = 1, init_signals(shell));
	update_status_and_print(shell, status);
	init_signals(shell);
}

void	external_executed(t_shell *shell, t_command *cmd)
{
	char	*path;
	char	**argv;
	int		ret;

	ret = get_path_and_argv(shell, cmd, &argv, &path);
	if (ret != 0)
	{
		shell->last_status = ret;
		return ;
	}
	run_child_process(path, argv, cmd, shell);
	close_heredoc_fd(cmd);
	free(path);
	free_token(argv);
}
