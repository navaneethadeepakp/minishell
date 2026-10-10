/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_home.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbecker <kbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 09:55:05 by kbecker           #+#    #+#             */
/*   Updated: 2025/12/10 10:24:29 by kbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	*get_home_dir_ptr(t_env *env)
{
	char	*home_dir;

	home_dir = set_ptr2value(env->env_entries, KEYNAME_HOME);
	return (home_dir);
}

int	change_to_home_dir(t_env *env)
{
	char	*home_dir;

	home_dir = get_home_dir_ptr(env);
	if (!home_dir)
		return (EXIT_FAILURE);
	if (chdir(home_dir) != 0)
		return (EXIT_FAILURE);
	update_pwd(env, home_dir);
	return (EXIT_SUCCESS);
}
