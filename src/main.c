/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:04:23 by davifern          #+#    #+#             */
/*   Updated: 2024/08/23 13:14:57 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_data(t_data *data)
{
	init_window_and_image(data);
	init_map(data);
	init_player(data);
	init_texture(data);
}

int	main()
{
	t_data	data;

	init_data(&data);
	set_hooks(&data);
	render(&data);
	mlx_loop(data.mlx_ptr);
	mlx_destroy_image(data.mlx_ptr, data.img->img_ptr); //TODO: necessário?
	return (0);
}
//TODO:     1 (48 bytes) ROOT LEAK: <CFString 0x7fbf53730590> [48]  length: 26  "Copyright Apple Inc., 2019"