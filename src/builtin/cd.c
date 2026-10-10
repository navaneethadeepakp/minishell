/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   cd.c											   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: kbecker <kbecker@student.42.fr>			+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/12/04 11:55:16 by kbecker		   #+#	#+#			 */
/*   Updated: 2025/12/05 14:53:09 by kbecker		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"

int	builtin_cd(t_shell *shell, t_command *cmd)
{
	t_env	*env;
	char	*path;
	char	*pwd;
	char	*old_pwd;

	if (cmd->number_args > 1)
		return (show_indiv_error(shell, CMD_CD, NULL, ERR_TOO_MANY_ARGS));
	env = shell->env;
	if (cmd->args && cmd->args[0])
		path = cmd->args[0];
	else
		path = get_home_dir_ptr(env);
	old_pwd = ft_strdup(get_pwd_ptr(env));
	if (chdir(path) == -1)
		return (perror(cmd->command_name), free(old_pwd), EXIT_FAILURE);
	pwd = getcwd(NULL, 0);
	update_pwd_and_oldpwd(env, pwd, old_pwd);
	free(pwd);
	free(old_pwd);
	return (EXIT_SUCCESS);
}
