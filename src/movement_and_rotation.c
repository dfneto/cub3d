/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_and_rotation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 13:50:18 by davifern          #+#    #+#             */
/*   Updated: 2024/08/30 14:26:34 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// x = x * cs(ang) - y * sn(ang); ang eh o angulo que quero rotacionar
// y = x * sn(ang) + y * cs(ang);
void	rotate_right(t_player *p)
{
	double		old_dir_x;
	double		old_plane_x;

	old_dir_x = p->dir_x;
	p->dir_x = p->dir_x * cos(-ROT_SPEED) - p->dir_y * sin(-ROT_SPEED);
	p->dir_y = old_dir_x * sin(-ROT_SPEED) + p->dir_y * cos(-ROT_SPEED);
	old_plane_x = p->planeX;
	p->planeX = p->planeX * cos(-ROT_SPEED) - p->planeY * sin(-ROT_SPEED);
	p->planeY = old_plane_x * sin(-ROT_SPEED) + p->planeY * cos(-ROT_SPEED);
}

void	rotate_left(t_player *p)
{
	double		old_dir_x;
	double		old_plane_x;

	old_dir_x = p->dir_x;
	p->dir_x = p->dir_x * cos(ROT_SPEED) - p->dir_y * sin(ROT_SPEED);
	p->dir_y = old_dir_x * sin(ROT_SPEED) + p->dir_y * cos(ROT_SPEED);
	old_plane_x = p->planeX;
	p->planeX = p->planeX * cos(ROT_SPEED) - p->planeY * sin(ROT_SPEED);
	p->planeY = old_plane_x * sin(ROT_SPEED) + p->planeY * cos(ROT_SPEED);
}

int	is_next_position_valid(t_data *data, double next_x, double next_y)
{
	if (next_x < 0.25 || next_y < 0.25
		|| next_y >= data->map_h
		|| next_x >= data->map_w)
		return (0);
	return (1);
}

void	calculate_next_position(int keycode, t_player *player,
	double *next_x, double *next_y)
{
	if (keycode == KEY_W_M || keycode == KEY_W_L)
	{
		*next_x = player->pos_x + player->dir_x * PLAYER_SPEED;
		*next_y = player->pos_y + player->dir_y * PLAYER_SPEED;
	}
	else if (keycode == KEY_S_M || keycode == KEY_S_L)
	{
		*next_x = player->pos_x - player->dir_x * PLAYER_SPEED;
		*next_y = player->pos_y - player->dir_y * PLAYER_SPEED;
	}
	else if (keycode == KEY_D_M || keycode == KEY_D_L)
	{
		*next_x = player->pos_x + player->dir_y * PLAYER_SPEED;
		*next_y = player->pos_y - player->dir_x * PLAYER_SPEED;
	}
	else if (keycode == KEY_A_M || keycode == KEY_A_L)
	{
		*next_x = player->pos_x - player->dir_y * PLAYER_SPEED;
		*next_y = player->pos_y + player->dir_x * PLAYER_SPEED;
	}
}

void	make_move(int keycode, t_data *data)
{
	double		next_x;
	double		next_y;
	t_player	*player;

	next_x = 0.0;
	next_y = 0.0;
	player = data->player;
	calculate_next_position(keycode, player, &next_x, &next_y);
	if (is_next_position_valid(data, next_x, next_y))
	{
		player->pos_x = next_x;
		player->pos_y = next_y;
	}
}
