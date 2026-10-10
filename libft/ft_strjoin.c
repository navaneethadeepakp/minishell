/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbecker <kbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:32:12 by kbecker           #+#    #+#             */
/*   Updated: 2025/10/19 17:23:14 by kbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char)
			* (ft_strlen((char *)s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

char	*ft_strnjoin(char const *s1, char const *s2, int n, char *tmp_line)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	len;

	len = ft_strlen(s2);
	if ((int)len > n && n > 0)
		len = n;
	str = (char *)malloc(sizeof(char)
			* (ft_strlen(s1) + n + 1));
	if (str == NULL)
		return (free(tmp_line), NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	j = 0;
	while (s2[j] && j < len)
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (free(tmp_line), str);
}
