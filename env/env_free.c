/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbecker <kbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 11:58:03 by kbecker           #+#    #+#             */
/*   Updated: 2025/12/06 11:58:49 by kbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	free_env(t_env *env)
{
	int	i;

	if (env)
	{
		if (env->env_entries)
		{
			i = 0;
			while (env->env_entries[i])
			{
				free(env->env_entries[i]);
				i++;
			}
			free(env->env_entries);
		}
		free(env);
	}
}
