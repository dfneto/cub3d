/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:04:23 by davifern          #+#    #+#             */
/*   Updated: 2024/07/11 11:18:54 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int err(char *str)
{
    printf("%s\n", str);
    return (1);
}


int parse_map()
{
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

int main(int argc, char **argv)
{
    t_win	    win;
    t_img       img; //vetor de pixels que será plotado depois
    t_player    player;

    (void)argc;
    (void)argv;
    
    if (parse_map())
        return (err(ERROR_PARSING));
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
    
    //create the player
    player.x = 65;
    player.y = 350;
    player.size = 30;
    player.speed = 5;
    player.dir_x = 0.0;
    player.dir_y = 1.0;
    player.direction_line_size = 200;

    //make the associations
    img.win = &win;
    win.img = &img;
    win.player = &player;
    
    draw_game_board(&img, &player);
    

    set_hooks(&win);

    mlx_loop(win.mlx_ptr);
    return (0);
}
//TODO:     1 (48 bytes) ROOT LEAK: <CFString 0x7fbf53730590> [48]  length: 26  "Copyright Apple Inc., 2019"
