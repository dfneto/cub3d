/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:47:14 by davifern          #+#    #+#             */
/*   Updated: 2024/08/28 15:35:49 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img *loadTexture(void *mlx, char *file_path, int *width, int *height)
{
    t_img *img = (t_img *)malloc(sizeof(t_img));
    img->img_ptr = mlx_xpm_file_to_image(mlx, file_path, width, height);
    
    if (!img)
    {
        printf("Failed to load texture: %s\n", file_path);
        exit(1);
    }

    img->addr = mlx_get_data_addr(img->img_ptr, &(img->bpp),
			&(img->line_len), &(img->endian));
    return img;
} 
