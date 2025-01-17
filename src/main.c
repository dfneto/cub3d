/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:04:23 by davifern          #+#    #+#             */
/*   Updated: 2024/09/12 15:31:15 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//O safe calloc verifica se o ponteiro eh nulo e se nao for chama o ft_bzero.
//Uso quando vou verificar se o ponteiro eh nulo ou se quero ja inicializar
//todas as variaveis do ponteiro a zero
void	init_data(t_data *data, char *argv)
{
	int	i;

	i = 0;
	data->textures = (t_textures *)safe_calloc(1, sizeof(t_textures));
	data->ray = (t_ray *)safe_calloc(1, sizeof(t_ray));
	data->buffer = (int **)safe_malloc(HEIGHT * sizeof(int *));
	while (i < WIDTH)
	{
		data->buffer[i] = (int *)safe_malloc(WIDTH * sizeof(int));
		i++;
	}
	init_window_and_image(data);
	parse_input(argv, data);
	init_player(data);
}


// ft_bzero(&data, sizeof(t_data));
//mlx_destroy_image(data.mlx_ptr, data.img->img_ptr) não é necessário
//porque para o programa sair tem que dar esc que detrói tudo
//ft_bzero: para garantir que os ponteiros e todas as variaveis sejam NULL e 0.
int	main(int argc, char *argv[])
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	data.i = 0;
	if (argc != 2)
		ft_perror(EINVAL, "./cub3d [MAP.cub]");
	init_data(&data, argv[1]);
	set_hooks(&data);
	render(&data);
	mlx_loop_hook(data.mlx_ptr, render_if_moved, &data);
	mlx_loop(data.mlx_ptr);
	mlx_destroy_image(data.mlx_ptr, data.img->img_ptr);
	return (0);
}
