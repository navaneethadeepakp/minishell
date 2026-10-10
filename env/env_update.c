/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbecker <kbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 11:55:35 by kbecker           #+#    #+#             */
/*   Updated: 2025/12/06 12:20:25 by kbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static int	split_arg(char *env_entry, char **keyname, char **value)
{
	char	*equal_sign_ptr;

	equal_sign_ptr = ft_strchr(env_entry, '=');
	if (!equal_sign_ptr)
		return (-1);
	else
	{
		*keyname = ft_substr(env_entry, 0, equal_sign_ptr - env_entry);
		if (!*keyname)
			return (perror(ENV_ERR_MSG), EXIT_FAILURE);
		*value = ft_strdup(equal_sign_ptr + 1);
		if (!*value)
			return (free(*keyname), perror(ENV_ERR_MSG), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	update_env_entry(char **env_entries, char *value)
{
	char	*new_entry;

	new_entry = ft_strdup(value);
	if (!new_entry)
		return (perror(ENV_ERR_MSG), EXIT_FAILURE);
	free(*env_entries);
	*env_entries = new_entry;
	return (EXIT_SUCCESS);
}

static int	create_env_entry(t_env *env, char *env_entry)
{
	int		i;
	int		count;
	char	**new_env_entries;
	char	*new_env_entry;

	new_env_entry = ft_strdup(env_entry);
	if (!new_env_entry)
		return (perror(ENV_ERR_MSG), EXIT_FAILURE);
	count = 0;
	while (env->env_entries[count])
		count++;
	new_env_entries = malloc(sizeof(char *) * (count + 2));
	if (!new_env_entries)
		return (free(new_env_entry), perror(ENV_ERR_MSG), EXIT_FAILURE);
	i = -1;
	while (++i < count)
		new_env_entries[i] = env->env_entries[i];
	new_env_entries[count] = new_env_entry;
	new_env_entries[count + 1] = NULL;
	free(env->env_entries);
	env->env_entries = new_env_entries;
	return (EXIT_SUCCESS);
}

int	add_or_update_by_entry(t_env *env, char *env_entry)
{
	char	*keyname;
	char	*value;
	char	**ptr;

	if (split_arg(env_entry, &keyname, &value) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ptr = get_env_entry(env, keyname);
	if (ptr == NULL)
		create_env_entry(env, env_entry);
	else
		if (update_env_entry(ptr, env_entry) == EXIT_FAILURE)
			return (free(keyname), free(value), EXIT_FAILURE);
	free(keyname);
	free(value);
	return (EXIT_SUCCESS);
}

int	add_or_update_by_keyname(t_env *env, char *keyname, char *value)
{
	char	**ptr;
	char	*env_entry;

	env_entry = ft_strjoin(keyname, value);
	if (!env_entry)
		return (perror(ENV_ERR_MSG), EXIT_FAILURE);
	ptr = get_env_entry(env, keyname);
	if (ptr == NULL)
		create_env_entry(env, env_entry);
	else
		if (update_env_entry(ptr, env_entry) == EXIT_FAILURE)
			return (free(keyname), free(value), EXIT_FAILURE);
	free(env_entry);
	return (EXIT_SUCCESS);
}
