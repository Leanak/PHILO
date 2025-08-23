/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 21:06:45 by lenakach          #+#    #+#             */
/*   Updated: 2025/05/06 13:34:49 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*ptr;

	ptr = malloc (sizeof(t_list));
	if (!ptr)
		return (NULL);
	(*ptr).content = content;
	(*ptr).next = NULL;
	return (ptr);
}

/*int	main(void)
{
	t_list	*tmp;

	tmp = ft_lstnew((void *)"Heyyy");

	printf("%s", (char *)(*tmp).content);
	return (0);
}*/
