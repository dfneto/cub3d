/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 19:23:03 by davifern          #+#    #+#             */
/*   Updated: 2024/08/28 15:32:17 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Swap the map grid rows: the last will be the first,
// the penultimate the second and so on
void    invert_grid(t_data *data)
{
    data->player_grid_y = data->map_h - data->player_grid_y - 1;
    for (int i = 0; i <  data->map_h / 2; i++) {
        for (int j = 0; j < data->map_w ; j++) {
            char temp = data->map[i][j];
            data->map[i][j] = data->map[data->map_h  - 1 - i][j];
            data->map[data->map_h  - 1 - i][j] = temp;
        }
    }
}
/* 
int parse_map(t_map *map)
{
    *map = (t_map){
        .grid = {
        {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
        {'1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '2', '0', '1'},
        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
        {'1', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '3', '0', '1'},
        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '1'},
        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
        {'1', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
        {'1', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '1'},
        {'1', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
        {'1', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '4', '0', '1'},
        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
        {'1', 'N', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
        {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}
        }
    };
    return 0;
} */

//Create the window and the image 
//https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html#initialization
void    init_window_and_image(t_data *data)
{  
    t_img       *img;
    
    data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
        clean_exit(data, "Fail to initialize mlxn\n");
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "CUB3D");
	if (!data->win_ptr)
		clean_exit(data, "Fail to create the window\n");
    img = malloc(sizeof(t_img));
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
void    set_player_direction_and_plane(t_player *player, char dir)
{
    if (dir == 'N')
    {
        player->dir_x = 0.0;
        player->dir_y = 1.0;
        player->planeX = 0.66;
        player->planeY = 0.0;
    }
    else if (dir == 'S')
    {
        player->dir_x = 0.0;
        player->dir_y = -1.0;
        player->planeX = -0.66;
        player->planeY = 0;
    }
    else if (dir == 'E')
    {
        player->dir_x = 1.0;
        player->dir_y = 0.0;
        player->planeX = 0;
        player->planeY = -0.66;
    }
    else if (dir == 'W')
    {
        player->dir_x = -1.0;
        player->dir_y = 0.0;
        player->planeX = 0;
        player->planeY = 0.66;
    }
}

//TODO: acho que não é necessário malloc se eu colocar o data->player no lugar
//O vetor posição x e y são as colunas e linhas do grid 
//e não coordenadas cartesianas. +0.5 pra ficar no meio de um quadrado
void    init_player(t_data *data)
{
    data->player = (t_player *)safe_calloc(1, sizeof(t_player)); //Troquei malloc por safe_malloc, ai nao precisa testar para null
    data->player->pos_x = data->player_grid_x + 0.5;
    data->player->pos_y = data->player_grid_y + 0.5;
    data->player->size = PLAYER_SIZE;
    set_player_direction_and_plane(data->player, data->player_grid_direction);
}

void    init_ray(t_ray *ray)
{
    ray->rayDirX = 0.0;
    ray->rayDirY = 0.0;
    ray->cameraX = 0.0;
    ray->deltaDistX = 0.0;
    ray->deltaDistY = 0.0;
    ray->sideDistX = 0.0;
    ray->sideDistY = 0.0;
    ray->wall_distance = 0.0;
    ray->hit = 0;
    ray->mapX = 0;
    ray->mapY = 0;
    ray->stepX = 0;
    ray->stepY = 0;
    ray->side = 0;
}
