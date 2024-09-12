/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture_pixels.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:45:06 by davifern          #+#    #+#             */
/*   Updated: 2024/09/12 15:30:05 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//Returns the pixel from the texture image loaded.
//To get or set the value of the pixel (5, 100) in an image size of (500, 500),
//we would need to locate the position as follows:
// int pos = (y * size_line + x * (bits_per_pixel / 8));
//Here we multiply size_line by y as we need to skip y lines (and yes, line 
//size is not equal to the amount of pixels in a line). We then add the 
//remaining x units multiplied by bits_per_pixel / 8 to align with the final
// location.
//Entendo da seguinte forma: eu localizo a posição do pixel na imagem, mas 
// essa posição é relativa, tipo linha 4, coluna 5 (4,5). Então com o endereço
// de memória da imagem eu posso ir na linha4, coluna 5 e para isso somo essa
// posição pos ao endereço adr.
//É uma aritmética de ponteiro
//(unsigned int *)ptr casts the char * to an unsigned int *, 
//meaning that it treats the memory at ptr as if it were storing an unsigned 
// int.
//(unsigned int *)ptr dereferences the pointer, giving you 
//the unsigned int value stored at that memory location.
//64 é o tamanho da textura. Para que o y cresça da mesma forma que num 
//plano cartesiano (y cresce à medida que sobe e não o contrário como ocorre
//na minilibx) tenho que printar o y invertido (maior y - y atual)
unsigned int	get_texture_pixel(t_img *texture, int pixel_x, int pixel_y)
{
	int	pos;

	pixel_y = TEXHEIGHT - pixel_y - 1;
	pos = (pixel_y * texture->line_len + pixel_x * (texture->bpp / 8));
	return (*(unsigned int *)((texture->addr + pos)));
}

//sem isso fica invertido o west e east
int	invert_if_west_or_east(int tex_x, int side)
{
	if (side == 0)
		return (TEXWIDTH - tex_x - 1);
	return (tex_x);
}

int	make_color_darker_for_y_sides(int side, int texture_pixel)
{
	if (side == 1)
		return (texture_pixel >> 1 & 8355711);
	return (texture_pixel);
}

//Set the pixels to the buffer to be printed at once
//step: how much to increase the texture coordinate per screen pixel: 
//porque veja, eu tenho uma textura de
//texHeight (64px no caso) de altura e tenho que desenhar uma linha vertical
//na tela (que vai ser o 3D do raycasting)
//que pode ser maior ou menor do que esses 64px. Não basta copiar uma coluna da
// textura e colocar na tela.
//Agora o que não entendo eh por que o texY não vai de 0 a 64. Acho que deveria
//pegar toda a linha vertical da textura e 
//desenhar na tela, aumentando/diminuindo de acordo com o tamanho que essa 
//linha deve ter na tela
//line_height eh um valor grande, porque dividi o HEIGHT da tela pelo 
//perpWallDist. Então o step será um valor pequeno
//tex_x: eh o x da textura de onde bateu o raio na parede.
void	set_wall_texture_pixels(t_ray *ray,
	int **buffer, int x, t_data *data)
{
	int		y;
	int		texture_pixel;
	double	step;
	double	tex_pos;
	t_img	*texture;

	texture = define_wall_texture(ray, data->textures);
	data->tex_x = (int)(ray->wall_x * (double)TEXWIDTH);
	data->tex_x = invert_if_west_or_east(data->tex_x, ray->side);
	step = 1.0 * TEXHEIGHT / ray->line_height;
	tex_pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		data->tex_y = (int)tex_pos & (TEXHEIGHT - 1);
		tex_pos += step;
		texture_pixel = get_texture_pixel(texture, data->tex_x, data->tex_y);
		texture_pixel = make_color_darker_for_y_sides(ray->side, texture_pixel);
		buffer[y][x] = texture_pixel;
		y++;
	}
}
