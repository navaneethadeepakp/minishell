/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbecker <kbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:31:12 by kbecker           #+#    #+#             */
/*   Updated: 2025/06/25 15:03:02 by kbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_get_len(long int nb)
{
	int		len;

	if (nb < 0)
		nb *= -1;
	len = 1;
	while (nb / 10)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			len;
	long int	nb;

	nb = n;
	len = ft_get_len(nb);
	str = (char *)malloc(sizeof(char) * (len + (n < 0) + 1));
	if (!str)
		return (NULL);
	if (nb < 0)
	{
		str[0] = '-';
		nb *= -1;
	}
	str[len + (n < 0)] = '\0';
	len--;
	while (len >= 0)
	{
		str[len + (n < 0)] = (nb % 10) + '0';
		nb /= 10;
		len--;
	}
	return (str);
}
