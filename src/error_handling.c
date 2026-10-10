/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbecker <kbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 12:22:38 by kbecker           #+#    #+#             */
/*   Updated: 2026/01/16 09:33:58 by kbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_error(t_shell *shell, char *err_msg)
{
	shell->error_exists = EXIT_FAILURE;
	if (err_msg)
	{
		ft_putstr_fd(COLOR_RED, STDOUT_FILENO);
		ft_putstr_fd(err_msg, STDOUT_FILENO);
		ft_putstr_fd(COLOR_RESET, STDOUT_FILENO);
	}
	return ;
}

int	set_shell_error(t_shell *shell, int err_no, char *cmd_name, char *arg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd_name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (arg)
	{
		ft_putstr_fd("`", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd("': ", STDERR_FILENO);
	}
	ft_putendl_fd(strerror(err_no), STDERR_FILENO);
	if (err_no == ENOENT)
		shell->last_status = EXIT_CODE_CMD_NOT_FOUND;
	else
		shell->last_status = EXIT_FAILURE;
	return (shell->last_status);
}

int	show_indiv_error(t_shell *shell, char *cmd_name, char *arg, char *err_msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd_name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (arg)
	{
		ft_putstr_fd("`", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd("': ", STDERR_FILENO);
	}
	ft_putendl_fd(err_msg, STDERR_FILENO);
	shell->last_status = EXIT_FAILURE;
	return (shell->last_status);
}
