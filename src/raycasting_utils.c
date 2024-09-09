/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:38:19 by davifern          #+#    #+#             */
/*   Updated: 2024/09/09 18:15:15 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	*define_wall_texture(t_ray *ray, t_textures *textures)
{
	if (ray->side == 0 && ray->ray_dir_x >= 0)
		return (textures->east);
	if (ray->side == 0 && ray->ray_dir_x < 0)
		return (textures->west);
	if (ray->side == 1 && ray->ray_dir_y >= 0)
		return (textures->north);
	return (textures->south);
}

//Calculate lowest and highest pixel to fill in current stripe
//Calculate the line_height (of the wall) that is related with
//the distance from the player to the wall (ray->wall_distance)
//and will be used to render the 3d view of the wall. 
//From the line_height we define from where (draw_start)
//to where (draw_end) we have to render to represent the wall.
//Everything before the draw_start is the floor and everything
//after draw_end is the ceiling
void	calculate_line_height(t_ray *ray)
{
	ray->line_height = (int)(HEIGHT / ray->wall_distance);
	if (ray->line_height < 0)
		ray->line_height = 0;
	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

//wall_x is where exactly the wall was hit
//It can be both on x as on y. The name doesn't mean that
//was hit on a specific side
void	calculate_wall_x(t_ray *ray, t_player *player)
{
	if (ray->side == 0)
		ray->wall_x = player->pos_y + ray->wall_distance * ray->ray_dir_y;
	else
		ray->wall_x = player->pos_x + ray->wall_distance * ray->ray_dir_x;
	ray->wall_x -= floor((ray->wall_x));
}

/*
Calculates de perpendicular wall distance from the player to 
the wall. Side = 0 if the ray hits EW in the wall and side = 1
if it hits NS side
Se por algum motivo (no mac quando a PLAYER_SPEED é abaixo de 0.11)
o wall_distance for 0 dá segfault
*/
void	calculate_wall_distance(t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_distance = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->wall_distance = (ray->side_dist_y - ray->delta_dist_y);
	if (fabs(ray->wall_distance) < EPSILON)
		ray->wall_distance = 0.0001;
}

/*
Calculates once, per x position:
ray_dir is the ray direction. It is a vector
delta_dist_x and delta_dist_y are the distance the ray has to travel 
to go from 1 x-side to the next x-side, or from 1 y-side to the next y-side.
*/
void	calculate_ray_direction_and_delta(t_ray *ray, t_player *player)
{
	ray->ray_dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->ray_dir_y = player->dir_y + player->plane_y * ray->camera_x;
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}
