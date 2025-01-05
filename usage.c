/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 10:21:29 by aindjare          #+#    #+#             */
/*   Updated: 2025/01/05 10:21:35 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	main_usage(const char *name)
{
	printf("%s is a wolfenstein 3D perspective view clone.\n", name);
	printf("Usage:\n");
	printf("\t%s <mapfile>\n", name);
	printf("Note:\n");
	printf("\tProvided mapfiles have to be in the `cub` format\n");
	printf("made by zadriouc & aindjare\n");
}
