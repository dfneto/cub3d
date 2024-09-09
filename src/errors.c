/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 19:29:43 by davifern          #+#    #+#             */
/*   Updated: 2024/09/09 18:43:50 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(t_data *data)
{
	int	i;

	i = 0;
	while (i <= data->map_h)
		free(data->map[i++]);
	free(data->map);
}

//O mais correto seria antes de fazer qualquer free verificar
//se o ponteiro nao aponta para NULL
void	free_textures(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->textures->north->img_ptr);
	free(data->textures->north);
	mlx_destroy_image(data->mlx_ptr, data->textures->south->img_ptr);
	free(data->textures->south);
	mlx_destroy_image(data->mlx_ptr, data->textures->east->img_ptr);
	free(data->textures->east);
	mlx_destroy_image(data->mlx_ptr, data->textures->west->img_ptr);
	free(data->textures->west);
	free(data->textures->floor);
	free(data->textures->ceiling);
	free(data->textures);
}

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	free(data->ray);
	while (i < WIDTH)
		free(data->buffer[i++]);
	if (data->map)
		free_map(data);
	if (data->textures)
		free_textures(data);
	free(data->buffer);
	free(data->tile);
	free(data->player);
	mlx_destroy_image(data->mlx_ptr, data->img->img_ptr);
	free(data->img);
}

void	clean_exit(t_data *data, char *msg)
{
	printf("%s\n", msg);
	if (!data)
		exit(1);
	free_data(data);
	if (data->mlx_ptr && data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		mlx_loop_end(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	exit(0);
}
