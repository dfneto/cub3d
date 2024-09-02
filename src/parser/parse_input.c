/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 10:16:57 by lsulzbac          #+#    #+#             */
/*   Updated: 2024/09/02 12:03:17 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//TODO: ao final de tudo tenho que init_the_player(data), Lucas?
void	parse_input(char *argv, t_data *data)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_read(ft_open(argv));
	while (tmp[i] && !is_textures_ok(data->textures))
	{
		check_texture_input(safe_strtrim(tmp[i], " "), data);
		i++;
	}
	while (tmp[i] && tmp[i][0] == '\0')
		i++;
	if (!tmp[i])
		ft_perror(EINVAL, "No map");
	create_square_map(tmp + i, data);
	clean_array(tmp);
	get_map_size(data);
	check_valid_char(data);
	check_closed(data);
}
