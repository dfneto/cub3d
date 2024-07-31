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

t_point dda_collision_detection_lodev(t_player *player, t_map *map)
{
    t_point end_point;
    
	float rayDirX = player->dir_x;
	float rayDirY = player->dir_y;
    printf("rayDirX %f, rayDirY %f\n", rayDirX, rayDirY);   
	int mapX = (int)player->x;
	int mapY = (int)player->y;
    printf("Posição inicial: coluna %d, linha %d\n", mapX, mapY);   

	double sideDistX;
	double sideDistY;

	double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1.0 / rayDirX);
	double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1.0 / rayDirY);
    printf("deltaDistX %f, deltaDistY %f\n", deltaDistX, deltaDistY);   
	
	int stepX;
	int stepY;

	int hit = 0;

	if (rayDirX < 0)
	{
		stepX = -1;
		sideDistX = (player->x - mapX) * deltaDistX;
	}
	else
	{
		stepX = 1;
		sideDistX = (mapX + 1.0 - player->x) * deltaDistX;
	}
	if (rayDirY < 0)
	{
		stepY = -1;
		sideDistY = (player->y - mapY) * deltaDistY;
	}
	else
	{
		stepY = 1;
		sideDistY = (mapY + 1.0 - player->y) * deltaDistY;
	}

	while (hit == 0) //enquanto não bateu na parede
	{
		if (sideDistX < sideDistY)
		{
			sideDistX += deltaDistX;
			mapX += stepX;
		}
		else
		{
			sideDistY += deltaDistY;
			mapY += stepY;
		}
		if (map->grid[mapX][mapY] == '1') 
        {
            printf("Encontrou parede na coluna %d, linha %d\n", mapX, mapY);   
            break;
        }    
	}
    end_point.x = mapX;
    end_point.y = mapY;

    return end_point; //vai dar ruim se nao acho uma parede
}