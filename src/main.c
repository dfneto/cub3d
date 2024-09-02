/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:04:23 by davifern          #+#    #+#             */
/*   Updated: 2024/09/02 11:44:33 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//TODO: necessario um safe calloc?
void	init_data(t_data *data, char *argv)
{
	int	i;

	i = 0;
	data->textures = (t_textures *)safe_calloc(1, sizeof(t_textures));
	data->ray = (t_ray *)safe_calloc(1, sizeof(t_ray));
	data->buffer = (int **)malloc(HEIGHT * sizeof(int *));
	while (i < WIDTH)
	{
		data->buffer[i] = (int *)malloc(WIDTH * sizeof(int));
		i++;
	}
	init_window_and_image(data);
	parse_input(argv, data);
	init_player(data);
}

//VER COMO FAZER PARA INICIAR AS ESTRUTURAS. Pq?
// ft_bzero(&data, sizeof(t_data)); //TODO: necessario??
//mlx_destroy_image(data.mlx_ptr, data.img->img_ptr); //TODO: necessário?
int	main(int argc, char *argv[])
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	if (argc != 2)
		ft_perror(EINVAL, "./cub3d [MAP.cub]");
	init_data(&data, argv[1]);
	set_hooks(&data);
	render(&data);
	mlx_loop(data.mlx_ptr);
	mlx_destroy_image(data.mlx_ptr, data.img->img_ptr);
	return (0);
}
