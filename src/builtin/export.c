/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbecker <kbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 11:55:35 by kbecker           #+#    #+#             */
/*   Updated: 2026/02/02 12:27:47 by kbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_arg(t_shell *shell, char *arg, int *error_exists)
{
	int	i;

	*error_exists = 1;
	if (!arg || (!ft_isalpha(arg[0]) && arg[0] != '_'))
		return (show_indiv_error(shell, CMD_EXPORT,
				arg, ERR_NOT_A_VALID_ID));
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			return (show_indiv_error(shell, CMD_EXPORT,
					arg, ERR_NOT_A_VALID_ID));
			return (EXIT_FAILURE);
		}
		i++;
	}
	*error_exists = 0;
	if (!arg[i])
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	builtin_export(t_shell *shell, t_command *cmd)
{
	int	i;
	int	arg_error;
	int	error_exists;

	if (!cmd->args || !cmd->args[0])
		return (builtin_env(shell, NULL));
	error_exists = 0;
	arg_error = 0;
	i = 0;
	while (cmd->args[i])
	{
		if (check_arg(shell, cmd->args[i], &arg_error) == EXIT_SUCCESS)
			add_or_update_by_entry(shell->env, cmd->args[i]);
		if (arg_error)
			error_exists = 1;
		i++;
	}
	if (error_exists)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
