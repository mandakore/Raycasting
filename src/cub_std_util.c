/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_std_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <sohyamaz@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 17:39:26 by sohyamaz          #+#    #+#             */
/*   Updated: 2026/02/10 17:49:17 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*dest;
	size_t			slen;

	if (s == NULL)
	{
		return (NULL);
	}
	slen = ft_strlen(s);
	if (start > slen)
		return (ft_strdup(""));
	else if (len > slen - start)
		len = slen - start;
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
		return (NULL);
	ft_strlcpy(dest, s + start, len + 1);
	return (dest);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t len)
{
	size_t	ret;

	if (!dest || !src)
		return (0);
	ret = ft_strlen(src);
	if (len == 0)
		return (ret);
	else if (len == 1)
	{
		*dest = '\0';
		return (ret);
	}
	while ((*src != '\0') && (len - 1 != 0))
	{
		*dest = *src;
		dest++;
		src++;
		len--;
	}
	*dest = '\0';
	return (ret);
}

char	*ft_strdup(const char *s)
{
	char	*dest;
	size_t	len;

	if (!s)
		return (NULL);
	len = 0;
	len = ft_strlen(s);
	dest = (char *)malloc(len + 1);
	if (dest == NULL)
		return (NULL);
	ft_memmove(dest, s, len);
	dest[len] = '\0';
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (!dest || !src)
		return (dest);
	if (dest == src)
		return (dest);
	d = (unsigned char *) dest;
	s = (const unsigned char *) src;
	if (d < s)
	{
		while (n != 0)
		{
			*d++ = *s++;
			n--;
		}
	}
	if (s < d)
	{
		d = d + n - 1;
		s = s + n - 1;
		while (n-- != 0)
			*d-- = *s--;
	}
	return (dest);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;

	if (!s)
		return (s);
	p = (unsigned char *) s;
	while (n > 0)
	{
		*p = (unsigned char) c;
		n --;
		p ++;
	}
	return (s);
}
