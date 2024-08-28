/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:04:23 by davifern          #+#    #+#             */
/*   Updated: 2024/08/28 10:44:47 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_data(t_data *data, char *argv)
{
	init_window_and_image(data);
	parse_input(argv, data);
/* 	print_map_grid(data);
	invert_grid(data);
	print_map_grid(data); */
	//init_map(data, argv);
	init_player(data);
	//init_texture(data);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	//VER COMO FAZER PARA INICIAR AS ESTRUTURAS
	ft_bzero(&data, sizeof(t_data)); //TODO: necessario??
	data.textures = (t_texture *)safe_calloc(1, sizeof(t_texture));
	data.ray = (t_ray *)safe_calloc(1, sizeof(t_ray));
	if (argc != 2)
		ft_perror(EINVAL, "./cub3d [MAP.cub]");
	init_data(&data, argv[1]);
	set_hooks(&data);
	render(&data);
	mlx_loop(data.mlx_ptr);
	mlx_destroy_image(data.mlx_ptr, data.img->img_ptr); //TODO: necessário?
	return (0);
}
//TODO:     1 (48 bytes) ROOT LEAK: <CFString 0x7fbf53730590> [48]  length: 26  "Copyright Apple Inc., 2019"