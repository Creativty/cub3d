/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 10:14:22 by aindjare          #+#    #+#             */
/*   Updated: 2025/01/05 10:02:14 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	mem_zero(void *memory, unsigned long size)
{
	unsigned long i;

	i = 0;
	while (memory && i < size)
		((char *)memory)[i++] = '\0';
}

void	mem_cpy(const char *src, int n, char *dst)
{
	int i;

	i = 0;
	while (src && dst && i < n)
	{
		dst[i] = src[i];
		i++;
	}
}
