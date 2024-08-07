/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:23:50 by davifern          #+#    #+#             */
/*   Updated: 2024/08/07 12:24:37 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    print_map_grid(t_map *map)
{
    int i = 0;
    int j = 0;
    while (i < ROWS)
    {
        while (j < COLS)
        {
            printf("%c ", map->grid[i][j]);
            j++;
        }
        j = 0;
        i++;
        printf("\n");
    }
}