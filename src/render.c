/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:18:57 by davifern          #+#    #+#             */
/*   Updated: 2024/09/06 16:38:09 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_player_position(t_player *player, t_data *data)
{
	double	next_x;
	double	next_y;

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
	if (BONUS)
		draw_minimap(data);
	update_player_position(data->player, data);
	mlx_put_image_to_window(data->mlx_ptr,
		data->win_ptr, data->img->img_ptr, 0, 0);
}

int	render_if_moved(t_data *data)
{
	if (!data->w && !data->s && !data->a && !data->d && !data->r && !data->l)
		return (0);
	data->i++;
	render(data);
	return (0);
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
		ray->camera_x = 2 * x / (double)WIDTH - 1;
		calculate_ray_direction_and_delta(ray, player);
		set_dda(ray, player);
		execute_dda(ray, data->map, data->map_h, data->map_w);
		calculate_wall_distance(ray);
		calculate_line_height(ray);
		calculate_wall_x(ray, player);
		set_wall_texture_pixels(ray, data->buffer, x, data);
		color_floor(data, data->buffer, ray->draw_start, x);
		color_ceiling(data, data->buffer, ray->draw_end, x);
		x++;
	}
	render_buffer(data->buffer, data->img);
	clean_buffer(data->buffer);
}
