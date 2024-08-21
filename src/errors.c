/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 19:29:43 by davifern          #+#    #+#             */
/*   Updated: 2024/08/21 19:58:38 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void clean_exit(t_data *data, char *msg)
{
    printf("%s\n", msg);
    if (!data)
		exit(1);
    if(data->mlx_ptr && data->win_ptr)
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	// if (data->win && data->mlx)
	// 	mlx_destroy_window(data->mlx, data->win);
	// if (data->mlx)
	// {
	// 	mlx_destroy_display(data->mlx);
	// 	mlx_loop_end(data->mlx);
	// 	free(data->mlx);
	// }
	// free_data(data);
	// exit(code);
}