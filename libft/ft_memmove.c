/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbecker <kbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 10:31:08 by kbecker           #+#    #+#             */
/*   Updated: 2025/03/19 09:41:44 by kbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dest_uc;
	unsigned char	*src_uc;
	size_t			i;

	if (!dest && !src)
		return (NULL);
	dest_uc = (unsigned char *)dest;
	src_uc = (unsigned char *)src;
	i = 0;
	if (dest_uc < src_uc)
	{
		while (i < n)
		{
			dest_uc[i] = src_uc[i];
			i++;
		}
		return (dest);
	}
	while (n > 0)
	{
		dest_uc[n - 1] = src_uc[n - 1];
		n--;
	}
	return (dest);
}
