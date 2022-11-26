/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <ldurieux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 22:55:22 by ldurieux          #+#    #+#             */
/*   Updated: 2022/11/24 22:55:26 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_internal.h"

void	*ft_realloc(void **ptr, size_t *size, size_t new_size)
{
	void	*res;

	if (!*ptr)
	{
		*ptr = malloc(sizeof(char) * new_size);
		if (!*ptr)
			return (NULL);
		*size = new_size;
		return (*ptr);
	}
	res = malloc(sizeof(char) * new_size);
	if (!res)
		return (NULL);
	ft_memcpy(res, *ptr, *size);
	free(*ptr);
	*size = new_size;
	*ptr = res;
	return (res);
}
