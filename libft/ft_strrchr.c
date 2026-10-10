/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbecker <kbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 11:26:17 by kbecker           #+#    #+#             */
/*   Updated: 2025/03/20 08:41:08 by kbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char			*str;
	int				i;

	str = (char *)s;
	i = ft_strlen(str);
	str += i;
	while (i--)
	{
		if (*str == (unsigned char)c)
			return (str);
		str--;
	}
	if (*str == (unsigned char)c)
		return (str);
	return (NULL);
}
