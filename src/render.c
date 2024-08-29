/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:18:57 by davifern          #+#    #+#             */
/*   Updated: 2024/08/29 15:03:14 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render(t_data *data)
{
	draw_with_raycasting(data);
	draw_minimap(data);
	mlx_put_image_to_window(data->mlx_ptr,
		data->win_ptr, data->img->img_ptr, 0, 0);
}

void	render_buffer(int **buffer, t_img *img)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_mlx_pixel_put(img, x, y, buffer[y][x]);
			x++;
		}
		y++;
	}
}

void	clean_buffer(int **buffer)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
			buffer[y][x++] = 0;
		y++;
	}
}

/*
line_height is the height of the vertical line that should be drawn. 
You can of course also multiply it with another value if you want 
to walls to be higher or lower
*/
void	draw_with_raycasting(t_data *data)
{
	int			x;
	char		**grid_map;
	t_ray		*ray;
	t_player	*player;

	player = data->player;
	grid_map = data->map;
	ray = data->ray;
	x = 0;
	while (x < WIDTH)
	{
		init_ray(data->ray);
		ray->cameraX = 2 * x / (double)WIDTH - 1;
		calculate_ray_direction_and_delta(ray, player);
		ray->mapX = (int)player->pos_x;
		ray->mapY = (int)player->pos_y;
		set_dda(ray, player);
		execute_dda(ray, grid_map);
		calculate_wall_distance(ray);
		calculate_line_height(ray);
		calculate_wall_x(ray, player);
		
		// calculate the line_height, the side and wall_x
		set_wall_texture_pixels(ray, data->buffer, x, data->textures);
		color_floor(data, data->buffer, ray->draw_start, x);
		color_ceiling(data, data->buffer, ray->draw_end, x);
		x++;
	}
	render_buffer(data->buffer, data->img);
	clean_buffer(data->buffer); //TODO: não sei se é necessário
}
