/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atashiro <atashiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 21:25:28 by atashiro          #+#    #+#             */
/*   Updated: 2026/02/10 17:37:09 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	close_window(t_game *game)
{
	mlx_loop_end(game->mlx);
	return (0);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*buf;

	if (size == 0 || nmemb == 0)
	{
		buf = (unsigned char *)malloc(1);
		if (buf == NULL)
			return (NULL);
		return (buf);
	}
	if (size != 0 && nmemb != 0 && nmemb > SIZE_MAX / size)
		return (NULL);
	buf = (unsigned char *)malloc(size * nmemb);
	if (buf == NULL)
		return (NULL);
	ft_bzero(buf, (size * nmemb));
	return (buf);
}

size_t	ft_strlen(const char *s)
{
	unsigned int	c;

	c = 0;
	if (!*s)
		return (0);
	while (s[c] != '\0')
		c ++;
	return (c);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p;

	if (!s)
		return ;
	p = (unsigned char *) s;
	while (n != 0)
	{
		*p = 0;
		n --;
		p ++;
	}
	return ;
}
