/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_everything_3d_with_texture.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 18:07:08 by davifern          #+#    #+#             */
/*   Updated: 2024/08/29 09:39:07 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//Returns the pixel from the texture image loaded.
//To get or set the value of the pixel (5, 100) in an image size of (500, 500),
//we would need to locate the position as follows:
// int pos = (y * size_line + x * (bits_per_pixel / 8));
//Here we multiply size_line by y as we need to skip y lines (and yes, line size 
//is not equal to the amount of pixels in a line). We then add the remaining x 
//units multiplied by bits_per_pixel / 8 to align with the final location.
//Entendo da seguinte forma: eu localizo a posição do pixel na imagem, mas essa posição
//é relativa, tipo linha 4, coluna 5 (4,5). Então com o endereço de memória da imagem
//eu posso ir na linha4, coluna 5 e para isso somo essa posição pos ao endereço adr.
//É uma aritmética de ponteiro
//(unsigned int *)ptr casts the char * to an unsigned int *, 
//meaning that it treats the memory at ptr as if it were storing an unsigned int.
//(unsigned int *)ptr dereferences the pointer, giving you 
//the unsigned int value stored at that memory location.
//64 é o tamanho da textura. Para que o y cresça da mesma forma que num plano cartesiano
//(y cresce à medida que sobe e não o contrário como ocorre na minilibx) tenho que printar
//o y invertido (maior y - y atual)
unsigned int	get_texture_pixel(t_img *texture, int pixel_x, int pixel_y)
{
    pixel_y = 64 - pixel_y;
    int pos = (pixel_y * texture->line_len + pixel_x * (texture->bpp / 8));
	return (*(unsigned int *)((texture->addr + pos)));
}

void render_buffer(unsigned int buffer[HEIGHT][WIDTH], t_img *img)
{
    int y = 0;
    int x = 0;
    while (y < HEIGHT)
    {
        while (x < WIDTH)
        {
            my_mlx_pixel_put(img, x, y, buffer[y][x]);
            x++;
        }
        x = 0;
        y++;
    }
}

void    clean_buffer(unsigned int buffer[HEIGHT][WIDTH])
{
    int y;
    int x;
    
    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
            buffer[y][x++] = 0;
        y++;
    }
}

t_img   *define_wall_texture(t_data *data)
{
    if(data->ray->side == 0 && data->ray->rayDirX >= 0) 
        return data->textures->east;
    if(data->ray->side == 0 && data->ray->rayDirX < 0) 
        return data->textures->west;
    if(data->ray->side == 1 && data->ray->rayDirY >= 0)
        return data->textures->north;
    return data->textures->south;
}

/*
pitch is an offset added to the vertical position of the drawn wall. 
By adding pitch, you can move the entire view up or down.
line_height is the height of the vertical line that should be drawn. 
You can of course also multiply it with another value if you want 
to walls to be higher or lower
*/
void    draw_everything_3d_texture(t_data *data)
{
    int x;
    int lineHeight;
    int pitch;
    unsigned int buffer[HEIGHT][WIDTH];
    char **grid_map;
    t_ray   *ray;
    t_player *player;
    
    player = data->player;
    grid_map = data->map;
    ray = data->ray;
    x = 0;
    while (x < WIDTH)
    {
        //calculate once, per x position
        init_ray(data->ray);
        ray->cameraX = 2 * x / (double)WIDTH - 1;
        calculate_ray_direction_and_delta(ray, player);
        ray->mapX = (int)player->pos_x;
        ray->mapY = (int)player->pos_y;
        calculate_side_dist_and_step(ray, player);
        while (ray->hit == 0)
            calculate_side_dist_ray_position_and_side(ray, grid_map); //dda
        calculate_wall_distance(ray);

        lineHeight = (int)(HEIGHT / ray->wall_distance);
        pitch = 0; 
        //calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + HEIGHT / 2 + pitch;
        if(drawStart < 0) 
            drawStart = 0;
        int drawEnd = lineHeight / 2 + HEIGHT / 2 + pitch;
        if(drawEnd >= HEIGHT) drawEnd = HEIGHT - 1;

        //calculate value of wallX
        double wallX; //where exactly the wall was hit
        if(ray->side == 0) wallX = player->pos_y + ray->wall_distance * ray->rayDirY;
        else          wallX = player->pos_x + ray->wall_distance * ray->rayDirX;
        wallX -= floor((wallX));

        //texturing calculations (-48 para transformar de char para int)
        // int texNum = grid_map->grid[ray->mapY][ray->mapX] -48 - 1; //1 subtracted from it so that texture 0 can be used!

        //x coordinate on the texture
        int texX = (int)(wallX * (double)texWidth); //texX eh o x da textura equivalente a onde bateu o raio na parede.
        if(ray->side == 0) texX = texWidth - texX - 1; //sem isso fica invertido o west e east
        
        // How much to increase the texture coordinate per screen pixel: porque veja, eu tenho uma textura de
        // texHeight (64px no caso) de altura e tenho que desenhar uma linha vertical na tela (que vai ser o 3D do raycasting)
        // que pode ser maior ou menor do que esses 64px. Não basta copiar uma coluna da textura e colocar na tela.
        // Agora o que não entendo eh porque o texY não vai de 0 a 64. Acho que deveria pegar toda a linha vertical da textura e 
        // desenhar na tela, aumentando/diminuindo de acordo com o tamanho que essa linha deve ter na tela
        double step = 1.0 * texHeight / lineHeight; //lineHeight eh um valor grande, porque dividi o HEIGHT da tela pelo perpWallDist. Então o step será um valor pequeno
        // Starting texture coordinate
        double texPos = (drawStart - pitch - HEIGHT / 2 + lineHeight / 2) * step;
        for(int y = drawStart; y < drawEnd; y++)
        {
            // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
            int texY = (int)texPos & (texHeight - 1);
            texPos += step;
            //acho que aqui tenho que pegar o pixel da imagem da textura
            t_img *texture = define_wall_texture(data);
            unsigned int texture_pixel = get_texture_pixel(texture, texX, texY); //textures[texNum][texHeight * texY + texX]; //tenho que somar texX porque texture[texNum] eh um array e não uma matriz, entao essa eh a forma de pegar o pixel y,x (linha,coluna) da textura
            //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
            if(ray->side == 1) 
                texture_pixel = (texture_pixel >> 1) & 8355711;
            buffer[y][x] = texture_pixel;
        }



        color_floor(data, buffer, drawStart, x);
        color_ceiling(data, buffer, drawEnd, x);
        x++;
    }
    render_buffer(buffer, data->img);
    clean_buffer(buffer); //TODO: não sei se é necessário
}

