/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_cmd_handling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbecker <kbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 13:57:28 by kbecker           #+#    #+#             */
/*   Updated: 2026/01/16 13:58:42 by kbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_last_command(t_shell *shell, t_command *cmd)
{
	char	*last_arg;

	if (cmd->number_args > 0)
		last_arg = cmd->args[cmd->number_args - 1];
	else
		last_arg = cmd->command_name;
	add_or_update_by_keyname(shell->env, KEYNAME_LAST_CMD, last_arg);
}
