/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:23:50 by davifern          #+#    #+#             */
/*   Updated: 2024/08/20 08:04:09 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    print_map_grid(t_data *data)
{
    int i = 0;
    int j = 0;
    while (i < data->map_h)
    {
        while (j < data->map_w)
        {
            printf("%c ", data->map[i][j]);
            j++;
        }
        j = 0;
        i++;
        printf("\n");
    }
}

int	get_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}