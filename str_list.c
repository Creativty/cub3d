/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aindjare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 10:01:29 by aindjare          #+#    #+#             */
/*   Updated: 2025/01/05 10:04:22 by aindjare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	str_list_push(t_list_str** parent, t_list_str* child)
{
	t_list_str*	iter;

	if (parent == NULL)
		return ;
	if (*parent == NULL)
		*parent = child;
	else
	{
		iter = *parent;
		while (iter && iter->next)
			iter = iter->next;
		iter->next = child;
	}
}

t_list_str*	str_list_make(t_state* state, char *data)
{
	t_list_str*	node;

	node = NULL;
	if (state->error == OK)
	{
		node = (t_list_str *)malloc(sizeof(t_list_str) * 1);
		if (node)
		{
			node->next = NULL;
			node->data = str_dup(data);
		}
		else
			state->error = ERROR_ALLOC;
	}
	return (node);
}

char	*str_list_join(t_state *state, t_list_str* list)
{
	int			i;
	int			len;
	int			delta;
	char*		data;
	t_list_str*	iter;

	len = 0;
	iter = list;
	while (iter)
	{
		len += str_len(iter->data);
		iter = iter->next;
	}
	data = (char*)malloc(sizeof(char) * (len + 1));
	if (data == NULL)
		return (make_state_error(state, ERROR_ALLOC), NULL);
	i = 0;
	iter = list;
	while (data && iter && i < len)
	{
		delta = str_len(iter->data);
		mem_cpy(iter->data, delta, &data[i]);
		iter = iter->next;
		i += delta;
	}
	data[i] = '\0';
	return (data);
}

void	str_list_free(t_list_str *list)
{
	if (list)
	{
		str_list_free(list->next);
		free(list->data);
		free(list);
	}
}
