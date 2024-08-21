/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:04:23 by davifern          #+#    #+#             */
/*   Updated: 2024/08/21 20:10:15 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    init_data(t_data *data)
{
    init_window_and_image(data);
    init_map(data);
    init_player(data);
}

int main()
{
    t_data      data;
    
    init_data(&data);
    set_hooks(&data);
    // draw_everything_3d_texture(&data);
    draw_minimap(&data);
    mlx_put_image_to_window(data.mlx_ptr,
		  data.win_ptr, data.img->img_ptr, 0, 0);
    mlx_loop(data.mlx_ptr);
    mlx_destroy_image(data.mlx_ptr, data.img->img_ptr); //TODO: necessário?
    return (0);
}
//TODO:     1 (48 bytes) ROOT LEAK: <CFString 0x7fbf53730590> [48]  length: 26  "Copyright Apple Inc., 2019"
