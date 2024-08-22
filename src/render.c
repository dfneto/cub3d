/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:18:57 by davifern          #+#    #+#             */
/*   Updated: 2024/08/22 13:21:47 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    render(t_data *data)
{
    draw_everything_3d_texture(data);
    draw_minimap(data);
    mlx_put_image_to_window(data->mlx_ptr,
		  data->win_ptr, data->img->img_ptr, 0, 0);
}