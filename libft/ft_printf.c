/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbecker <kbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 16:16:08 by kbecker           #+#    #+#             */
/*   Updated: 2025/05/15 12:09:00 by kbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_handle_strings(char const *inputstr, va_list args)
{
	int	count;

	count = 0;
	if (*inputstr == 'c')
		count = ft_putchar_fd((int)va_arg(args, int), 1);
	else if (*inputstr == 's')
		count = ft_putstr_fd((char *)va_arg(args, char *), 1);
	return (count);
}

static int	ft_handle_hex(char const *inputstr, va_list args)
{
	int					count;
	unsigned int		ui_value;
	unsigned long int	uli_value;
	uintptr_t			tmp;

	count = 0;
	if ((*inputstr != 'p') && (*inputstr != 'x') && (*inputstr != 'X'))
		return (count);
	tmp = (uintptr_t)va_arg(args, void *);
	if (*inputstr == 'p')
	{
		uli_value = (unsigned long int)tmp;
		count = (int)ft_putstr_fd("0x", 1);
		if (count >= 0)
			count += ft_putunbr_base_fd(uli_value, "0123456789abcdef", 1);
	}
	else
	{
		ui_value = (unsigned int)tmp;
		if (*inputstr == 'x')
			count = ft_putunbr_base_fd(ui_value, "0123456789abcdef", 1);
		else if (*inputstr == 'X')
			count = ft_putunbr_base_fd(ui_value, "0123456789ABCDEF", 1);
	}
	return (count);
}

static int	ft_handle_numbers(char const *inputstr, va_list args)
{
	int	count;

	count = 0;
	if (*inputstr == 'd' || *inputstr == 'i')
		count = ft_putnbr_base_fd(
				(int)va_arg(args, int), "0123456789", 1);
	else if (*inputstr == 'u')
		count = ft_putnbr_base_fd(
				(unsigned int)va_arg(args, int), "0123456789", 1);
	return (count);
}

static int	ft_handle_start(char const *inputstr, va_list args)
{
	int	count;

	count = 0;
	count += ft_handle_strings(inputstr, args);
	count += ft_handle_hex(inputstr, args);
	count += ft_handle_numbers(inputstr, args);
	return (count);
}

int	ft_printf(const char *inputstr, ...)
{
	va_list	args;
	int		count;
	int		no_of_char;

	count = 0;
	va_start(args, inputstr);
	while (*inputstr)
	{
		no_of_char = 0;
		if (*inputstr == '%')
		{
			inputstr++;
			no_of_char += ft_handle_start(inputstr, args);
			if (*inputstr == '%')
				no_of_char += ft_putchar_fd(*inputstr, 1);
		}
		else
			no_of_char = ft_putchar_fd(*inputstr, 1);
		if (no_of_char < 0)
			return (-1);
		count += no_of_char;
		inputstr++;
	}
	va_end(args);
	return (count);
}
