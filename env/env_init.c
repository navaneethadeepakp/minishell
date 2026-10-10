/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbecker <kbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 11:40:25 by kbecker           #+#    #+#             */
/*   Updated: 2025/12/18 10:00:28 by kbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static void	check_entry_values(t_env *env)
{
	char	*ptr;

	delete_env_entry(env, KEYNAME_LAST_CMD);
	delete_env_entry(env, KEYNAME_OLDPWD);
	ptr = set_ptr2value(env->env_entries, KEYNAME_PATH);
	if (!ptr)
		add_or_update_by_keyname(env, KEYNAME_PATH, DEFAULT_PATH);
}

static char	**copy_envp(char **envp)
{
	int		i;
	int		count;
	char	**new_env;

	count = get_no_of_env_entries(envp);
	new_env = malloc(sizeof(char *) * (count + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_env[i] = ft_strdup(envp[i]);
		if (!new_env[i])
		{
			while (--i >= 0)
				free(new_env[i]);
			free(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[count] = NULL;
	return (new_env);
}

t_env	*init_env(int argc, char **argv, char **envp, int is_interactive)
{
	t_env	*env;

	(void)argc;
	(void)argv;
	env = malloc(sizeof(t_env));
	if (!env)
		return (perror(ENV_ERR_MSG), NULL);
	env->env_entries = copy_envp(envp);
	change_to_home_dir(env);
	incr_shlvl(env, is_interactive);
	check_entry_values(env);
	return (env);
}
