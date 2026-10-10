/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbecker <kbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 11:55:24 by kbecker           #+#    #+#             */
/*   Updated: 2025/12/10 11:13:36 by kbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(t_shell *shell, t_command *cmd)
{
	char	*cwd;

	(void)shell;
	(void)cmd;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (perror(CMD_PWD), EXIT_FAILURE);
	ft_putendl_fd(cwd, STDOUT_FILENO);
	free(cwd);
	return (EXIT_SUCCESS);
}
