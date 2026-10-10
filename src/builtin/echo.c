/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbecker <kbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 10:07:41 by kbecker           #+#    #+#             */
/*   Updated: 2026/01/29 17:13:56 by kbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_arg(
			int *i, int print_newline, t_command *cmd, int *found_non_option)
{
	if (!print_newline && ft_strcmp(cmd->args[*i], OPTION_N) == 0
		&& !*found_non_option)
	{
		(*i)++;
		return (1);
	}
	*found_non_option = 1;
	return (0);
}

int	builtin_echo(t_shell *shell, t_command *cmd)
{
	int	i;
	int	print_newline;
	int	found_non_option;

	(void)shell;
	print_newline = 1;
	found_non_option = 0;
	i = 0;
	if (cmd->args && cmd->args[i] && ft_strcmp(cmd->args[i], OPTION_N) == 0)
	{
		print_newline = 0;
		i++;
	}
	while (cmd->args && cmd->args[i])
	{
		if (skip_arg(&i, print_newline, cmd, &found_non_option))
			continue ;
		ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
		if (cmd->args[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (print_newline)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
