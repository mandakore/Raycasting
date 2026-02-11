/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyamaz <sohyamaz@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 05:40:29 by sohyamaz          #+#    #+#             */
/*   Updated: 2026/02/10 18:02:17 by sohyamaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

char	*ft_strrchr(const char *str, int c)
{
	unsigned char	*temp;
	unsigned char	*org;
	unsigned char	check;

	if (!str)
		return (NULL);
	org = (unsigned char *) str;
	str = str + ft_strlen(str);
	temp = (unsigned char *) str;
	check = (unsigned char) c;
	while (org != temp)
	{
		if (*temp == check)
			return ((char *)str);
		str --;
		temp --;
	}
	if (*str == check)
		return ((char *)str);
	return (NULL);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;

	if (!s1 || !s2)
		return (INT_MIN);
	if (n == 0)
		return (0);
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (ft_strlen(s1) == 0 || ft_strlen(s2) == 0)
		return (*str1 - *str2);
	while ((*str1 != '\0' || *str2 != '\0') && n > 0)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1 ++;
		str2 ++;
		n --;
	}
	return (0);
}
