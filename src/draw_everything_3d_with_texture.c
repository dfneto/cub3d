/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_everything_3d_with_texture.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 18:07:08 by davifern          #+#    #+#             */
/*   Updated: 2024/08/15 06:07:13 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void drawBuffer(t_win *win, uint32_t buffer[HEIGHT][WIDTH])
{ //buffer[HEIGHT][WIDTH]
    int y = 0;
    int x = 0;
    while (y < HEIGHT)
    {
        while (x < WIDTH)
        {
            my_mlx_pixel_put(win->img, x, y, buffer[y][x]);
            x++;
        }
        x = 0;
        y++;
    }
}

void *loadTexture(void *mlx, char *file_path, int *width, int *height)
{
    void *img = mlx_xpm_file_to_image(mlx, file_path, width, height);
    if (!img)
    {
        printf("Failed to load texture: %s\n", file_path);
        exit(1);
    }
    return img;
}

void generate_textures(void *mlx, uint32_t *texture[8]) {
    int width, height;
    
    texture[0] = loadTexture(mlx, "textures/south.xpm", &width, &height);
    texture[1] = loadTexture(mlx, "textures/west.xpm", &width, &height);
    texture[2] = loadTexture(mlx, "textures/south.xpm", &width, &height);
    texture[3] = loadTexture(mlx, "textures/south.xpm", &width, &height);
    texture[4] = loadTexture(mlx, "textures/south.xpm", &width, &height);
    texture[5] = loadTexture(mlx, "textures/south.xpm", &width, &height);
    texture[6] = loadTexture(mlx, "textures/south.xpm", &width, &height);
    texture[7] = loadTexture(mlx, "textures/south.xpm", &width, &height);
}

void    draw_everything_3d_texture(t_win *win)
{
    //declarados pelo lodev fora do main
    uint32_t buffer[HEIGHT][WIDTH]; // y-coordinate first because it works per scanline
    uint32_t* texture[8]; //8 porque ele tem de 0 a 7 números no mapa, assim quer representar 8 texturas

    //declarados no main
    for(int i = 0; i < 8; i++) {
        texture[i] = (uint32_t*)malloc(texWidth * texHeight * sizeof(uint32_t)); //acho que deveria somar mais texWidth
        // if (texture[i] == NULL) {
        //     // Handle memory allocation failure
        //     return 1;
        // }
    }

    generate_textures(win->mlx_ptr, texture);
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
    int color;
    
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
            if (grid_map->grid[mapY][mapX] == '1')
            {
                hit = 1;
                color = BLUE;
            }
            if (grid_map->grid[mapY][mapX] == '2')
            {
                hit = 1; 
                color = RED;
            }
        }
        if (side == 0) //acho que entao bateu no lado do quadrado (W O)
            perpWallDist = (sideDistX - deltaDistX);
        else           //bateu em cima ou em baixo (N S)
            perpWallDist = (sideDistY - deltaDistY);

        //height of the vertical line that should be drawn            
        lineHeight = (int)(HEIGHT / perpWallDist); //You can of course also multiply it with another value, for example 2*screenHeight, if you want to walls to be higher or lower


        //TEXTURE --------------------------------------------------------------------------------------------
        int pitch = 100;

        //calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + HEIGHT / 2 + pitch;
        if(drawStart < 0) 
            drawStart = 0;
        int drawEnd = lineHeight / 2 + HEIGHT / 2 + pitch;
        if(drawEnd >= HEIGHT) drawEnd = HEIGHT - 1;

        //texturing calculations (-48 para transformar de char para int)
        int texNum = grid_map->grid[mapY][mapX] -48 - 1; //1 subtracted from it so that texture 0 can be used!
        (void)color;
        (void)lineHeight;
        (void)buffer;
        (void)texNum;
    

        //calculate value of wallX
        double wallX; //where exactly the wall was hit
        if(side == 0) wallX = player->pos_y + perpWallDist * rayDirY;
        else          wallX = player->pos_x + perpWallDist * rayDirX;
        wallX -= floor((wallX));

        //x coordinate on the texture
        int texX = (int)(wallX * (double)texWidth);
        if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
        if(side == 1 && rayDirY < 0) texX = texWidth - texX - 1;

        // TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
        // How much to increase the texture coordinate per screen pixel
        double step = 1.0 * texHeight / lineHeight;
        // Starting texture coordinate
        double texPos = (drawStart - pitch - HEIGHT / 2 + lineHeight / 2) * step;
        for(int y = drawStart; y < drawEnd; y++)
        {
            // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
            int texY = (int)texPos & (texHeight - 1);
            texPos += step;
            uint32_t color = texture[texNum][texHeight * texY + texX];
            //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
            if(side == 1) color = (color >> 1) & 8355711;
            buffer[y][x] = color;
        }
        x++;
    }

    drawBuffer(win, buffer);
    // for(int y = 0; y < HEIGHT; y++) for(int x = 0; x < WIDTH; x++) 
    //     buffer[y][x] = 0; //clear the buffer instead of cls()
}
