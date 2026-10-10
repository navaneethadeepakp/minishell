/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naperisw <naperisw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 11:35:00 by kbecker           #+#    #+#             */
/*   Updated: 2026/01/16 13:53:30 by kbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	update_and_parse(t_shell *shell, char *input)
{
	int	syntax_err;

	syntax_err = -1;
	if (shell->is_interactive && input && *skip_spaces(input))
		add_history(input);
	shell->commands = parse_input(input, &syntax_err);
	if (!shell->commands)
	{
		if (syntax_err != -1)
			shell->last_status = syntax_err;
		return (0);
	}
	return (1);
}

static char	*read_input_with_prompt(t_shell *shell)
{
	char	*input;
	char	*prompt;

	init_signals(shell);
	prompt = display_prompt(shell);
	input = readline(prompt);
	free(prompt);
	if (g_sig == SIGINT)
	{
		shell->last_status = 128 + SIGINT;
		g_sig = 0;
	}
	return (input);
}

static char	*read_input_from_fd(int fd)
{
	char	*line;
	char	*tmp;
	char	c;
	int		len;
	int		bytes_read;

	line = ft_strdup("");
	if (!line)
		return (NULL);
	len = 0;
	while (1)
	{
		bytes_read = read(fd, &c, 1);
		if (bytes_read <= 0 || c == '\n')
			break ;
		tmp = line;
		line = ft_strnjoin(line, &c, 1, tmp);
		if (!line)
			return (NULL);
		len++;
	}
	if (bytes_read < 0 || (bytes_read == 0 && len == 0))
		return (free(line), NULL);
	return (line);
}

static char	*read_initial_prompt(t_shell *shell)
{
	if (shell->is_interactive)
		return (read_input_with_prompt(shell));
	return (read_input_from_fd(STDIN_FILENO));
}

int	read_input(t_shell *shell)
{
	char	*input;
	int		ret;

	input = read_initial_prompt(shell);
	if (!input)
		return (EXIT_SHELL);
	if (!update_and_parse(shell, input))
		return (free(input), EXIT_SUCCESS);
	ret = exec_and_cleanup(shell);
	free(input);
	if (ret == EXIT_SHELL)
		return (EXIT_SHELL);
	return (EXIT_SUCCESS);
}
