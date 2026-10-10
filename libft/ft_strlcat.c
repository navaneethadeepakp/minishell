/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbecker <kbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 10:57:35 by kbecker           #+#    #+#             */
/*   Updated: 2025/03/19 11:33:07 by kbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	d_len;
	size_t	s_len;
	int		pos;
	int		len;

	d_len = ft_strlen(dst);
	s_len = ft_strlen(src);
	if (dstsize > d_len)
		len = d_len + s_len;
	else
		len = s_len + dstsize;
	pos = 0;
	while (src[pos] && (d_len + 1) < dstsize)
	{
		dst[d_len] = src[pos];
		d_len++;
		pos++;
	}
	dst[d_len] = '\0';
	return (len);
}
