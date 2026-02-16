/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <sohyamaz@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 19:41:27 by sohyamaz          #+#    #+#             */
/*   Updated: 2026/02/17 04:35:39 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"
//
//bool	get_map_size(t_map *map, char *fullpath)
//{
//	size_t	x;
//	char	*line;
//
//	if (map == NULL || fullpath == NULL)
//		return (false);
//	map->cubfd = open(fullpath, O_RDONLY);
//	if (map->cubfd < 0)
//		return (perror("open"), false);
//	x = 0;
//	while (1)
//	{
//		line = get_next_line(map->cubfd);
//		if (line == NULL)
//			break ;
//		x = ft_strlen(line) + 1;
//		if (x > map->x)
//			map->x = x;
//		map->y++;
//		free(line);
//	}
//	map->y++;
//	close(map->cubfd);
//	return (true);
//}

bool	is_config_line(char c)
{
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
		return (true);
	if (c == 'F' || c == 'C')
		return (true);
	return (false);
}

static char	*gnl_strjoin(char *s1, char c)
{
	size_t	dsize;
	char	*dest;
	int		i;

	if (!s1)
		return (NULL);
	i = 0;
	dsize = ft_strlen(s1) + 2;
	dest = (char *)malloc(sizeof(char) * dsize);
	if (dest == NULL)
	{
		free(s1);
		return (NULL);
	}
	while (s1[i] != '\0')
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = c;
	i++;
	dest[i] = '\0';
	free (s1);
	return (dest);
}

static int	get_next_char(int fd)
{
	static char		buf[BUFFER_SIZE];
	static char		*bufptr;
	static int		remain;
	unsigned char	asc;

	if (remain == 0)
	{
		remain = read(fd, buf, BUFFER_SIZE);
		if (remain == 0)
			return (EOF);
		if (remain < 0)
			return (INT_MIN);
		bufptr = buf;
	}
	asc = 0;
	if (remain > 0)
	{
		asc = (unsigned char) *bufptr;
		bufptr ++;
		remain --;
		return (asc);
	}
	else
		return (EOF);
}

static char	*set_next_line(int asc, char *val)
{
	if (asc == EOF)
	{
		if (*val == '\0')
		{
			free (val);
			return (NULL);
		}
		return (val);
	}
	if (asc == INT_MIN)
	{
		if (val != NULL)
			free (val);
		return (NULL);
	}
	val = gnl_strjoin(val, asc);
	if (val == NULL)
		return (NULL);
	return (val);
}

char	*get_next_line(int fd)
{
	char	*val;
	int		asc;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	val = ft_calloc(sizeof(char), 1);
	if (val == NULL)
		return (NULL);
	while (1)
	{
		asc = get_next_char(fd);
		val = set_next_line(asc, val);
		if (val == NULL)
			return (NULL);
		if (asc == '\n' || asc == EOF)
			break ;
	}
	return (val);
}
