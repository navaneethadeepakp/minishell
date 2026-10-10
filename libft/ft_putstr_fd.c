/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbecker <kbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:55:22 by kbecker           #+#    #+#             */
/*   Updated: 2025/04/03 12:18:50 by kbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	if (s == NULL)
	{
		if (write(fd, "(null)", 6) < 0)
			return (-1);
		return (6);
	}
	if (!s)
		return (0);
	len = ft_strlen(s);
	if (write(fd, s, len) < 0)
		return (-1);
	return (len);
}
