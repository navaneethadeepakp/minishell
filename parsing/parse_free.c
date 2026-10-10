/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbecker <kbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 13:39:02 by kbecker           #+#    #+#             */
/*   Updated: 2025/12/13 16:22:48 by kbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	free_redirects(t_redirect *redirect)
{
	t_redirect	*next_redirect;

	if (!redirect)
		return ;
	while (redirect)
	{
		next_redirect = redirect->next;
		if (redirect->filename)
			free(redirect->filename);
		free(redirect);
		redirect = next_redirect;
	}
}

void	free_commands(t_command *cmd)
{
	t_command	*next_cmd;
	int			i;

	while (cmd)
	{
		next_cmd = cmd->next;
		if (cmd->command_line)
			free(cmd->command_line);
		if (cmd->command_name)
			free(cmd->command_name);
		if (cmd->args)
		{
			i = -1;
			while (++i < cmd->number_args)
			{
				if (cmd->args[i])
					free(cmd->args[i]);
			}
			free(cmd->args);
		}
		free_redirects(cmd->redirects);
		free(cmd);
		cmd = next_cmd;
	}
}

void	free_token(char **token)
{
	int	i;

	if (!token)
		return ;
	i = -1;
	while (token && token[++i])
		free(token[i]);
	free(token);
}
