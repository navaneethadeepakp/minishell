/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbecker <kbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 11:56:16 by kbecker           #+#    #+#             */
/*   Updated: 2025/12/07 17:43:17 by kbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	delete_env_entries(t_env *env, char **args)
{
	while (*args)
		delete_env_entry(env, *args++);
	return (EXIT_SUCCESS);
}

int	builtin_unset(t_shell *shell, t_command *cmd)
{
	t_env	*env;

	env = shell->env;
	delete_env_entries(env, cmd->args);
	return (EXIT_SUCCESS);
}
