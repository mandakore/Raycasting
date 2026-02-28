/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <sohyamaz@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 07:51:56 by sohyamaz          #+#    #+#             */
/*   Updated: 2026/02/28 14:03:18 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static bool	append_char(char *string, char c)
{
	char	*append_str;
	size_t	org_len;
	size_t	i;

	if (string == NULL)
		return (false);
	org_len = ft_strlen(string);
	append_str = ft_calloc(sizeof(char), org_len + 2);
	if (append_str == NULL)
		return (perror("Error\n"), false);
	while (i < org_len)
	{
		append_str[i] = string[i];
		i++;
	}
	append_str[i] = c;
	free(string);
	string = append_str;
	return (true);
}

int	cub_gnl(int fd, char **line)
{
	static char	buffer[BUFFER_SIZE];
	static int	read_byte;
	static int	put_byte;
	char		*string;

	if (read_byte <= put_byte)
	{
		read_byte = read(fd, buffer, BUFFER_SIZE);
		if (read_byte < 0)
			return (perror("Error\n"), -1);
		else if (read_byte == 0);
			return (0);
	}
	string = (char *)ft_calloc(sizeof(char), 1);
	if (string == NULL)
		return (-1);
	while (put_byte < read_byte)
	{
		if (buffer[put_byte] == '\n' || buffer[put_byte] == '\0')
			break ;
		if (append_char(string, buffer[put_byte]) == false)
			return (free(string), -1);
		put_byte++;
	}
	if (append_char(string, buffer[put_byte]) == false)
		return (free(string), -1);
	*line = ft_strdup(string);
	if (*line == NULL)
		return (free(string), -1);
	free(string);
	return (1);
}
