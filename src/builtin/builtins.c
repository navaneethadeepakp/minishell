/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naperisw <naperisw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 11:15:39 by kbecker           #+#    #+#             */
/*   Updated: 2025/12/17 17:02:28 by naperisw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_executed(t_shell *shell, t_command *cmd)
{
	if (ft_strcmp(cmd->command_name, CMD_EXIT) == 0)
		return (builtin_exit(shell, cmd));
	if (ft_strcmp(cmd->command_name, CMD_CD) == 0)
		return (builtin_cd(shell, cmd));
	if (ft_strcmp(cmd->command_name, CMD_ECHO) == 0)
		return (builtin_echo(shell, cmd));
	if (ft_strcmp(cmd->command_name, CMD_ENV) == 0)
		return (builtin_env(shell, cmd));
	if (ft_strcmp(cmd->command_name, CMD_EXPORT) == 0)
		return (builtin_export(shell, cmd));
	if (ft_strcmp(cmd->command_name, CMD_PWD) == 0)
		return (builtin_pwd(shell, cmd));
	if (ft_strcmp(cmd->command_name, CMD_UNSET) == 0)
		return (builtin_unset(shell, cmd));
	return (BUILTIN_NOT_FOUND);
}
