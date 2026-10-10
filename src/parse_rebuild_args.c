/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rebuild_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbecker <kbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 18:16:20 by kbecker           #+#    #+#             */
/*   Updated: 2026/01/20 19:43:39 by kbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	find_first_nonempty_cmd(t_command *cmd)
{
	int	i;

	free(cmd->command_name);
	cmd->command_name = NULL;
	if (!cmd->args)
		return (-1);
	i = 0;
	while (cmd->args[i])
	{
		if (cmd->args[i][0] != '\0')
		{
			cmd->command_name = ft_strdup(cmd->args[i]);
			return (i + 1);
		}
		i++;
	}
	return (-1);
}

void	rebuild_args_after_expansion(t_command *cmd)
{
	char	**new_args;
	int		i;
	int		j;

	i = 0;
	if (cmd->command_name && cmd->command_name[0] == '\0')
		i = find_first_nonempty_cmd(cmd);
	if (!cmd->args || i < 0)
		return ;
	new_args = malloc(sizeof(char *) * (cmd->number_args + 1));
	if (!new_args)
		return ;
	j = 0;
	while (cmd->args[i])
	{
		if (cmd->args[i][0] != '\0')
			new_args[j++] = cmd->args[i];
		i++;
	}
	new_args[j] = NULL;
	free(cmd->args);
	cmd->args = new_args;
	cmd->number_args = j;
}