/*
Calculates de perpendicular wall distance from the player to 
the wall. Side = 0 if the ray hits EW in the wall and side = 1
if it hits NS side
*/
void calculate_wall_distance(t_ray * ray)
{
    if (ray->side == 0)
        ray->wall_distance = (ray->sideDistX - ray->deltaDistX);
    else
        ray->wall_distance = (ray->sideDistY - ray->deltaDistY);
}

/*
Calculates once, per x position:
ray_dir is the ray direction. It is a vector
delta_dist_x and delta_dist_y are the distance the ray has to travel 
to go from 1 x-side to the next x-side, or from 1 y-side to the next y-side.
*/
void calculate_ray_direction_and_delta(t_ray *ray, t_player *player)
{
    ray->rayDirX = player->dir_x + player->planeX * ray->cameraX;
    ray->rayDirY = player->dir_y + player->planeY * ray->cameraX;
    ray->deltaDistX = (ray->rayDirX == 0) ? 1e30 : fabs(1 / ray->rayDirX);
    ray->deltaDistY = (ray->rayDirY == 0) ? 1e30 : fabs(1 / ray->rayDirY);
}

/*
side_distance: get incremented with deltaDistX with every jump in 
their direction, and mapX and mapY get incremented with stepX and stepY respectively. 
map_x and map_y: are the grid coordinates of the ray position and 
get incremented with step_x and step_y respectively
side: 1 if the ray intersects a NS grid line (y-side), 
0 if the ray intersects a EW grid line (x-side)
*/
void calculate_side_dist_ray_position_and_side(t_ray * ray, char **grid_map)
{
    if (ray->sideDistX < ray->sideDistY)
    {
        ray->sideDistX += ray->deltaDistX;
        ray->mapX += ray->stepX;
        ray->side = 0;
    }
    else
    {
        ray->sideDistY += ray->deltaDistY;
        ray->mapY += ray->stepY;
        ray->side = 1;
    }
    if (grid_map[ray->mapY][ray->mapX] >= '1')
        ray->hit = 1;
}

/*
Calculates once, per x position:
side_distance: is the distance the ray has to travel from 
its start position to the first x-side and the first y-side
step_x and step_y: always either -1 or +1. If the ray has 
to go in the negative or positive direction
*/
void calculate_side_dist_and_step(t_ray * ray, t_player * player)
{
    if (ray->rayDirX < 0)
    {
        ray->stepX = -1;
        ray->sideDistX = (player->pos_x - ray->mapX) * ray->deltaDistX;
    }
    else
    {
        ray->stepX = 1;
        ray->sideDistX = (ray->mapX + 1.0 - player->pos_x) * ray->deltaDistX; 
    }
    if (ray->rayDirY < 0)
    {
        ray->stepY = -1;
        ray->sideDistY = (player->pos_y - ray->mapY) * ray->deltaDistY;
    }
    else
    {
        ray->stepY = 1;
        ray->sideDistY = (ray->mapY + 1.0 - player->pos_y) * ray->deltaDistY;
    }
}
