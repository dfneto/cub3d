/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:04:23 by davifern          #+#    #+#             */
/*   Updated: 2024/08/07 14:57:48 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int         dimension_2d = 1;

int err(char *str)
{
    printf("%s\n", str);
    return (1);
}


int parse_map(t_map *map)
{
    *map = (t_map){
        .grid = {
        {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'N', '1'},
        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
        {'1', '0', 'M', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},   
        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
        {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}
        }
    };
    printf("[3][2] = %c\n", map->grid[3][2]); //M
    printf("[22][1] = %c\n", map->grid[22][1]); //N
    return 0;
}

/* ver sobre cores e estudar bitshft e hexadecimal em:
https://harm-smits.github.io/42docs/libs/minilibx/colors.html
https://gontjarow.github.io/MiniLibX/mlx-tutorial-draw-pixel.html
https://gontjarow.github.io/MiniLibX/mlx_pixel_put.html
int rgb_to_int(double r, double g, double b)
{
    int color = 0;
    color |= (int)(b * 255);
    color |= (int)(g * 255) << 8;
    color |= (int)(r * 255) << 16;
    return (color);
}
*/


void    temp(t_win *win)
{
    // draw_map_walls(win->img, win->map);
    // my_mlx_pixel_put(win->img, 600, 230, RED);
    draw_player(win->img, win->player);
    // draw_player_direction_line(win->img, win->player, win->player->x, win->player->y, BLUE);
    
    mlx_put_image_to_window(win->mlx_ptr,
		win->win_ptr, win->img->img_ptr, 0, 0);
}


int main()
{
    t_win	    win;
    t_img       img; //vetor de pixels que será plotado depois
    t_player    player; //TODO: devo criar um malloc? Pq sim ou pq não?
    t_map       *map = (t_map *)malloc(sizeof(t_map)); //TODO: precisa de malloc? E pq win e img não precisam?
    
    if (parse_map(map))
        return (err(ERROR_PARSING));
    
    // print_map_grid(map);

    //Create the window and the image https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html#initialization
    win.mlx_ptr = mlx_init();
	if (!win.mlx_ptr)
		return (1);
	win.win_ptr = mlx_new_window(win.mlx_ptr, WIDTH, HEIGHT, "CUB3D");
	if (!win.win_ptr)
		return (2);
	img.img_ptr = mlx_new_image(win.mlx_ptr, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img_ptr, &img.bpp,
			&img.line_len, &img.endian);
    
    player = create_player(map); 

    //make the associations
    img.win = &win;
    win.img = &img;
    win.player = &player;
    win.map = map;
    win.height = 24;
    win.width = 24;
    win.zoom = 32;
    player.win = &win;
    
    set_hooks(&win);
    // if (dimension_2d)
        // draw_everything_2d(&win); //to draw the game in 2D
    // else
    //     draw_everything_3d(&win);

    temp(&win);


    mlx_loop(win.mlx_ptr);
    return (0);
}
//TODO:     1 (48 bytes) ROOT LEAK: <CFString 0x7fbf53730590> [48]  length: 26  "Copyright Apple Inc., 2019"
