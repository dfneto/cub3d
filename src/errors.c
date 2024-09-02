/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 19:29:43 by davifern          #+#    #+#             */
/*   Updated: 2024/09/02 11:27:48 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//TODO: colocar isso?
// if (data->mlx)
// {
// 	mlx_destroy_display(data->mlx);
// 	mlx_loop_end(data->mlx);
// 	free(data->mlx);
// }
// free_data(data);
// exit(code);
void	clean_exit(t_data *data, char *msg)
{
	printf("%s\n", msg);
	if (!data)
		exit(1);
	if (data->mlx_ptr && data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
}
