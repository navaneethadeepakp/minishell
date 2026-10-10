/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbecker <kbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:04:37 by kbecker           #+#    #+#             */
/*   Updated: 2025/04/03 13:53:43 by kbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	nb;
	char		c;

	nb = n;
	if (nb < 0)
	{
		write(fd, "-", 1);
		nb *= -1;
	}
	if (nb >= 10)
		ft_putnbr_fd(nb / 10, fd);
	c = (nb % 10) + '0';
	write(fd, &c, 1);
}

static int	ft_put_sign(long long int *nbr, int fd)
{
	int	count;

	count = 0;
	if (*nbr < 0)
	{
		count = ft_putchar_fd('-', fd);
		*nbr = -*nbr;
	}
	return (count);
}

int	ft_putnbr_base_fd(long long int nbr, char const *base, int fd)
{
	int		count;
	int		radix;
	int		no_of_char;

	count = 0;
	radix = (int)ft_strlen(base);
	count = ft_put_sign(&nbr, fd);
	if (count < 0)
		return (-1);
	if (nbr < radix)
		no_of_char = ft_putchar_fd(base[nbr], 1);
	else
	{
		no_of_char = ft_putnbr_base_fd(nbr / radix, base, fd);
		if (no_of_char < 0)
			return (-1);
		count += no_of_char;
		no_of_char = ft_putchar_fd(base[nbr % radix], 1);
		if (no_of_char < 0)
			return (-1);
	}
	count += no_of_char;
	if (no_of_char < 0)
		count = -1;
	return (count);
}

int	ft_putunbr_base_fd(unsigned long int nbr, char const *base, int fd)
{
	int		count;
	int		radix;

	count = 0;
	radix = (int)ft_strlen(base);
	if (nbr < (unsigned long int)radix)
		count += (int)ft_putchar_fd(base[nbr], 1);
	else
	{
		count += ft_putnbr_base_fd(nbr / radix, base, fd);
		count += (int)ft_putchar_fd(base[nbr % radix], 1);
	}
	return (count);
}
