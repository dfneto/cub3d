/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:18:57 by davifern          #+#    #+#             */
/*   Updated: 2024/09/02 11:20:29 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//Apply the next position to the player
void	apply_position(t_player *player, double next_x, double next_y)
{
	player->pos_x = next_x;
	player->pos_y = next_y;
}

void update_player_position(t_player *player, t_data *data)
{
    double next_x;
    double next_y;

	next_x = 0.0;
	next_y = 0.0;
    if (data->w)
		calculate_position_forward(player, &next_x, &next_y);
	if (data->s)
		calculate_position_back(player, &next_x, &next_y);
	if (data->a)
		calculate_position_left(player, &next_x, &next_y);
	if (data->d)
		calculate_position_right(player, &next_x, &next_y);
    if (data->r)
		rotate_left_right(player, -ROT_SPEED);
	if (data->l)
		rotate_left_right(player, ROT_SPEED);
    if (is_next_position_valid(data, next_x, next_y))
		apply_position(player, next_x, next_y);
}

void	render(t_data *data)
{
	draw_with_raycasting(data);
	draw_minimap(data);
	update_player_position(data->player, data);
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
	t_ray		*ray;
	t_player	*player;

	player = data->player;
	ray = data->ray;
	x = 0;
	while (x < WIDTH)
	{
		init_ray(data->ray);
		ray->cameraX = 2 * x / (double)WIDTH - 1;
		calculate_ray_direction_and_delta(ray, player);
		ray->map_x = (int)player->pos_x;
		ray->map_y = (int)player->pos_y;
		set_dda(ray, player);
		execute_dda(ray, data->map, data->map_h, data->map_w);
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
