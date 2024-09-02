/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:35:57 by davifern          #+#    #+#             */
/*   Updated: 2024/09/02 10:37:14 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_position_forward(t_player *player, double *next_x, double *next_y)
{
	*next_x = player->pos_x + player->dir_x * PLAYER_SPEED;
	*next_y = player->pos_y + player->dir_y * PLAYER_SPEED;
}

void	calculate_position_back(t_player *player, double *next_x, double *next_y)
{
	*next_x = player->pos_x - player->dir_x * PLAYER_SPEED;
	*next_y = player->pos_y - player->dir_y * PLAYER_SPEED;
}

void	calculate_position_left(t_player *player, double *next_x, double *next_y)
{
	*next_x = player->pos_x - player->dir_y * PLAYER_SPEED;
	*next_y = player->pos_y + player->dir_x * PLAYER_SPEED;
}

void	calculate_position_right(t_player *player, double *next_x, double *next_y)
{
	*next_x = player->pos_x + player->dir_y * PLAYER_SPEED;
	*next_y = player->pos_y - player->dir_x * PLAYER_SPEED;
}

int	is_next_position_valid(t_data *data, double next_x, double next_y)
{
	if (next_x < 0.25 || next_y < 0.25
		|| next_y >= data->map_h
		|| next_x >= data->map_w)
		return (0);
	return (1);
}