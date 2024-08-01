/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:02:01 by davifern          #+#    #+#             */
/*   Updated: 2024/07/30 13:48:21 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//Looks when there is a wall in the player's direction (not in their sides)
//and returns the coordinates of the end point (it means, the coordinates
//where the ray direction hits the wall) and their distance
t_point_distance dda_collision_detection_lodev(t_player *player, t_map *map)
{
    t_point_distance end_point;
    
	float rayDirX = player->dir_x;
	float rayDirY = player->dir_y;
	int col = (int)player->x;
	int row = (int)player->y;

	double sideDistX;
	double sideDistY;

	double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1.0 / rayDirX);
	double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1.0 / rayDirY);
	
	double perpWallDist;
	
	int stepX;
	int stepY;

	int hit = 0;
	int side;

	if (rayDirX < 0) 
	{
		stepX = -1;
		sideDistX = (player->x - col) * deltaDistX;
	}
	else
	{
		stepX = 1;
		sideDistX = (col + 1.0 - player->x) * deltaDistX;
	}
	if (rayDirY > 0)
	{
		stepY = -1;
		sideDistY = (player->y - row) * deltaDistY;
	}
	else
	{
		stepY = 1;
		sideDistY = (row + 1.0 - player->y) * deltaDistY;
	}

	while (hit == 0)
	{
		if (sideDistX < sideDistY)
		{
			sideDistX += deltaDistX;
			col += stepX;
			side = 0;
		}
		else
		{
			sideDistY += deltaDistY;
			row += stepY;
			side = 1;
		}
		if (map->grid[row][col] == '1') 
            break;
	}
	if(side == 0) perpWallDist = (sideDistX - deltaDistX);
    else          perpWallDist = (sideDistY - deltaDistY);

	/* Essa parte peguei do chat: https://chatgpt.com/share/e4e4a020-c3d0-4199-b8da-b3d3df881922 
	I have a point A in a map with known coordinates (x,y), his direction (in a vector form) and 
	a distance between A and B. How can I calculate the coordinates of B?
	double dir_magnitude = sqrt(player->dir_x * player->dir_x + player->dir_y * player->dir_y);
    // Normalize the direction vector
    double dir_x_unit = player->dir_x / dir_magnitude;
    double dir_y_unit = player->dir_y / dir_magnitude;
    // Calculate the coordinates of point B
    end_point.x = player->x + perpWallDist * dir_x_unit;
    end_point.y = player->y - perpWallDist * dir_y_unit;
	*/
	//essa formula peguei do video do jaxi: end = start + dir * length
	end_point.x = player->x + player->dir_x * perpWallDist;
    end_point.y = player->y - player->dir_y * perpWallDist; //TODO: usar o y positivo, como eh no x, mas na hora de printar o pixel fazer a conversao
	end_point.distance = perpWallDist;
	printf("distance = %f\n", end_point.distance);
    return end_point;
}