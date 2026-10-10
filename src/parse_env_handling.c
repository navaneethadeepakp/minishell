/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env_handling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naperisw <naperisw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 18:16:20 by kbecker           #+#    #+#             */
/*   Updated: 2026/02/01 18:51:55 by naperisw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*expand_var(t_shell *shell, char *start, char **end)
{
	char	*var_name;
	char	*var_value;
	char	*result;

	*end = start + 1;
	if (**end == '?')
	{
		(*end)++;
		result = ft_itoa(shell->last_status);
		return (result);
	}
	while (**end && (ft_isalnum(**end) || **end == '_'))
		(*end)++;
	if (*end == start + 1)
		return (ft_strdup("$"));
	var_name = ft_substr(start + 1, 0, *end - start - 1);
	var_value = set_ptr2value(shell->env->env_entries, var_name);
	if (var_value)
		result = ft_strdup(var_value);
	else
		result = ft_strdup("");
	return (free(var_name), result);
}

static char	*find_end(char *start, int single_quote, int double_quote)
{
	char	*end;

	end = start;
	if (!single_quote && !double_quote)
	{
		while (*end && *end != '$' && *end != '\'' && *end != '"')
			end++;
	}
	else if (single_quote)
	{
		while (*end && *end != '\'')
			end++;
	}
	else if (double_quote)
	{
		while (*end && *end != '$' && *end != '"')
			end++;
	}
	return (end);
}

static void	handle_char(t_shell *shell, char **arg, char **s, int *q)
{
	char	*end;
	char	*expanded;

	if (**s == '\'' || **s == '"')
	{
		if (**s == '\'' && !q[1])
			q[0] = !q[0];
		else if (**s == '"' && !q[0])
			q[1] = !q[1];
		else
			*arg = ft_strnjoin(*arg, *s, 1, *arg);
		(*s)++;
		return ;
	}
	if (**s == '$' && !q[0])
	{
		expanded = expand_var(shell, *s, &end);
		*arg = ft_strnjoin(*arg, expanded, ft_strlen(expanded), *arg);
		free(expanded);
		*s = end;
		return ;
	}
	end = find_end(*s, q[0], q[1]);
	*arg = ft_strnjoin(*arg, *s, end - *s, *arg);
	*s = end;
}

static char	*check_arg(t_shell *shell, char *str)
{
	char	*new_arg;
	char	*str_cpy;
	int		q[2];

	new_arg = ft_strdup("");
	str_cpy = str;
	q[0] = 0;
	q[1] = 0;
	while (*str_cpy)
		handle_char(shell, &new_arg, &str_cpy, q);
	free(str);
	return (new_arg);
}

void	check_env_vars(t_shell *shell)
{
	t_command	*cmd;
	t_redirect	*redirect;
	int			i;

	cmd = shell->commands;
	while (cmd)
	{
		if (cmd->command_name)
			cmd->command_name = check_arg(shell, cmd->command_name);
		i = -1;
		while (cmd->args && cmd->args[++i])
			cmd->args[i] = check_arg(shell, cmd->args[i]);
		rebuild_args_after_expansion(cmd);
		redirect = cmd->redirects;
		while (redirect)
		{
			redirect->filename = check_arg(shell, redirect->filename);
			redirect = redirect->next;
		}
		cmd = cmd->next;
	}
}
