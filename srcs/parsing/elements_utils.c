/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:49:12 by apoh              #+#    #+#             */
/*   Updated: 2025/04/11 22:31:18 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	count_arr_elements(char **arr)
{
	int	count;

	count = -1;
	while (arr[++count])
	{
	}
	return (count);
}

bool	print_error(const char *message)
{
	ft_dprintf(STDERR_FILENO, "Error\n%s\n", message);
	return (false);
}
