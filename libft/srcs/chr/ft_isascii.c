/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:43:24 by ldurieux          #+#    #+#             */
/*   Updated: 2022/11/08 14:43:26 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define ASCII_MAX	127

int	ft_isascii(int chr)
{
	return ((unsigned int)chr <= ASCII_MAX);
}
