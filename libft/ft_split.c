/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbecker <kbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 21:35:39 by kbecker           #+#    #+#             */
/*   Updated: 2025/10/19 17:19:56 by kbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_get_no_of_words(char const *str, char c)
{
	unsigned int	counter;

	counter = 0;
	while (*str)
	{
		while (*str == c)
			str++;
		if (!*str)
			break ;
		counter++;
		while (*str && *str != c)
			str++;
	}
	return (counter);
}

static char	**ft_memalloc_dest(unsigned int word_count)
{
	char	**dest;

	dest = ft_calloc(word_count + 1, sizeof(char *));
	if (dest != NULL)
		dest[word_count] = NULL;
	return (dest);
}

static char	**ft_free_dest(char **dest)
{
	int	i;

	i = 0;
	while (dest[i])
	{
		free(dest[i]);
		i++;
	}
	free(dest);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char			**dest;
	unsigned int	word_count;
	int				line_no;
	int				word_start;
	int				i;

	word_count = ft_get_no_of_words(s, c);
	dest = ft_memalloc_dest(word_count);
	i = 0;
	line_no = -1;
	word_start = 0;
	while (dest && s[i])
	{
		while (s[i] == c)
			i++;
		if (!s[i])
			break ;
		word_start = i;
		while (s[i] && s[i] != c)
			i++;
		dest[++line_no] = ft_strndup(s + word_start, i - word_start);
		if (dest[line_no] == NULL)
			return (ft_free_dest(dest));
	}
	return (dest);
}
