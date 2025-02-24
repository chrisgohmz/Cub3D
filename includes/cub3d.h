/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgoh <cgoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 19:50:23 by cgoh              #+#    #+#             */
/*   Updated: 2025/02/22 19:50:26 by cgoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx-linux/mlx.h"
# include "../libft/libft.h"
# include "unistd.h"
# include "stdio.h"
# include "stdlib.h"

typedef struct s_data
{
	void	*mlx;
	void	*win;
	char	map[5][6];
}	t_data;

#endif
