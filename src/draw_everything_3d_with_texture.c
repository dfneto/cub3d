/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_everything_3d_with_texture.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 18:07:08 by davifern          #+#    #+#             */
/*   Updated: 2024/08/29 14:49:47 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
Calculates de perpendicular wall distance from the player to 
the wall. Side = 0 if the ray hits EW in the wall and side = 1
if it hits NS side
*/
void	calculate_wall_distance(t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_distance = (ray->sideDistX - ray->deltaDistX);
	else
		ray->wall_distance = (ray->sideDistY - ray->deltaDistY);
}

/*
Calculates once, per x position:
ray_dir is the ray direction. It is a vector
delta_dist_x and delta_dist_y are the distance the ray has to travel 
to go from 1 x-side to the next x-side, or from 1 y-side to the next y-side.
*/
void	calculate_ray_direction_and_delta(t_ray *ray, t_player *player)
{
	ray->rayDirX = player->dir_x + player->planeX * ray->cameraX;
	ray->rayDirY = player->dir_y + player->planeY * ray->cameraX;
	ray->deltaDistX = fabs(1 / ray->rayDirX);
	ray->deltaDistY = fabs(1 / ray->rayDirY);
}
