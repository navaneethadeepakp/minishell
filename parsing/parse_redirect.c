/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naperisw <naperisw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 14:02:34 by kbecker           #+#    #+#             */
/*   Updated: 2026/02/01 17:56:48 by naperisw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	is_redirect_token(char *token)
{
	return (strcmp(token, ">") == 0 || strcmp(token, ">>") == 0
		|| strcmp(token, "<") == 0 || strcmp(token, "<<") == 0);
}

static int	create_redirect(char **type_str, char **filename,
		t_redirect *redirect)
{
	if (strcmp(*type_str, ">") == 0)
		redirect->type = REDIRECT_OUT;
	else if (strcmp(*type_str, ">>") == 0)
		redirect->type = REDIRECT_APPEND;
	else if (strcmp(*type_str, "<") == 0)
		redirect->type = REDIRECT_IN;
	else if (strcmp(*type_str, "<<") == 0)
		redirect->type = REDIRECT_HEREDOC;
	else
		return (0);
	if (redirect->type == REDIRECT_HEREDOC)
	{
		redirect->expand_heredoc = !has_quotes_heredoc(*filename);
		redirect->filename = remove_quotes(*filename);
	}
	else
		redirect->filename = ft_strdup(*filename);
	redirect->next = NULL;
	*type_str[0] = '\0';
	if (redirect->filename == NULL)
		return (1);
	*filename[0] = '\0';
	return (2);
}

static void	add_redirect(t_command *cmd, t_redirect *new_redirect)
{
	t_redirect	*current;

	if (cmd->redirects == NULL)
	{
		cmd->redirects = new_redirect;
		return ;
	}
	current = cmd->redirects;
	while (current->next != NULL)
		current = current->next;
	current->next = new_redirect;
}

int	extract_redirects(t_command *cmd, char **args, int no_of_args, int *status)
{
	t_redirect		*redirects;
	int				i;
	int				no_of_redirects;
	int				total_no_of_redirects;

	total_no_of_redirects = 0;
	i = -1;
	while (++i < no_of_args)
	{
		if (is_redirect_token(args[i]))
		{
			if (i + 1 >= no_of_args || !args[i + 1])
				return (*status = 2,
					ft_putstr_fd(REDIRECT_ERR_MSG, STDERR_FILENO), -1);
			redirects = (t_redirect *)malloc(sizeof(t_redirect));
			if (!redirects)
				return (-1);
			no_of_redirects = create_redirect(&args[i], &args[i + 1],
					redirects);
			add_redirect(cmd, redirects);
			total_no_of_redirects += no_of_redirects;
			i += (no_of_redirects - 1);
		}
	}
	return (total_no_of_redirects);
}
