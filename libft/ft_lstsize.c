/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbecker <kbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 19:53:04 by kbecker           #+#    #+#             */
/*   Updated: 2025/03/20 08:38:54 by kbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		count;
	t_list	*tmp_lst;

	count = 0;
	tmp_lst = lst;
	while (tmp_lst)
	{
		count++;
		tmp_lst = tmp_lst->next;
	}
	return (count);
}
