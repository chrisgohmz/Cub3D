/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:58:40 by apoh              #+#    #+#             */
/*   Updated: 2025/03/06 14:58:51 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	read_map_line(t_mapdata *parse)
{
	char	*line;
	int	height;
	
	height = 0;
	parse->map = malloc(sizeof(char *) * 30);
	if (parse->map == NULL)
	{
		printf("Allocating memory for map failed\n");
		return (-1);
	}
	while (1)
	{
		line = get_next_line(parse->fd);
		if (line == NULL)
			break ;
		if (ft_strncmp(line, "\n", 1) == 0)
		{
			free(line);
			continue ;
		}
		parse->map[height] = ft_strdup(line);
		height++;
		free(line);
	}
	parse->map[height] = NULL;
	parse->map_height = height;
	return (0);
}

int	parsing(void)
{
	t_mapdata	parse;
	
	ft_memset(&parse, 0, sizeof(t_mapdata));
	parse.fd = open("text.cub", O_RDONLY);
	if (parse.fd == -1)
	{
		printf("File opening failed\n");
		return (-1);
	}
	while (1)
	{
		parse.line = get_next_line(parse.fd);
		if (parse.line == NULL)
			break ;
		if (ft_strncmp(parse.line, "NO ", 3) == 0)
		{
			printf("Storing north_texture\n");
			parse.north_texture = ft_strdup(parse.line);
		}
		else if (ft_strncmp(parse.line, "SO ", 3) == 0)
		{
			printf("Storing south_texture\n");
			parse.south_texture = ft_strdup(parse.line);
		}
		else if (ft_strncmp(parse.line, "WE ", 3) == 0)
		{
			printf("Storing west_texture\n");
			parse.west_texture = ft_strdup(parse.line);
		}
		else if (ft_strncmp(parse.line, "EA ", 3) == 0)
		{
			printf("Storing east_texture\n");
			parse.east_texture = ft_strdup(parse.line);
		}
		else if (ft_strncmp(parse.line, "\n", 1) == 0)
		{
		}
		else if (ft_strncmp(parse.line, "F ", 2) == 0)
		{
			printf("Storing Floor colour\n");
			parse.floor_colour = ft_strdup(parse.line);
		}
		else if (ft_strncmp(parse.line, "C ", 2) == 0)
		{
			printf("Storing Ceiling colour\n");
			parse.ceiling_colour = ft_strdup(parse.line);
		}
		else
			read_map_line(&parse);
		free(parse.line);
	}
	close(parse.fd);
	printf("After parsing, initialising data collected\n");
	printf("North texture : %s\n", parse.north_texture);
	printf("South texture : %s\n", parse.south_texture);
	printf("West texture : %s\n", parse.west_texture);
	printf("East texture : %s\n", parse.east_texture);
	printf("Floor colour : %s\n", parse.floor_colour);
	printf("Ceiling colour : %s\n", parse.ceiling_colour);
	for (int i = 0; i < parse.map_height; i++)
	{
		printf("%s", parse.map[i]);
		free(parse.map[i]);
	}
	free(parse.map);
	free(parse.north_texture);
	free(parse.south_texture);
	free(parse.west_texture);
	free(parse.east_texture);
	free(parse.floor_colour);
	free(parse.ceiling_colour);
	return (0);
}
