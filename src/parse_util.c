/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <sohyamaz@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 16:22:17 by sohyamaz          #+#    #+#             */
/*   Updated: 2026/02/01 18:54:48 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CUB3D_H"

bool	is_valid_extention(char *fullpath, char *target)
{
	char	*filename;
	char	*extention;
	size_t	fname_len;
	size_t	target_len;

	if (fullpath == NULL)
		return (false);
	filename = ft_strrchr(fullpath, '/');
	if (filename != NULL)
		filename++;
	else
		filename = fullpath;
	fname_len = ft_strlen(filename);
	taget_len = ft_strlen(target);
	if (fname_len <= target_len)
		return (false);
	extention = filename + fname_len - target_len;
	if (ft_strncmp(extention, target, target_len) != 0)
		return (false);
	return (true);
}

char	*get_next_line(int fd)
{
	char		ret[1000];
	static char	buffer[BUFFER_SIZE];
	static int	read_byte;
	static int	put_byte;
	int			i;

	i = 0;
	while (1)
	{
		if (put_byte >= read_byte)
		{
			read_byte = read(fd, buffer, BUFFER_SIZE);
			if (read_byte <= 0)
				return (NULL);
			put_byte = 0;
		}
		ret[i] = buffer[put_byte];
		i++;
		put_byte++;
		if (buffer[put_byte - 1] == '\0' || buffer[put_byte - 1] == '\n')
			break ;
	}
	ret[i] = '\0';
	return (ft_strdup(ret));
}
