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
	int col = (int)player->x;
	int row = (int)player->y;
    // printf("Posição inicial: coluna %d, linha %d\n", mapX, mapY);   

	double sideDistX;
	double sideDistY;

	double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1.0 / rayDirX);
	double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1.0 / rayDirY);
    // printf("deltaDistX %f, deltaDistY %f\n", deltaDistX, deltaDistY);   
	
	int stepX;
	int stepY;

	int hit = 0;

	if (rayDirX < 0) 
	{
		stepX = -1;
		sideDistX = (player->x - col) * deltaDistX;
		// printf("rayDirX < 0, sideDistX = %.2f\n", sideDistX);
	}
	else //aqui
	{
		stepX = 1;
		sideDistX = (col + 1.0 - player->x) * deltaDistX;
		// printf("rayDirX >= 0, sideDistX = %.2f\n", sideDistX);
	}
	if (rayDirY > 0) //aqui
	{
		stepY = -1;
		sideDistY = (player->y - row) * deltaDistY;
		// printf("rayDirY > 0, sideDistY = %.2f\n", sideDistY);
	}
	else
	{
		stepY = 1;
		sideDistY = (row + 1.0 - player->y) * deltaDistY;
		// printf("rayDirY <= 0, sideDistY = %.2f\n", sideDistY);
	}

	while (hit == 0) //enquanto não bateu na parede
	{
		if (sideDistX < sideDistY)
		{
			sideDistX += deltaDistX;
			col += stepX;
			printf("mapX = %d\n", col);
		}
		else
		{
			sideDistY += deltaDistY;
			row += stepY;
			printf("grid[%d][%d] = %c, mapY = %d\n", row, col, map->grid[col][row], row);
		}
		if (map->grid[row][col] == '1') 
        {
            printf("Encontrou parede na coluna %d, linha %d\n", col, row);   
            break;
        }    
	}
    end_point.x = col;
    end_point.y = row;

    return end_point; //vai dar ruim se nao achar uma parede
}