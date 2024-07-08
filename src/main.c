/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:04:23 by davifern          #+#    #+#             */
/*   Updated: 2024/07/08 13:24:30 by davifern         ###   ########.fr       */
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
    t_win	win;
    t_img   img; //vetor de pixels que será plotado depois

    (void)argc;
    (void)argv;
    
    if (parse_map())
        return (err(ERROR_PARSING));
    //https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html#initialization
    win.mlx_ptr = mlx_init();
	if (!win.mlx_ptr)
		return (1);
	win.win_ptr = mlx_new_window(win.mlx_ptr, WIDTH, HEIGHT, "CUB3D");
	if (!win.win_ptr)
		return (2);
	img.img_ptr = mlx_new_image(win.mlx_ptr, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img_ptr, &img.bpp,
			&img.line_len, &img.endian);
    
    
    img.win = &win;
    win.img = &img;
    plot_game_board(&img);

    set_hooks(&win);

    mlx_loop(win.mlx_ptr);
    return (0);
}
