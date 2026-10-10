/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naperisw <naperisw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:00:00 by kbecker           #+#    #+#             */
/*   Updated: 2026/01/01 19:14:39 by naperisw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	get_no_of_commands(t_command *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

char	*get_command_line(char **input_ptr)
{
	char	*start;
	char	*end;
	char	*ptr;
	char	quote_char;

	ptr = skip_spaces(*input_ptr);
	start = ptr;
	while (*ptr && *ptr != '|')
	{
		ptr = find_end_of_token(ptr, &quote_char);
		ptr = skip_spaces(ptr);
	}
	end = ptr;
	while (end > start && (*(end - 1) == ' '
			|| (*(end - 1) >= 9 && *(end - 1) <= 13)))
		end--;
	if (*ptr == '|')
		ptr++;
	*input_ptr = ptr;
	return (get_token(start, end));
}

static int	init_cmd(t_command *cmd, int idx, const char *cmd_line)
{
	cmd->command_line = ft_strdup(cmd_line);
	if (!cmd->command_line)
		return (EXIT_FAILURE);
	cmd->idx = idx;
	cmd->command_name = NULL;
	cmd->args = NULL;
	cmd->number_args = 0;
	cmd->redirects = NULL;
	cmd->next = NULL;
	return (EXIT_SUCCESS);
}

t_command	*create_command(t_command *prev_cmd, char *cmd_line,
			int idx, int *status)
{
	t_command	*cmd;
	char		**args;
	int			no_of_args;

	cmd = (t_command *)malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	if (init_cmd(cmd, idx, cmd_line) == EXIT_FAILURE)
		return (free(cmd), NULL);
	args = parse_arguments(cmd_line, &no_of_args);
	if (!args || !args[0])
	{
		if (args)
			free_token(args);
		return (free(cmd->command_line), free(cmd), NULL);
	}
	if (set_args(cmd, args, no_of_args, status) == EXIT_FAILURE)
		return (free_commands(cmd), NULL);
	cmd->prev = prev_cmd;
	return (cmd);
}
