/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbecker <kbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 11:51:54 by kbecker           #+#    #+#             */
/*   Updated: 2025/12/18 10:13:46 by kbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_shell(t_shell *shell, int argc, char **argv, char **envp)
{
	if (!shell)
		return ;
	ft_memset(shell, 0, sizeof(t_shell));
	shell->is_interactive = isatty(STDIN_FILENO);
	shell->pid = getpid();
	shell->env = init_env(argc, argv, envp, shell->is_interactive);
	if (!shell->env)
		return ;
	init_signals(shell);
}
