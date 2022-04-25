/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdelendchr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 08:47:38 by skorte            #+#    #+#             */
/*   Updated: 2022/04/25 08:47:38 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

/*
** The strdelendchr() function returns a pointer to a new string with all
** occurences of the character c removed from its end.
*/

char	*ft_strdelendchr(const char *s, int c)
{
	int		len;
	char	*rtn;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	while (s[len - 1] == c)
		len--;
	rtn = malloc (sizeof(char) * (len + 1));
	ft_strlcpy(rtn, s, len + 1);
	return (rtn);
}
