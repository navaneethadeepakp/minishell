/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_shlvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbecker <kbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 12:29:39 by kbecker           #+#    #+#             */
/*   Updated: 2025/12/18 10:01:23 by kbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	incr_shlvl(t_env *env, int is_interactive)
{
	char	*shlvl_ptr;
	char	*shlvl_value;
	int		shlvl_idx;

	if (!is_interactive)
		return ;
	shlvl_idx = 0;
	shlvl_ptr = set_ptr2value(env->env_entries, KEYNAME_SHLVL);
	if (shlvl_ptr)
		shlvl_idx = ft_atoi(shlvl_ptr);
	shlvl_idx++;
	if (shlvl_idx > 999)
		shlvl_idx = 1;
	shlvl_value = ft_itoa(shlvl_idx);
	if (!shlvl_value)
		return ;
	add_or_update_by_keyname(env, KEYNAME_SHLVL, shlvl_value);
	free(shlvl_value);
}
