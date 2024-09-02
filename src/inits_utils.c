/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:33:57 by davifern          #+#    #+#             */
/*   Updated: 2024/09/02 12:35:57 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_to_north_or_south(t_player *player, double dir)
{
	if (dir == 'N')
	{
		player->dir_x = 0.0;
		player->dir_y = 1.0;
		player->plane_x = 0.66;
		player->plane_y = 0.0;
	}
	else
	{
		player->dir_x = 0.0;
		player->dir_y = -1.0;
		player->plane_x = -0.66;
		player->plane_y = 0;
	}
}

void	set_to_east_or_west(t_player *player, double dir)
{
	if (dir == 'E')
	{
		player->dir_x = 1.0;
		player->dir_y = 0.0;
		player->plane_x = 0;
		player->plane_y = -0.66;
	}
	else
	{
		player->dir_x = -1.0;
		player->dir_y = 0.0;
		player->plane_x = 0;
		player->plane_y = 0.66;
	}
}
