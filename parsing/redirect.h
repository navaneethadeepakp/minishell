/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naperisw <naperisw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 12:02:49 by kbecker           #+#    #+#             */
/*   Updated: 2026/02/01 17:41:43 by naperisw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

# define REDIRECT_ERR_MSG "Redirect Error - Parameter missing!\n"

//	REDIRECT_IN,		--> <
//	REDIRECT_OUT,		--> >
//	REDIRECT_APPEND,	--> >>
//	REDIRECT_HEREDOC	--> <<
typedef enum e_redirect_type
{
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_APPEND,
	REDIRECT_HEREDOC
}	t_redirect_type;

typedef struct s_redirect
{
	t_redirect_type		type;
	char				*filename;
	int					heredoc_fd;
	int					expand_heredoc;
	struct s_redirect	*next;
}	t_redirect;

#endif
