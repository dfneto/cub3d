/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 10:24:24 by lsulzbac          #+#    #+#             */
/*   Updated: 2024/08/28 15:32:53 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_square_map(char **tmp, t_data *data)
{
	size_t	width;
	int		height;

	width = 0;
	height = 0;
	while (tmp[height])
	{
		if (tmp[height][0] == '\0')
			ft_perror(EINVAL, "Space between map");
		if (ft_strlen(tmp[height]) > width)
			width = ft_strlen(tmp[height]);
		height++;
	}
	data->map = (char **)safe_calloc(height + 1, sizeof(char *));
	while (--height >= 0)
	{
		data->map[height] = (char *)safe_calloc(1, sizeof(char) * (width + 1));
		ft_memset(data->map[height], '0', width);
		ft_memcpy(data->map[height], tmp[height], ft_strlen(tmp[height]));
	}
}

void	add_to_count(t_data *data, int i, int j)
{
	if (data->map[i][j] != 'N' && data->map[i][j] != 'S'
		&& data->map[i][j] != 'W' && data->map[i][j] != 'E')
		return ;
	data->player_grid_direction = data->map[i][j];
	data->player_grid_x = j;
	data->player_grid_y = i;
	data->number_of_players += 1;
	data->map[i][j] = '0';
}

int	check_char(char c)
{
	int	i;

	i = 0;
	while (VALID_CHAR[i])
	{
		if (c == VALID_CHAR[i])
			return (0);
		i++;
	}
	return (1);
}

void	check_valid_char(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map_h - 1)
	{
		j = 0;
		while (j < data->map_w - 1)
		{
			if (check_char(data->map[i][j]))
				ft_perror(EINVAL, "Char not allowed");
			add_to_count(data, i, j);
			j++;
		}
		i++;
	}
	if (data->number_of_players > 1)
		ft_perror(EINVAL, "More than one player found");
	if (data->number_of_players < 1)
		ft_perror(EINVAL, "No player found");
}

void	get_map_size(t_data *data)
{
	int	i;

	i = 0;
	data->map_w = ft_strlen(data->map[0]);
	while (data->map[i] != NULL)
	{
		data->map_h += 1;
		i++;
	}
}
