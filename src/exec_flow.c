/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_flow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbecker <kbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:43:31 by naperisw          #+#    #+#             */
/*   Updated: 2026/01/27 10:18:11 by kbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_builtin(t_shell *shell, t_command *cmd)
{
	int	stdin_backup;
	int	stdout_backup;
	int	return_code;

	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	if (stdin_backup < 0 || stdout_backup < 0)
	{
		if (stdin_backup >= 0)
			close(stdin_backup);
		if (stdout_backup >= 0)
			close(stdout_backup);
		return (EXIT_FAILURE);
	}
	if (redirects_apply(cmd) != EXIT_SUCCESS)
		return (close_heredoc_fd(cmd),
			restore_fds(stdin_backup, stdout_backup), EXIT_FAILURE);
	update_last_command(shell, cmd);
	return_code = builtin_executed(shell, cmd);
	restore_fds(stdin_backup, stdout_backup);
	return (return_code);
}

static int	execute_single_command(t_shell *shell, t_command *cmd)
{
	int	ret;

	if (!cmd || !cmd->command_name || !cmd->command_name[0])
		return (EXIT_SUCCESS);
	if (is_builtin(cmd))
	{
		ret = exec_builtin(shell, cmd);
		if (ret == EXIT_SHELL)
			return (EXIT_SHELL);
		shell->last_status = ret;
		return (EXIT_SUCCESS);
	}
	external_executed(shell, cmd);
	return (EXIT_SUCCESS);
}

static int	exec_commands(t_shell *shell)
{
	int	ret;

	if (!shell->commands)
		return (EXIT_SUCCESS);
	if (prepare_heredoc(shell) != EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	if (shell->commands->next == NULL)
	{
		ret = execute_single_command(shell, shell->commands);
		if (ret == EXIT_SHELL)
			return (EXIT_SHELL);
	}
	else
		execute_pipes(shell);
	return (EXIT_SUCCESS);
}

int	exec_and_cleanup(t_shell *shell)
{
	int	ret;

	check_env_vars(shell);
	ret = exec_commands(shell);
	if (shell->commands)
	{
		free_commands(shell->commands);
		shell->commands = NULL;
	}
	if (ret == EXIT_SHELL)
		return (EXIT_SHELL);
	return (EXIT_SUCCESS);
}
