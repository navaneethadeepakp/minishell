/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naperisw <naperisw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 11:21:55 by kbecker           #+#    #+#             */
/*   Updated: 2026/01/09 19:06:08 by naperisw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_isnumeric(char *s)
{
	int	i;

	if (!s || !*s)
		return (0);
	i = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(t_shell *shell, t_command *cmd)
{
	int	single_cmd;

	single_cmd = (cmd->prev == NULL && cmd->next == NULL);
	if (shell->is_interactive && single_cmd)
		ft_putendl_fd("exit", STDOUT_FILENO);
	if (cmd->number_args == 0)
		return (EXIT_SHELL);
	if (!ft_isnumeric(cmd->args[0]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd->args[0], STDERR_FILENO);
		ft_putendl_fd(" :numeric argument required", STDERR_FILENO);
		shell->last_status = 2;
		return (EXIT_SHELL);
	}
	if (cmd->number_args > 1)
	{
		ft_putendl_fd("minishell: exit: too many arguments ", STDERR_FILENO);
		shell->last_status = 1;
		return (1);
	}
	shell->last_status = (unsigned char)ft_atoi(cmd->args[0]);
	return (EXIT_SHELL);
}
