/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 19:23:03 by davifern          #+#    #+#             */
/*   Updated: 2024/09/12 14:27:21 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Swap the map grid rows: the last will be the first,
// the penultimate the second and so on
void	invert_grid(t_data *data)
{
	int		i;
	int		j;
	char	temp;

	i = 0;
	data->player_grid_y = data->map_h - data->player_grid_y - 1;
	while (i < data->map_h / 2)
	{
		j = 0;
		while (j < data->map_w)
		{
			temp = data->map[i][j];
			data->map[i][j] = data->map[data->map_h - 1 - i][j];
			data->map[data->map_h - 1 - i][j] = temp;
			j++;
		}
		i++;
	}
}

//Create the window and the image 
//Ver: https://harm-smits.github.io/42docs/
//libs/minilibx/getting_started.html#initialization
void	init_window_and_image(t_data *data)
{
	t_img	*img;

	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		clean_exit(data, "Fail to initialize mlxn\n");
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "CUB3D");
	if (!data->win_ptr)
		clean_exit(data, "Fail to create the window\n");
	img = safe_calloc(1, sizeof(t_img));
	img->img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	if (!img->img_ptr)
		clean_exit(data, "Fail to create the image\n");
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp,
			&img->line_len, &img->endian);
	if (!img->addr)
		clean_exit(data, "Fail to get the image address\n");
	data->img = img;
}

//N: [0 1], W: [-1 0], S: [0 -1], O: [1  0]
void	set_player_direction_and_plane(t_player *player, char dir)
{
	if (dir == 'N' || dir == 'S')
		set_to_north_or_south(player, dir);
	else
		set_to_east_or_west(player, dir);
}

//O vetor posição x e y são as colunas e linhas do grid 
//e não coordenadas cartesianas. +0.5 pra ficar no meio de um quadrado
//Em data->player: troquei malloc por safe_malloc, ai nao precisa
//testar para null
void	init_player(t_data *data)
{
	data->player = (t_player *)safe_calloc(1, sizeof(t_player));
	data->player->pos_x = data->player_grid_x + 0.5;
	data->player->pos_y = data->player_grid_y + 0.5;
	data->player->size = PLAYER_SIZE;
	set_player_direction_and_plane(data->player, data->player_grid_direction);
}

void	init_ray(t_ray *ray)
{
	ray->ray_dir_x = 0.0;
	ray->ray_dir_y = 0.0;
	ray->camera_x = 0.0;
	ray->delta_dist_x = 0.0;
	ray->delta_dist_y = 0.0;
	ray->side_dist_x = 0.0;
	ray->side_dist_y = 0.0;
	ray->wall_distance = 0.0;
	ray->map_x = 0;
	ray->map_y = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->side = 0;
	ray->line_height = 0;
	ray->draw_end = 0;
	ray->draw_start = 0;
}
