/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:04:23 by davifern          #+#    #+#             */
/*   Updated: 2024/07/08 10:02:47 by davifern         ###   ########.fr       */
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
    t_win	window;
    t_img   img; //vetor de pixels que será plotado depois

(void)argc;
(void)argv;
    if (parse_map())
        return (err(ERROR_PARSING));
    //https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html#initialization
    window.mlx_ptr = mlx_init();
	if (!window.mlx_ptr)
		return (1);
	window.win_ptr = mlx_new_window(window.mlx_ptr, WIDTH, HEIGHT, "CUB3D");
	if (!window.win_ptr)
		return (2);
	img.img_ptr = mlx_new_image(window.mlx_ptr, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img_ptr, &img.bpp,
			&img.line_len, &img.endian);
    img.win = &window;
    plot_game_board(&img);
    mlx_loop(window.mlx_ptr);
    return (0);
}
