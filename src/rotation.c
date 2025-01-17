/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 13:50:18 by davifern          #+#    #+#             */
/*   Updated: 2024/09/02 12:35:57 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// x = x * cs(ang) - y * sn(ang); ang eh o angulo que quero rotacionar
// y = x * sn(ang) + y * cs(ang);
void	rotate_left_right(t_player *p, double rot_speed)
{
	double		old_dir_x;
	double		old_plane_x;

	old_dir_x = p->dir_x;
	p->dir_x = p->dir_x * cos(rot_speed) - p->dir_y * sin(rot_speed);
	p->dir_y = old_dir_x * sin(rot_speed) + p->dir_y * cos(rot_speed);
	old_plane_x = p->plane_x;
	p->plane_x = p->plane_x * cos(rot_speed) - p->plane_y * sin(rot_speed);
	p->plane_y = old_plane_x * sin(rot_speed) + p->plane_y * cos(rot_speed);
}
