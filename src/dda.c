/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:19:33 by davifern          #+#    #+#             */
/*   Updated: 2024/08/30 13:05:50 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//side_distance: get incremented with deltaDistX with every jump in 
//their direction, and mapX and mapY get incremented with stepX and 
//stepY respectively. 
//map_x and map_y: are the grid coordinates of the ray position and 
//get incremented with step_x and step_y respectively
//side: 1 if the ray intersects a NS grid line (y-side), 
//0 if the ray intersects a EW grid line (x-side)
void	execute_dda(t_ray *ray, char **grid_map, int height, int width)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->map_x += ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->map_y += ray->stepY;
			ray->side = 1;
		}
		if (ray->map_y < 0.25
			|| ray->map_x < 0.25
			|| ray->map_y >= height
			|| ray->map_x >= width)
			break ;
		else if (grid_map[ray->map_y][ray->map_x] >= '1')
			hit = 1;
	}
}

/*
Calculates once, per x position:
side_distance: is the distance the ray has to travel from 
its start position to the first x-side and the first y-side
step_x and step_y: always either -1 or +1. If the ray has 
to go in the negative or positive direction
*/
void	set_dda(t_ray *ray, t_player *player)
{
	if (ray->rayDirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (player->pos_x - ray->map_x) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->map_x + 1.0 - player->pos_x) * ray->deltaDistX;
	}
	if (ray->rayDirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (player->pos_y - ray->map_y) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->map_y + 1.0 - player->pos_y) * ray->deltaDistY;
	}
}
