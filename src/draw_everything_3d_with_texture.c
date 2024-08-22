/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_everything_3d_with_texture.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 18:07:08 by davifern          #+#    #+#             */
/*   Updated: 2024/08/22 16:19:55 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


// fill all the pixels with black
void	clean_map(t_img *img)
{
	int i;
	int j;
	
	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			my_mlx_pixel_put(img, i, j, BLACK);
			j++;
		}
		i++;
	}
    //TODO: era necessario antes, talvez o seja:
	// mlx_put_image_to_window(img->win->mlx_ptr,
	// 	img->win->win_ptr, img->img_ptr, 0, 0);
}

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
unsigned int	get_texture_pixel(t_img *texture, int pixel_x, int pixel_y)
{
    pixel_y = 64 - pixel_y;
    int pos = (pixel_y * texture->line_len + pixel_x * (texture->bpp / 8));
    /*
        (unsigned int *)ptr casts the char * to an unsigned int *, meaning that it treats the memory at ptr as if it were storing an unsigned int.
        *(unsigned int *)ptr dereferences the pointer, giving you the unsigned int value stored at that memory location.
    */
	return (*(unsigned int *)((texture->addr + pos)));
}

void drawBuffer(unsigned int buffer[HEIGHT][WIDTH], t_img *img)
{ //buffer[HEIGHT][WIDTH]
    int y = 0;
    int x = 0;
    while (y < HEIGHT)
    {
        while (x < WIDTH)
        {//acho que aqui eh a imagem da tela
            my_mlx_pixel_put(img, x, y, buffer[y][x]);
            x++;
        }
        x = 0;
        y++;
    }
}

t_img *loadTexture(void *mlx, char *file_path, int *width, int *height)
{
    t_img *img = (t_img *)malloc(sizeof(t_img));
    img->img_ptr = mlx_xpm_file_to_image(mlx, file_path, width, height);
    
    if (!img)
    {
        printf("Failed to load texture: %s\n", file_path);
        exit(1);
    }

    img->addr = mlx_get_data_addr(img->img_ptr, &(img->bpp),
			&(img->line_len), &(img->endian));
    return img;
}

void generate_textures(void *mlx, t_img **texture) {
    int width, height;
    
    texture[0] = loadTexture(mlx, "textures/north.xpm", &width, &height);
    texture[1] = loadTexture(mlx, "textures/east.xpm", &width, &height);
    texture[2] = loadTexture(mlx, "textures/south.xpm", &width, &height);
    texture[3] = loadTexture(mlx, "textures/west.xpm", &width, &height);
}

/*
pitch is an offset added to the vertical position of the drawn wall. By adding pitch, you can move the entire view up or down.
line_height is the height of the vertical line that should be drawn. You can of course also multiply it with another value if you want to walls to be higher or lower
*/
void    draw_everything_3d_texture(t_data *data)
{
    int x;
    int lineHeight;
    int pitch;
    unsigned int buffer[HEIGHT][WIDTH];
    t_map *grid_map;
    t_ray   *ray;
    t_img **textures;
    t_player *player;
    
    player = data->player;
    grid_map = data->map;
    ray = data->ray;
    textures = calloc(4, sizeof(t_img**));
    generate_textures(data->mlx_ptr, textures);
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
            calculate_side_dist_wall_position_and_side(ray, grid_map);
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
        int texNum = grid_map->grid[ray->mapY][ray->mapX] -48 - 1; //1 subtracted from it so that texture 0 can be used!

        //x coordinate on the texture
        int texX = (int)(wallX * (double)texWidth); //texX eh o x da textura equivalente a onde bateu o raio na parede.
        if(ray->side == 0 && ray->rayDirX > 0) texX = texWidth - texX - 1;
        if(ray->side == 1 && ray->rayDirY < 0) texX = texWidth - texX - 1;
        
        // TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
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

            unsigned int texture_pixel = get_texture_pixel(textures[texNum], texX, texY); //textures[texNum][texHeight * texY + texX]; //tenho que somar texX porque texture[texNum] eh um array e não uma matriz, entao essa eh a forma de pegar o pixel y,x (linha,coluna) da textura
            //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
            if(ray->side == 1) texture_pixel = (texture_pixel >> 1) & 8355711;
            buffer[y][x] = texture_pixel;
        }
        int cor = get_rgb(225,30,0);
        for(int y = 0; y < drawStart; y++)
        {
            buffer[y][x] = cor;
        }
        for(int y = drawEnd; y < HEIGHT; y++)
        {
            buffer[y][x] = cor;
        }
        x++;
    }

    drawBuffer(buffer,  data->img);
    for(int y = 0; y < HEIGHT; y++)
    {
        for(int x = 0; x < WIDTH; x++)
        {
            buffer[y][x] = 0;
        }
    }

    // for(int y = 0; y < HEIGHT; y++) for(int x = 0; x < WIDTH; x++) 
    //     buffer[y][x] = 0; //clear the buffer instead of cls()
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
map_x and map_y: are the ray position and get incremented with step_x and step_y respectively
side: 1 if the ray intersects a NS grid line (y-side), 
0 if the ray intersects a EW grid line (x-side)
*/
void calculate_side_dist_wall_position_and_side(t_ray * ray, t_map * grid_map)
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
    if (grid_map->grid[ray->mapY][ray->mapX] >= '1')
        ray->hit = 1;
}

/*
Calculates once, per x position:
side_distance: are the distance the ray has to travel from 
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
