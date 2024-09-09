/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 19:29:43 by davifern          #+#    #+#             */
/*   Updated: 2024/09/09 17:07:24 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// while(i <= data->map_h)
// 	free(data->map[i++]);
// free(data->map);
// free(data->textures->north->img_ptr);
// free(data->textures->north);

// free(data->textures->south);
// free(data->textures->east);
// free(data->textures->west);
void	free_data(t_data *data)
{
	int	i;

	i = 0;
	free(data->ray);
	while (i < WIDTH)
		free(data->buffer[i++]);
	free(data->buffer);
	free(data->tile);
	free(data->player);
	free(data->textures->floor);
	free(data->textures->ceiling);
}

void	clean_exit(t_data *data, char *msg)
{
	printf("%s\n", msg);
	if (!data)
		exit(1);
	if (data->mlx_ptr && data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		mlx_loop_end(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	free_data(data);
	exit(0);
}
