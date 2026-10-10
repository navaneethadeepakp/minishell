/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbecker <kbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:31:28 by kbecker           #+#    #+#             */
/*   Updated: 2025/10/19 17:24:41 by kbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*str;
	size_t	len;

	len = ft_strlen(s) + 1;
	str = malloc(len);
	if (!str)
		return (NULL);
	ft_memcpy(str, s, len);
	return (str);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*str;

	str = (char *)ft_calloc(n + 1, sizeof(char));
	if (str != NULL)
		ft_strlcpy(str, s, n + 1);
	return (str);
}
