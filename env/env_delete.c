/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_delete.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbecker <kbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 17:04:32 by kbecker           #+#    #+#             */
/*   Updated: 2025/12/10 11:04:24 by kbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static int	env_entry_found(t_env *env, char *keyname)
{
	char	**ptr;

	ptr = get_env_entry(env, keyname);
	if (ptr)
		return (1);
	return (0);
}

static int	found_env_entry(char *env_entry, char *keyname, int len)
{
	if (len < 1)
		return (0);
	if (keyname[len - 1] == '=')
		len--;
	if (ft_strncmp(env_entry, keyname, len) != 0
		|| env_entry[len] != '=')
		return (0);
	else
		return (1);
}

void	delete_env_entry(t_env *env, char *keyname)
{
	int		i;
	int		j;
	int		key_len;
	int		count;
	char	**new_env;

	if (!env_entry_found(env, keyname))
		return ;
	count = get_no_of_env_entries(env->env_entries);
	new_env = (char **)malloc(sizeof(char *) * (count));
	if (!new_env)
		return ;
	key_len = ft_strlen(keyname);
	i = -1;
	j = 0;
	while (env->env_entries[++i])
	{
		if (found_env_entry(env->env_entries[i], keyname, key_len))
			free(env->env_entries[i]);
		else
			new_env[j++] = env->env_entries[i];
	}
	new_env[j] = NULL;
	free(env->env_entries);
	env->env_entries = new_env;
}
