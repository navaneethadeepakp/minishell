/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naperisw <naperisw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 22:03:32 by naperisw          #+#    #+#             */
/*   Updated: 2026/02/01 18:23:02 by naperisw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	append_heredoc_part(t_shell *shell, char *line, int i, char **out)
{
	char	*tmp;
	char	*end;
	char	*expanded;

	if (line[i] == '$')
	{
		expanded = expand_var(shell, &line[i], &end);
		if (!expanded)
			return (-1);
		tmp = *out;
		*out = ft_strnjoin(*out, expanded, ft_strlen(expanded), tmp);
		free(expanded);
		if (!*out)
			return (-1);
		return (i + (end - &line[i]));
	}
	tmp = *out;
	*out = ft_strnjoin(*out, &line[i], 1, tmp);
	if (!*out)
		return (-1);
	return (i + 1);
}

char	*expand_line_heredoc(t_shell *shell, char *line)
{
	char	*out;
	int		i;

	out = strdup("");
	if (!out)
		return (NULL);
	i = 0;
	while (line[i])
	{
		i = append_heredoc_part(shell, line, i, &out);
		if (i < 0)
			return (free(out), NULL);
	}
	return (out);
}

void	write_heredoc_line(t_shell *shell, t_redirect *redirect,
			int write_end, char *line)
{
	char	*expanded;

	if (redirect->expand_heredoc)
	{
		expanded = expand_line_heredoc(shell, line);
		free(line);
		if (!expanded)
			exit(EXIT_FAILURE);
		write(write_end, expanded, ft_strlen(expanded));
		write(write_end, "\n", 1);
		free(expanded);
	}
	else
	{
		write(write_end, line, ft_strlen(line));
		write(write_end, "\n", 1);
		free(line);
	}
}

void	close_heredoc_fd(t_command *cmd)
{
	t_redirect	*redirect;

	redirect = cmd->redirects;
	while (redirect)
	{
		if (redirect->type == REDIRECT_HEREDOC && redirect->heredoc_fd >= 0)
		{
			close(redirect->heredoc_fd);
			redirect->heredoc_fd = -1;
		}
		redirect = redirect->next;
	}
}

int	redirect_heredoc(t_redirect *redirect)
{
	int	fd;

	if (!redirect)
		return (EXIT_FAILURE);
	fd = redirect->heredoc_fd;
	if (fd < 0)
		return (EXIT_FAILURE);
	if (fd != STDIN_FILENO)
	{
		if (dup2(fd, STDIN_FILENO) < 0)
		{
			perror("dup2");
			close(fd);
			redirect->heredoc_fd = -1;
			return (EXIT_FAILURE);
		}
		close(fd);
	}
	redirect->heredoc_fd = -1;
	return (EXIT_SUCCESS);
}
