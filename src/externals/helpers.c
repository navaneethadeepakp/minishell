/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naperisw <naperisw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 17:09:03 by naperisw          #+#    #+#             */
/*   Updated: 2026/01/04 22:45:39 by naperisw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_command *cmd)
{
	if (!cmd || !cmd->command_name)
		return (0);
	return (
		!ft_strcmp(cmd->command_name, CMD_CD)
		|| !ft_strcmp(cmd->command_name, CMD_ECHO)
		|| !ft_strcmp(cmd->command_name, CMD_ENV)
		|| !ft_strcmp(cmd->command_name, CMD_EXIT)
		|| !ft_strcmp(cmd->command_name, CMD_EXPORT)
		|| !ft_strcmp(cmd->command_name, CMD_UNSET)
		|| !ft_strcmp(cmd->command_name, CMD_PWD)
	);
}

void	restore_fds(int in, int out)
{
	if (dup2(in, STDIN_FILENO) < 0)
		perror("dup2");
	if (dup2(out, STDOUT_FILENO) < 0)
		perror("dup2");
	close(in);
	close(out);
}
