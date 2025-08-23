/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:46:39 by lenakach          #+#    #+#             */
/*   Updated: 2025/05/14 13:56:22 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	cc;
	int				i;

	cc = (unsigned char)c;
	i = 0;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == cc)
			return ((char *)(&s[i]));
		i--;
	}
	return (NULL);
}
/*int	main(void)
{
	const char	str[] = "llo";
	int	c;

	c = 72;
	printf("Mon retour est : %p", ft_strrchr(str, c));
	return (0);
}*/