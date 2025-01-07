/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 10:37:28 by aindjare          #+#    #+#             */
/*   Updated: 2025/01/07 10:38:02 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	explain_error(enum e_state_error code)
{
	if (code == ERROR_MLX)
		printf("\tmlx initialization has failed.\n");
	else if (code == ERROR_IMAGE_FORMAT)
		printf("\tan image has incorrect format.\n");
	else if (code == ERROR_IMAGE_LOAD)
		printf("\tan image could not be loaded.\n");
	else if (code == ERROR_LINUX)
		printf("\ta syscall has failed with: %s\n" , strerror(errno));
	else
		printf("\tan uncaught error has occurred with code %d\n", code);
}
