/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbecker <kbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 11:17:32 by kbecker           #+#    #+#             */
/*   Updated: 2025/12/18 10:02:30 by kbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# define KEYNAME_PWD "PWD="
# define KEYNAME_OLDPWD "OLDPWD="
# define KEYNAME_HOME "HOME="
# define KEYNAME_SHLVL "SHLVL="
# define KEYNAME_PATH "PATH="
# define KEYNAME_USER "USER="
# define KEYNAME_LAST_CMD "_="

# define DEFAULT_PATH "/usr/local/sbin:/usr/bin:/bin"
# define ENV_ERR_MSG "Environment Error: "

# include <stdio.h>
# include "../libft/libft.h"

typedef struct s_env
{
	char		**env_entries;
}	t_env;

//env_delete.c
void		delete_env_entry(t_env *env_entries, char *keyname);

//env_free.c
void		free_env(t_env *env);

//env/env_home.c
char		*get_home_dir_ptr(t_env *env);
int			change_to_home_dir(t_env *env);
//env_init.c
t_env		*init_env(int argc, char **argv, char **envp, int is_interactive);

//env_pwd.c
void		update_pwd(t_env *env, char *new_pwd);
void		update_oldpwd(t_env *env, char *new_oldpwd);
void		update_pwd_and_oldpwd(t_env *env, char *new_pwd, char *new_oldpwd);
char		*get_pwd_ptr(t_env *env);

//env_shlvl.c
void		incr_shlvl(t_env *env, int is_interactive);

//env_update.c
int			add_or_update_by_entry(t_env *env_entries, char *arg);
int			add_or_update_by_keyname(t_env *env, char *keyname, char *value);

//env_utils.c
int			get_no_of_env_entries(char **env_entries);
char		*set_ptr2value(char **env_entries, const char *keyname);
char		**get_env_entry(t_env *env, char *keyname);

#endif