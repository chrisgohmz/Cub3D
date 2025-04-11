/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 21:33:24 by cgoh              #+#    #+#             */
/*   Updated: 2025/04/11 22:31:24 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static bool	check_color_range(int *color, char *color_str)
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

static int	count_commas(const char *str)
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

static int	validating_commas(char *str)
{
	if (count_commas(str) != 2)
	{
		ft_dprintf(STDERR_FILENO, "Error\nFile contains invalid line\n");
		return (-1);
	}
	return (0);
}

static int	validating_array_elements(char **color_rgb_arr)
{
	if (count_arr_elements(color_rgb_arr) != 3)
	{
		ft_dprintf(STDERR_FILENO, "Error\nFile contains invalid line\n");
		free_2d_arr((void ***)&color_rgb_arr);
		return (-1);
	}
	return (0);
}

int	get_color(char *str)
{
	char	**color_rgb_arr;
	int		red;
	int		green;
	int		blue;

	if (validating_commas(str) == -1)
		return (-1);
	color_rgb_arr = ft_split(str, ',');
	if (!color_rgb_arr)
		return (-1);
	if (validating_array_elements(color_rgb_arr) == -1)
		return (-1);
	if (!check_color_range(&red, color_rgb_arr[0])
		|| !check_color_range(&green, color_rgb_arr[1])
		|| !check_color_range(&blue, color_rgb_arr[2]))
	{
		free_2d_arr((void ***)&color_rgb_arr);
		return (-1);
	}
	free_2d_arr((void ***)&color_rgb_arr);
	return (red << 16 | green << 8 | blue);
}
