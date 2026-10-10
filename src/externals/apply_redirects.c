/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naperisw <naperisw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 19:58:17 by naperisw          #+#    #+#             */
/*   Updated: 2026/01/04 22:25:34 by naperisw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_input(t_redirect *redirect)
{
	int	fd;

	fd = open(redirect->filename, O_RDONLY);
	if (fd < 0)
		return (perror(redirect->filename), EXIT_FAILURE);
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		close(fd);
		return (perror("dup2"), EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

int	redirect_output(t_redirect *redirect)
{
	int	fd;

	fd = open(redirect->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (perror(redirect->filename), EXIT_FAILURE);
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		close(fd);
		return (perror("dup2"), EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

int	redirect_append(t_redirect *redirect)
{
	int	fd;

	fd = open(redirect->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (perror(redirect->filename), EXIT_FAILURE);
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		close(fd);
		return (perror("dup2"), EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

static int	handle_redirects(t_redirect *redirect)
{
	if (!redirect)
		return (EXIT_FAILURE);
	if (redirect->type == REDIRECT_IN)
		return (redirect_input(redirect));
	if (redirect->type == REDIRECT_OUT)
		return (redirect_output(redirect));
	if (redirect->type == REDIRECT_APPEND)
		return (redirect_append(redirect));
	if (redirect->type == REDIRECT_HEREDOC)
		return (redirect_heredoc(redirect));
	return (EXIT_FAILURE);
}

int	redirects_apply(t_command *cmd)
{
	t_redirect	*redirect;

	redirect = cmd->redirects;
	while (redirect)
	{
		if (handle_redirects(redirect) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		redirect = redirect->next;
	}
	return (EXIT_SUCCESS);
}
