/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbecker <kbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 18:36:05 by naperisw          #+#    #+#             */
/*   Updated: 2026/02/02 12:59:53 by kbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*format_path_to_display(char *home, char *cwd)
{
	size_t	i;
	size_t	home_len;
	char	*display;

	i = 1;
	if (!cwd)
		return (display = ft_strdup("?"), display);
	if (home && ft_strncmp(cwd, home, ft_strlen(home)) == 0)
	{
		home_len = ft_strlen(home);
		display = (char *)malloc((ft_strlen(cwd) - home_len + 2)
				* sizeof(char));
		if (!display)
			return (NULL);
		display[0] = '~';
		while (cwd[home_len])
			display[i++] = cwd[home_len++];
		display[i] = '\0';
	}
	else
		display = ft_strdup(cwd);
	return (display);
}

static char	*get_cwd_to_display(char **env_entries)
{
	char	*cwd;
	char	*home_ptr;
	char	*pwd_ptr;
	char	*display;

	home_ptr = set_ptr2value(env_entries, KEYNAME_HOME);
	pwd_ptr = set_ptr2value(env_entries, KEYNAME_PWD);
	if (pwd_ptr && *pwd_ptr)
		cwd = ft_strdup(pwd_ptr);
	else
		cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	display = format_path_to_display(home_ptr, cwd);
	free(cwd);
	return (display);
}

static char	*add_to_prompt(char *prompt, char *new_value)
{
	char	*new_prompt;

	if (!new_value)
		return (prompt);
	new_prompt = ft_strjoin(prompt, new_value);
	if (!new_prompt)
		return (prompt);
	free(prompt);
	return (new_prompt);
}

char	*display_prompt(t_shell *shell)
{
	char	*user_ptr;
	char	*cwd;
	char	*prompt;

	user_ptr = set_ptr2value(shell->env->env_entries, KEYNAME_USER);
	cwd = get_cwd_to_display(shell->env->env_entries);
	prompt = ft_strdup("");
	if (!prompt)
		return (free(cwd), NULL);
	prompt = add_to_prompt(prompt, RL_BOLD);
	prompt = add_to_prompt(prompt, RL_COLOR_GREEN);
	if (user_ptr)
		prompt = add_to_prompt(prompt, user_ptr);
	else
		prompt = add_to_prompt(prompt, "?");
	prompt = add_to_prompt(prompt, "@minishell:");
	prompt = add_to_prompt(prompt, RL_COLOR_BLUE);
	prompt = add_to_prompt(prompt, cwd);
	prompt = add_to_prompt(prompt, "$ ");
	prompt = add_to_prompt(prompt, RL_COLOR_RESET);
	if (cwd)
		free(cwd);
	if (prompt == NULL)
		return (NULL);
	return (prompt);
}
