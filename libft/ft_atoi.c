/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbecker <kbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:26:45 by kbecker           #+#    #+#             */
/*   Updated: 2025/03/19 09:41:36 by kbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_delete_spaces(char *str)
{
	while ((*str == ' ') || ((*str >= 9) && (*str <= 13)))
		str++;
	return (str);
}

char	*ft_set_factor(char *str, int *factor)
{
	*factor = 1;
	if (*str == '-')
		*factor *= -1;
	if (*str == '+' || *str == '-')
		str++;
	return (str);
}

int	ft_atoi(const char *nptr)
{
	char	*str;
	int		number;
	int		factor;

	str = (char *)nptr;
	str = ft_delete_spaces(str);
	str = ft_set_factor(str, &factor);
	number = 0;
	while (*str)
	{
		if ((*str < '0') || (*str > '9'))
			return (number * factor);
		if (number > 0)
			number *= 10;
		number += *str - '0';
		str++;
	}
	return (number * factor);
}
