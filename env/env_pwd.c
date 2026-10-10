/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbecker <kbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 12:25:53 by kbecker           #+#    #+#             */
/*   Updated: 2025/12/10 10:48:09 by kbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	update_pwd(t_env *env, char *new_pwd)
{
	if (!env || !new_pwd)
		return ;
	add_or_update_by_keyname(env, KEYNAME_PWD, new_pwd);
}

void	update_oldpwd(t_env *env, char *new_oldpwd)
{
	if (!env || !new_oldpwd)
		return ;
	add_or_update_by_keyname(env, KEYNAME_OLDPWD, new_oldpwd);
}

void	update_pwd_and_oldpwd(t_env *env, char *new_pwd, char *new_oldpwd)
{
	update_pwd(env, new_pwd);
	update_oldpwd(env, new_oldpwd);
}

char	*get_pwd_ptr(t_env *env)
{
	if (!env)
		return (NULL);
	return (set_ptr2value(env->env_entries, KEYNAME_PWD));
}
