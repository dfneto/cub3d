/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:02:01 by davifern          #+#    #+#             */
/*   Updated: 2024/08/09 09:12:29 by davifern         ###   ########.fr       */
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
	int mapX = (int)player->pos_x;
	int mapY = (int)player->pos_y;

	double sideDistX;
	double sideDistY;
	double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1.0 / rayDirX); //como que a posicao do jogador (que eh de onde vem a direacao) vai gerar um delta maior ou menor?
	double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1.0 / rayDirY);
	
	double perpWallDist;
	
	int stepX;
	int stepY;

	int hit = 0;
	int side;

	if (rayDirX < 0) 
	{
		stepX = -1;
		sideDistX = (player->pos_x - mapX) * deltaDistX;
	}
	else
	{
		stepX = 1;
		sideDistX = (mapX + 1.0 - player->pos_x) * deltaDistX;
	}
	if (rayDirY > 0)
	{
		stepY = -1;
		sideDistY = (player->pos_y - mapY) * deltaDistY;
	}
	else
	{
		stepY = 1;
		sideDistY = (mapY + 1.0 - player->pos_y) * deltaDistY;
	}

	while (hit == 0)
	{
		if (sideDistX < sideDistY)
		{
			sideDistX += deltaDistX;
			mapX += stepX;
			side = 0;
		}
		else
		{
			sideDistY += deltaDistY;
			mapY += stepY;
			side = 1;
		}
		if (map->grid[mapY][mapX] == '1') //TODO: por que no do lodev eh mapX, mapY?
            break; 
		// We won't know exactly where the wall was hit however, but that's not needed in this case because we won't use textured walls for now.
	}
	if(side == 0) perpWallDist = (sideDistX - deltaDistX);
    else          perpWallDist = (sideDistY - deltaDistY);

	//essa formula peguei do video do jaxi: end = start + dir * length
	end_point.x = player->pos_x + player->dir_x * perpWallDist;
    end_point.y = player->pos_y - player->dir_y * perpWallDist; //TODO: usar o y positivo, como eh no x, mas na hora de printar o pixel fazer a conversao
	end_point.distance = perpWallDist;
    return end_point;
}

//check if there is a wall in front of the player considering the sides also
int	has_wall(t_player *player)
{
	t_player *player_left = (t_player *)malloc(sizeof(t_player));
	t_player *player_right = (t_player *)malloc(sizeof(t_player));

	player_left->win = player->win;
	player_left->pos_x = player->pos_x;
	player_left->pos_y = player->pos_y;
	player_left->dir_x = player->dir_x * cos(6*ROT_SPEED) - player->dir_y * sin(6*ROT_SPEED);
	player_left->dir_y = player->dir_x * sin(6*ROT_SPEED) + player->dir_y * cos(6*ROT_SPEED);

	player_right->pos_x = player->pos_x;
	player_right->pos_y = player->pos_y;
	player_right->dir_x = player->dir_x * cos(-6*ROT_SPEED) - player->dir_y * sin(-6*ROT_SPEED);
	player_right->dir_y = player->dir_x * sin(-6*ROT_SPEED) + player->dir_y * cos(-6*ROT_SPEED);
	player_right->win = player->win;
	if (dda_collision_detection_lodev(player, player->win->map).distance <= 0.2 || 
		dda_collision_detection_lodev(player_left, player->win->map).distance <= 0.7 ||
		dda_collision_detection_lodev(player_right, player->win->map).distance <= 0.7)
		return 1;
	return 0;
}