/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_closed.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 18:44:12 by lsulzbac          #+#    #+#             */
/*   Updated: 2024/08/28 15:29:26 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**copy_map(t_data *map)
{
	int		i;
	char	**tmp_map;

	i = 0;
	tmp_map = (char **)safe_calloc((map->map_h + 1), sizeof(char *));
	while (i < map->map_h)
	{
		tmp_map[i] = safe_strdup(map->map[i]);
		i++;
	}
	return (tmp_map);
}

int	is_map_closed(t_data *map, int x, int y)
{
	if (x < 0 || y < 0 || x >= (int)map->map_w || y >= (int)map->map_h)
		return (1);
	if (map->map[y][x] == '1')
		return (0);
	map->map[y][x] = '1';
	if (is_map_closed(map, x, y - 1) || is_map_closed(map, x, y + 1)
		|| is_map_closed(map, x - 1, y) || is_map_closed(map, x + 1, y))
		return (1);
	return (0);
}

void	check_closed(t_data *data)
{
	char	**tmp_map;

	invert_grid(data);
	tmp_map = copy_map(data);
	if (is_map_closed(data, data->player_grid_x, data->player_grid_y))
		ft_perror(EINVAL, "Map not closed");
	clean_array(data->map);
	data->map = tmp_map;
}
