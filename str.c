/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 10:23:57 by aindjare          #+#    #+#             */
/*   Updated: 2025/01/04 10:54:04 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
