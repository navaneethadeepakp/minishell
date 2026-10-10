/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_syntax_error.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naperisw <naperisw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 17:13:13 by naperisw          #+#    #+#             */
/*   Updated: 2026/01/09 18:58:27 by naperisw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ends_with_pipe(char	*str)
{
	int		i;
	char	*s;

	if (!str)
		return (0);
	s = skip_spaces(str);
	if (*s == '|')
		return (0);
	i = (int)ft_strlen(str);
	while (i > 0 && (str[i - 1] == ' ' || (str[i - 1] >= 9
				&& str[i - 1] <= 13)))
		i--;
	return (i > 0 && str[i - 1] == '|');
}

static int	handle_pipe_error(char *ptr, t_command *cmd, int *status)
{
	char	*s;

	if (!ptr || !status)
		return (0);
	s = skip_spaces(ptr);
	if (*s != '|')
		return (0);
	if (s[0] == '|' && s[1] == '|')
		ft_putstr_fd(COLOR_RED
			"minishell: syntax error near unexpected token `||'\n"COLOR_RESET,
			STDERR_FILENO);
	else
		ft_putstr_fd(COLOR_RED
			"minishell: syntax error near unexpected token `|'\n"COLOR_RESET,
			STDERR_FILENO);
	if (status)
		*status = 2;
	if (cmd)
		free_commands(get_first_cmd(cmd));
	return (1);
}

static int	handle_quotes_error(char *input, int *status)
{
	int		i;
	char	q;

	if (!input || !status)
		return (0);
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			q = input[i++];
			while (input[i] && input[i] != q)
				i++;
			if (!input[i])
			{
				ft_putstr_fd(COLOR_RED
					"minishell: syntax error: unclosed quote\n"COLOR_RESET,
					STDERR_FILENO);
				return (*status = 2, 1);
			}
		}
		if (input[i])
			i++;
	}
	return (0);
}

int	handle_syntax_error(t_command *cmd, char *input, char *ptr, int *status)
{
	char	*s;
	char	*start;

	if (!input || !status)
		return (0);
	s = skip_spaces(ptr);
	start = skip_spaces(input);
	if (cmd == NULL && s == start)
	{
		if (handle_quotes_error(input, status))
			return (1);
	}
	if (handle_pipe_error(s, cmd, status))
		return (1);
	return (0);
}
