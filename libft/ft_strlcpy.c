/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbecker <kbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 10:57:35 by kbecker           #+#    #+#             */
/*   Updated: 2025/03/19 11:36:23 by kbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	if (dstsize < 1)
		return (ft_strlen(src));
	i = 0;
	while (*src)
	{
		if (i < (dstsize - 1))
		{
			*dst = *src;
			dst++;
		}
		src++;
		i++;
	}
	*dst = '\0';
	return (i);
}
