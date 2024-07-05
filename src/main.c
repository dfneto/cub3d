/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:04:23 by davifern          #+#    #+#             */
/*   Updated: 2024/07/05 15:23:27 by davifern         ###   ########.fr       */
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

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

int main(int argc, char **argv)
{
    // t_cub   *cub;
    t_win	window;
    t_img   img;

(void)argc;
(void)argv;
    if (parse_map())
        return (err(ERROR_PARSING));
    window.mlx_ptr = mlx_init();
	if (!window.mlx_ptr)
		return (1);
	window.win_ptr = mlx_new_window(window.mlx_ptr, WIDTH, HEIGHT, "CUB3D");
	if (!window.win_ptr)
		return (2);
	img.img_ptr = mlx_new_image(window.mlx_ptr, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img_ptr, &img.bpp,
			&img.line_len, &img.endian);
    my_mlx_pixel_put(&img, 150, 150, 0x00FF0000);
    mlx_put_image_to_window(window.mlx_ptr, window.win_ptr, img.img_ptr, 0, 0);

    mlx_loop(window.mlx_ptr);
    return (0);
}