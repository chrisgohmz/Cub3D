/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:49:12 by apoh              #+#    #+#             */
/*   Updated: 2025/03/28 12:49:14 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	found_map_start(const char *str)
{
	int	i;

	i = -1;
	while (str[++i] == ' ')
	{
	}
	return (str[i] == '1');
}

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

bool	check_color_range(int *color, char *color_str)
{
	int	i;

	if (ft_strlen(color_str) > 3)
		return (print_error("Color range must be within 0 and 255"));
	i = -1;
	while (color_str[++i])
	{
		if (!ft_isdigit(color_str[i]))
			return (print_error("Color may only contain digits"));
	}
	*color = ft_atoi(color_str);
	if (*color < 0 || *color > 255)
		return (print_error("Color range must be within 0 and 255"));
	return (true);
}

int	count_commas(const char *str)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == ',')
			++count;
	}
	return (count);
}
