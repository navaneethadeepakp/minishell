/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naperisw <naperisw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:30:13 by kbecker           #+#    #+#             */
/*   Updated: 2026/01/06 15:14:29 by naperisw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	**parse_arguments(char *cmd_line, int *no_of_args)
{
	char	**args;
	char	*ptr;
	char	quote_char;
	int		i;

	*no_of_args = no_of_arguments(cmd_line);
	args = (char **)malloc(sizeof(char *) * (*no_of_args + 1));
	if (!args)
		return (NULL);
	ptr = skip_spaces(cmd_line);
	i = 0;
	while (*ptr && i < *no_of_args)
	{
		args[i] = get_token(ptr, find_end_of_token(ptr, &quote_char));
		if (!args[i])
			return (free_args(args, i), NULL);
		ptr = skip_spaces(find_end_of_token(ptr, &quote_char));
		i++;
	}
	args[i] = NULL;
	return (args);
}

char	**copy_args(t_command *cmd, char **src, int no_of_args,
				int no_of_redirects)
{
	char	**dst;
	int		i;

	cmd->command_name = NULL;
	dst = (char **)malloc(sizeof(char *) * (no_of_args - no_of_redirects + 1));
	if (!dst)
		return (NULL);
	i = 0;
	cmd->number_args = 0;
	while (i < no_of_args)
	{
		if (src[i] && src[i][0] != '\0')
		{
			if (!cmd->command_name)
				cmd->command_name = ft_strdup(src[i]);
			else
				dst[cmd->number_args++] = ft_strdup(src[i]);
		}
		i++;
	}
	dst[cmd->number_args] = NULL;
	return (dst);
}

int	set_args(t_command *cmd, char **args, int no_of_args, int *status)
{
	int	no_of_redirects;

	no_of_redirects = extract_redirects(cmd, args, no_of_args, status);
	if (no_of_redirects < 0)
		return (free_token(args), EXIT_FAILURE);
	cmd->number_args = no_of_args;
	no_of_args = no_of_args - no_of_redirects;
	if (no_of_args > 0)
		cmd->args = copy_args(cmd, args, cmd->number_args, no_of_redirects);
	else
		cmd->args = NULL;
	free_token(args);
	return (EXIT_SUCCESS);
}

int	no_of_arguments(char *cmd_line)
{
	int		count;
	char	*ptr;
	char	quote_char;

	count = 0;
	ptr = skip_spaces(cmd_line);
	while (*ptr)
	{
		count++;
		ptr = find_end_of_token(ptr, &quote_char);
		ptr = skip_spaces(ptr);
	}
	return (count);
}

void	free_args(char **args, int i)
{
	while (--i >= 0)
		free(args[i]);
	free(args);
}
