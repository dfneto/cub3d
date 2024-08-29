/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:19:33 by davifern          #+#    #+#             */
/*   Updated: 2024/08/29 12:36:47 by davifern         ###   ########.fr       */
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
void	execute_dda(t_ray *ray, char **grid_map)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY;
			ray->side = 1;
		}
		if (grid_map[ray->mapY][ray->mapX] >= '1')
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
		ray->sideDistX = (player->pos_x - ray->mapX) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->mapX + 1.0 - player->pos_x) * ray->deltaDistX;
	}
	if (ray->rayDirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (player->pos_y - ray->mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1.0 - player->pos_y) * ray->deltaDistY;
	}
}
