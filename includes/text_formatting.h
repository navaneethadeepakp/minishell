/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_formatting.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbecker <kbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 10:23:38 by kbecker           #+#    #+#             */
/*   Updated: 2026/01/16 10:38:14 by kbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXT_FORMATTING_H
# define TEXT_FORMATTING_H

# define COLOR_RED     "\033[31m"
# define COLOR_GREEN   "\033[32m"
# define COLOR_YELLOW  "\033[33m"
# define COLOR_BLUE    "\033[34m"
# define COLOR_MAGENTA "\033[35m"
# define COLOR_CYAN    "\033[36m"
# define COLOR_GRAY    "\033[90m"
# define COLOR_RESET   "\033[0m"
# define BOLD		   "\033[1m"

# define RL_COLOR_GREEN	"\001\033[32m\002"
# define RL_COLOR_BLUE	"\001\033[34m\002"
# define RL_COLOR_RESET	"\001\033[0m\002"
# define RL_BOLD		"\001\033[1m\002"

#endif