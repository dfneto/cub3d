/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_everything_3d_with_texture.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 18:07:08 by davifern          #+#    #+#             */
/*   Updated: 2024/08/21 19:55:13 by davifern         ###   ########.fr       */
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

void drawBuffer(unsigned int buffer[HEIGHT][WIDTH], t_win *win)
{ //buffer[HEIGHT][WIDTH]
    int y = 0;
    int x = 0;
    while (y < HEIGHT)
    {
        while (x < WIDTH)
        {//acho que aqui eh a imagem da tela
            my_mlx_pixel_put(win->img, x, y, buffer[y][x]);
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

void    draw_everything_3d_texture(t_win *win)
{
    //declarados pelo lodev fora do main
    unsigned int buffer[HEIGHT][WIDTH]; // y-coordinate first because it works per scanline
    // uint32_t* texture[8]; //8 porque ele tem de 0 a 7 números no mapa, assim quer representar 8 texturas
    t_img **textures = calloc(5, sizeof(t_img**));
    // int width, height;
    // textura = loadTexture(win->mlx_ptr, "textures/north.xpm", &width, &height);
    

    //declarados no main
    // for(int i = 0; i < 5; i++) {
    //     textures[i] = (int *)malloc(texWidth * texHeight * sizeof(int *)); //acho que deveria somar mais texWidth
    //     // if (texture[i] == NULL) {
    //     //     // Handle memory allocation failure
    //     //     return 1;
    //     // }
    // }

    generate_textures(win->mlx_ptr, textures);
    // mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, texture[1], 100, 100);

    // clean_map(win->img);
    t_player *player = win->player;
    t_map *grid_map = win->map;

    int x;
    double rayDirX = 0.0;
    double rayDirY = 0.0;
    double cameraX = 0.0;
    double deltaDistX = 0.0;
    double deltaDistY = 0.0;
    double sideDistX = 0.0;
    double sideDistY = 0.0;
    double perpWallDist = 0.0;
    int hit = 0;
    int mapX = 0;
    int mapY = 0;
    int stepX = 0;
    int stepY = 0;
    int side = 0;
    int lineHeight;
    // int drawStart;
    // int drawEnd;
    
    x = 0;
    while (x < WIDTH)
    {
        //zera tudo
        cameraX = 0.0;
        rayDirX = 0.0;
        rayDirY = 0.0;
        mapX = 0;
        mapY = 0;
        stepX = 0;
        stepY = 0;
        sideDistX = 0.0;
        sideDistY = 0.0;
        deltaDistX = 0.0;
        deltaDistY = 0.0;
        perpWallDist = 0.0;
        side = 0;
        hit = 0;
        lineHeight = 0;
        // drawStart = 0;
        // drawEnd = 0;

        cameraX = 2 * x / (double)WIDTH - 1;
        rayDirX = player->dir_x + player->planeX * cameraX;
        rayDirY = player->dir_y + player->planeY * cameraX;
        
        mapX = (int)player->pos_x;
        mapY = (int)player->pos_y;

        deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
        // deltaDistX = fabs(1 / rayDirX);
        // deltaDistY = fabs(1 / rayDirY);

        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (player->pos_x - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - player->pos_x) * deltaDistX; 
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (player->pos_y - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - player->pos_y) * deltaDistY;
        }

        while (hit == 0) //enquanto não bateu na parede
        {
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (grid_map->grid[mapY][mapX] >= '1')
                hit = 1;
        }
        if (side == 0) //acho que entao bateu no lado do quadrado (W O)
            perpWallDist = (sideDistX - deltaDistX);
        else           //bateu em cima ou em baixo (N S)
            perpWallDist = (sideDistY - deltaDistY);

        //height of the vertical line that should be drawn            
        lineHeight = (int)(HEIGHT / perpWallDist); //You can of course also multiply it with another value, for example 2*screenHeight, if you want to walls to be higher or lower

        //TEXTURE --------------------------------------------------------------------------------------------
        int pitch = 0; //This value is an offset added to the vertical position of the drawn wall. By adding pitch, you can move the entire view up or down.
        //TODO: esse pitch tava em 100
        
        //calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + HEIGHT / 2 + pitch;
        if(drawStart < 0) 
            drawStart = 0;
        int drawEnd = lineHeight / 2 + HEIGHT / 2 + pitch;
        if(drawEnd >= HEIGHT) drawEnd = HEIGHT - 1;

        //calculate value of wallX
        double wallX; //where exactly the wall was hit
        if(side == 0) wallX = player->pos_y + perpWallDist * rayDirY;
        else          wallX = player->pos_x + perpWallDist * rayDirX;
        wallX -= floor((wallX));

        //texturing calculations (-48 para transformar de char para int)
        int texNum = grid_map->grid[mapY][mapX] -48 - 1; //1 subtracted from it so that texture 0 can be used!

        //x coordinate on the texture
        int texX = (int)(wallX * (double)texWidth); //texX eh o x da textura equivalente a onde bateu o raio na parede.
        if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
        if(side == 1 && rayDirY < 0) texX = texWidth - texX - 1;
        
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
            if(side == 1) texture_pixel = (texture_pixel >> 1) & 8355711;
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

    drawBuffer(buffer,  win);
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
