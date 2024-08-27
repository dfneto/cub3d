/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsulzbac <lsulzbac@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 10:19:30 by lsulzbac          #+#    #+#             */
/*   Updated: 2024/03/16 10:19:31 by lsulzbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_textures_ok(t_texture *tex)
{
	return (tex->ceiling && tex->floor && tex->north && tex->south && tex->west
		&& tex->east);
}

void	add_texture(char *tok, char *info, t_data *data)
{
	char	*tmp;

	if (!info)
		ft_perror(EINVAL, "Invalid texture - No path");
	tmp = ft_strtok(info, " ");
	if (!ft_strcmp(tok, "NO") && !data->textures->north)
		data->textures->north = new_file_img(tmp, data);
	else if (!ft_strcmp(tok, "SO") && !data->textures->south)
	{
		data->textures->south = new_file_img(tmp, data);
		invert_image_x(data->textures->south); //Talvez nao precise...
	}
	else if (!ft_strcmp(tok, "WE") && !data->textures->west)
	{
		data->textures->west = new_file_img(tmp, data);
		invert_image_x(data->textures->west); //Talvez nao precise...
	}
	else if (!ft_strcmp(tok, "EA") && !data->textures->east)
		data->textures->east = new_file_img(tmp, data);
	else
		ft_perror(EINVAL, "Invalid texture - Wrong identifier");
	if (ft_strtok(NULL, " "))
		ft_perror(EINVAL, "Invalid texture - Extra information in line");
}

void	add_color(char *tok, char *info, t_data *data)
{
	if (!info)
		ft_perror(EINVAL, "Invalid color - No RGB");
	if (!ft_strcmp(tok, "C") && !data->textures->ceiling)
		data->textures->ceiling = create_new_color(info);
	else if (!ft_strcmp(tok, "F") && !data->textures->floor)
		data->textures->floor = create_new_color(info);
	else
		ft_perror(EINVAL, "Color already set");
}

void	check_texture_input(char *line, t_data *data)
{
	char	*tok;

	if (line[0] == '\0')
	{
		free(line);
		return ;
	}
	tok = ft_strtok(line, " ");
	if (!ft_strcmp(tok, "C") || !ft_strcmp(tok, "F"))
		add_color(tok, ft_strtok(NULL, "\0"), data);
	else
		add_texture(tok, ft_strtok(NULL, "\0"), data);
	free(line);
}
