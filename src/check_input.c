/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbecker <kbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 13:24:24 by kbecker           #+#    #+#             */
/*   Updated: 2025/12/06 11:02:03 by kbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_input(t_shell *shell, int argc, char **argv)
{
	(void)argv;
	(void)shell;
	if (argc != 1)
		return (set_error(shell, ERR_WRONG_INPUT), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
