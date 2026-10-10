/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbecker <kbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 11:56:05 by kbecker           #+#    #+#             */
/*   Updated: 2026/01/09 12:19:52 by kbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**duplicate_entries(char **array)
{
	char	**copy;
	int		count;
	int		i;

	if (!array)
		return (NULL);
	count = 0;
	while (array[count])
		count++;
	copy = (char **)malloc(sizeof(char *) * (count + 1));
	if (!copy)
		return (NULL);
	i = -1;
	while (++i < count)
	{
		copy[i] = ft_strdup(array[i]);
		if (!copy[i])
		{
			free_token(copy);
			return (NULL);
		}
	}
	copy[count] = NULL;
	return (copy);
}

static char	**sort_entries(t_env *env)
{
	char	**sorted_entries;
	int		i;
	int		j;
	char	*temp;

	sorted_entries = duplicate_entries(env->env_entries);
	if (!sorted_entries)
		return (NULL);
	i = -1;
	while (sorted_entries[++i])
	{
		j = i + 1;
		while (sorted_entries[j])
		{
			if (ft_strcmp(sorted_entries[i], sorted_entries[j]) > 0)
			{
				temp = sorted_entries[i];
				sorted_entries[i] = sorted_entries[j];
				sorted_entries[j] = temp;
			}
			j++;
		}
	}
	return (sorted_entries);
}

static void	print_entry(char *entry)
{
	char	*equal_sign;

	equal_sign = ft_strchr(entry, '=');
	if (!equal_sign)
		return ;
	ft_putstr_fd(MSG_DECLARE_X, STDOUT_FILENO);
	write(STDOUT_FILENO, entry, equal_sign - entry);
	ft_putstr_fd("=\"", STDOUT_FILENO);
	ft_putstr_fd(equal_sign + 1, STDOUT_FILENO);
	ft_putendl_fd("\"", STDOUT_FILENO);
}

static int	print_env_sorted(t_shell *shell)
{
	char	**sorted_entries;
	int		i;

	sorted_entries = sort_entries(shell->env);
	if (!sorted_entries)
		return (set_shell_error(
				shell, ENOMEM, CMD_EXPORT, NULL));
	i = -1;
	while (sorted_entries[++i])
	{
		if (ft_strncmp(sorted_entries[i],
				KEYNAME_LAST_CMD, ft_strlen(KEYNAME_LAST_CMD)) != 0)
			print_entry(sorted_entries[i]);
	}
	free_token(sorted_entries);
	return (EXIT_SUCCESS);
}

int	builtin_env(t_shell *shell, t_command *cmd)
{
	char	**env_entries;

	if (!cmd)
		return (print_env_sorted(shell));
	if (cmd->args && cmd->args[0])
		return (set_shell_error(
				shell, ENOENT, cmd->command_name, cmd->args[0]));
	env_entries = shell->env->env_entries;
	while (env_entries && *env_entries)
	{
		ft_putendl_fd(*env_entries, STDOUT_FILENO);
		env_entries++;
	}
	return (EXIT_SUCCESS);
}
