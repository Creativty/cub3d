/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 10:23:57 by aindjare          #+#    #+#             */
/*   Updated: 2025/01/07 10:35:17 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>

int	str_len(const char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int	str_find(const char *haystack, const char *pattern)
{
	int	i;
	int	j;

	i = 0;
	while (pattern && haystack && haystack[i])
	{
		j = 0;
		while (pattern[j] && haystack[i + j] == pattern[j])
			j++;
		if (str_len(pattern) == j)
			return (i);
		i++;
	}
	return (-1);
}

bool	str_suffix(const char *haystack, const char *pattern)
{
	int	offset;

	offset = str_len(haystack) - str_len(pattern);
	if (offset < 0)
		return (false);
	return (str_find(haystack, pattern) == offset);
}

bool	str_prefix(const char *haystack, const char *pattern)
{
	return (str_find(haystack, pattern) == 0);
}

char	*str_dup(const char *src)
{
	int		i;
	int		len;
	char	*dst;

	len = str_len(src);
	dst = (char *)malloc(sizeof(char) * (len + 1));
	if (dst)
	{
		i = 0;
		while (dst && i < len)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (dst);
}
