/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbecker <kbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 13:08:04 by kbecker           #+#    #+#             */
/*   Updated: 2026/01/15 11:43:09 by kbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_shell(t_shell *shell)
{
	rl_clear_history();
	free_env(shell->env);
	free_commands(shell->commands);
	if (shell)
		free(shell);
	return ;
}
