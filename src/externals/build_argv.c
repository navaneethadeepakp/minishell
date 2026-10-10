/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naperisw <naperisw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 13:57:09 by naperisw          #+#    #+#             */
/*   Updated: 2026/01/09 18:51:35 by naperisw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*search_in_path(char **path, char *cmd)
{
	char	*full;
	char	*tmp;
	int		i;

	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		if (!tmp)
			break ;
		full = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!full)
			break ;
		if (access(full, X_OK) == 0)
			return (free_token(path), full);
		free(full);
		i++;
	}
	free_token(path);
	return (NULL);
}

char	*get_exec_path(t_env *env, char *cmd)
{
	char	*path_env;
	char	**path;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_env = set_ptr2value(env->env_entries, KEYNAME_PATH);
	if (!path_env)
		return (NULL);
	path = ft_split(path_env, ':');
	if (!path)
		return (NULL);
	return (search_in_path(path, cmd));
}

char	**build_argv(t_command *cmd)
{
	char	**argv;
	int		i;

	if (!cmd || !cmd->command_name)
		return (NULL);
	argv = malloc(sizeof(char *) * (cmd->number_args + 2));
	if (!argv)
		return (NULL);
	argv[0] = ft_strdup(cmd->command_name);
	if (!argv[0])
		return (free_token(argv), NULL);
	i = 0;
	while (i < cmd->number_args)
	{
		argv[i + 1] = ft_strdup(cmd->args[i]);
		if (!argv[i + 1])
			return (free_token(argv), NULL);
		i++;
	}
	argv[i + 1] = NULL;
	return (argv);
}

static int	handle_exec_not_found(t_shell *shell, t_command *cmd, char ***argv)
{
	if (ft_strchr(cmd->command_name, '/'))
	{
		if (access(cmd->command_name, F_OK) == 0
			&& access(cmd->command_name, X_OK) != 0)
			shell->last_status = EXIT_CODE_PERMISSION_DENIED;
		else
			shell->last_status = EXIT_CODE_CMD_NOT_FOUND ;
		perror(cmd->command_name);
	}
	else
	{
		if (!set_ptr2value(shell->env->env_entries, KEYNAME_PATH))
		{
			errno = ENOENT;
			perror(cmd->command_name);
		}
		else
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(cmd->command_name, STDERR_FILENO);
			ft_putendl_fd(": command not found", STDERR_FILENO);
		}
		shell->last_status = EXIT_CODE_CMD_NOT_FOUND;
	}
	return (free_token(*argv), *argv = NULL, shell->last_status);
}

int	get_path_and_argv(t_shell *shell, t_command *cmd, char ***argv, char **path)
{
	*argv = build_argv(cmd);
	if (!*argv)
		return (1);
	*path = get_exec_path(shell->env, cmd->command_name);
	if (*path)
		return (0);
	return (handle_exec_not_found(shell, cmd, argv));
}
