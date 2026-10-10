/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naperisw <naperisw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 12:36:41 by kbecker           #+#    #+#             */
/*   Updated: 2026/01/09 18:48:21 by naperisw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_command	*get_first_cmd(t_command *cmd)
{
	t_command	*prev_cmd;

	while (cmd && cmd->prev)
	{
		prev_cmd = cmd->prev;
		cmd = prev_cmd;
	}
	return (cmd);
}

void	set_next_cmd(t_command *prev_cmd, t_command *cmd)
{
	if (prev_cmd)
		prev_cmd->next = cmd;
}

static int	get_next_idx(t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->prev;
	}
	return (i);
}

static	t_command	*parse_next_command(t_command *cmd, char **ptr,
					int *status, char *input)
{
	t_command	*prev_cmd;
	char		*cmd_line;
	int			idx;

	*ptr = skip_spaces(*ptr);
	if (handle_syntax_error(cmd, input, *ptr, status))
		return (NULL);
	cmd_line = get_command_line(ptr);
	if (!cmd_line)
		return (*status = 1, perror(PARSE_ERR_MSG), NULL);
	prev_cmd = cmd;
	idx = get_next_idx(prev_cmd);
	cmd = create_command(prev_cmd, cmd_line, idx, status);
	free(cmd_line);
	if (!cmd)
	{
		if (prev_cmd)
			free_commands(get_first_cmd(prev_cmd));
		return (NULL);
	}
	set_next_cmd(prev_cmd, cmd);
	*ptr = skip_spaces(*ptr);
	return (cmd);
}

t_command	*parse_input(char *input, int *status)
{
	t_command	*cmd;
	char		*ptr;

	if (status)
		*status = -1;
	if (!input)
		return (NULL);
	ptr = skip_spaces(input);
	if (!*ptr)
		return (NULL);
	if (ends_with_pipe(input))
	{
		ft_putendl_fd("syntax error near unexpected token `|'", STDERR_FILENO);
		if (status)
			*status = 2;
		return (NULL);
	}
	cmd = NULL;
	while (*ptr)
	{
		cmd = parse_next_command(cmd, &ptr, status, input);
		if (!cmd)
			return (NULL);
	}
	return (get_first_cmd(cmd));
}
