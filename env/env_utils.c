/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbecker <kbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 14:08:39 by kbecker           #+#    #+#             */
/*   Updated: 2026/01/10 12:30:46 by kbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	**get_env_entry(t_env *env_entries, char *keyname)
{
	int		i;
	size_t	key_len;

	key_len = ft_strlen(keyname);
	i = 0;
	while (env_entries->env_entries[i])
	{
		if (ft_strncmp(env_entries->env_entries[i], keyname, key_len) == 0)
			return (&(env_entries->env_entries[i]));
		i++;
	}
	return (NULL);
}

char	*set_ptr2value(char **env_entries, const char *keyname)
{
	char	*ptr;
	int		key_len;
	int		i;

	ptr = NULL;
	i = 0;
	while (env_entries[i])
	{
		key_len = ft_strlen(keyname);
		if (ft_strncmp(env_entries[i], keyname, key_len) == 0
			&& (env_entries[i][key_len] == '='
			|| ft_strncmp(keyname + key_len - 1, "=", 1) == 0))
		{
			ptr = env_entries[i] + key_len;
			if (!ptr)
				ptr = NULL;
			if (*ptr == '=' && keyname[key_len - 1] != '=')
				ptr++;
			return (ptr);
		}
		i++;
	}
	return (NULL);
}

int	get_no_of_env_entries(char **env_entries)
{
	int	count;

	count = 0;
	while (env_entries[count])
		count++;
	return (count);
}
