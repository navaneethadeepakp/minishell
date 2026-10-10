/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbecker <kbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 11:31:45 by kbecker           #+#    #+#             */
/*   Updated: 2026/01/16 11:33:07 by kbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*skip_until_quote(char *str, char quote)
{
	while (*str && *str != quote)
		str++;
	if (*str == quote)
		str++;
	return (str);
}

static char	*handle_quote(char *str, char *quote_char)
{
	*quote_char = *str;
	str++;
	return (skip_until_quote(str, *quote_char));
}

static int	is_redirect_operator(char *str)
{
	if (*str == '<' || *str == '>')
	{
		if (*(str + 1) == *str)
			return (2);
		return (1);
	}
	return (0);
}

char	*find_end_of_token(char *str, char *quote_char)
{
	int	redirect_len;

	*quote_char = 0;
	redirect_len = is_redirect_operator(str);
	if (redirect_len > 0)
		return (str + redirect_len);
	while (*str && *str != ' ' && *str != '|' && *str != '<' && *str != '>'
		&& !(*str >= 9 && *str <= 13))
	{
		if (*str == '"' || *str == '\'')
			str = handle_quote(str, quote_char);
		else
			str++;
	}
	return (str);
}
