/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naperisw <naperisw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:25:57 by kbecker           #+#    #+#             */
/*   Updated: 2026/01/08 16:17:55 by naperisw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	int		ret;

	shell = (t_shell *)malloc(sizeof(t_shell));
	if (!shell)
		return (perror(ERR_MSG), set_error(shell, NULL), EXIT_FAILURE);
	if (check_input(shell, argc, argv) == EXIT_FAILURE)
		return (free_shell(shell), EXIT_FAILURE);
	init_shell(shell, argc, argv, envp);
	while (1)
	{
		ret = read_input(shell);
		if (ret == EXIT_SHELL)
			break ;
	}
	ret = shell->last_status;
	free_shell(shell);
	return (ret);
}
