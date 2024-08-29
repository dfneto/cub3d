/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:04:23 by davifern          #+#    #+#             */
/*   Updated: 2024/08/29 15:00:50 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_data(t_data *data, char *argv)
{
	data->textures = (t_textures *)safe_calloc(1, sizeof(t_textures)); //TODO: necessario um safe calloc?
	data->ray = (t_ray *)safe_calloc(1, sizeof(t_ray));
	// buffer[HEIGHT][WIDTH]
	// data->buffer = (unsigned int **)malloc(HEIGHT * sizeof(int));
	data->buffer = (int **)malloc(HEIGHT * sizeof(int *));

	int i = 0;
	while (i < WIDTH)
	{
		// data->buffer[i] = (unsigned int *)malloc(WIDTH * sizeof(int));
		data->buffer[i] = (int *)malloc(WIDTH * sizeof(int));

		i++;
	}
	init_window_and_image(data);
	parse_input(argv, data);
	init_player(data);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	//VER COMO FAZER PARA INICIAR AS ESTRUTURAS Lucas
	ft_bzero(&data, sizeof(t_data)); //TODO: necessario?? Lucas
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