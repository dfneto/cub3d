#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <SDL2/SDL.h>

#define screenWidth 640
#define screenHeight 480
#define texWidth 64
#define texHeight 64
#define mapWidth 24
#define mapHeight 24

int worldMap[mapWidth][mapHeight] =
{
    {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
    {4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
    {4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
    {4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
    {4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
    {4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
    {4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
    {4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
    {4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
    {4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
    {4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
    {6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
    {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
    {4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
    {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
    {4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
    {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
    {4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
    {4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
    {4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
    {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
    {4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
};

Uint32 buffer[screenHeight][screenWidth];

void generate_textures(Uint32* texture[8]) {
    for(int x = 0; x < texWidth; x++) {
        for(int y = 0; y < texHeight; y++) {
            int xorcolor = (x * 256 / texWidth) ^ (y * 256 / texHeight);
            int ycolor = y * 256 / texHeight;
            int xycolor = y * 128 / texHeight + x * 128 / texWidth;

            texture[0][texWidth * y + x] = 65536 * 254 * (x != y && x != texWidth - y); // flat red texture with black cross
            texture[1][texWidth * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; // sloped greyscale
            texture[2][texWidth * y + x] = 256 * xycolor + 65536 * xycolor; // sloped yellow gradient
            texture[3][texWidth * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; // xor greyscale
            texture[4][texWidth * y + x] = 256 * xorcolor; // xor green
            texture[5][texWidth * y + x] = 65536 * 192 * (x % 16 && y % 16); // red bricks
            texture[6][texWidth * y + x] = 65536 * ycolor; // red gradient
            texture[7][texWidth * y + x] = 128 + 256 * 128 + 65536 * 128; // flat grey texture
        }
    }
}

int main() {
    double posX = 22.0, posY = 11.5;  //x and y start position
    double dirX = -1.0, dirY = 0.0; //initial direction vector
    double planeX = 0.0, planeY = 0.66; //the 2d raycaster version of camera plane

    double time = 0; //time of current frame
    double oldTime = 0; //time of previous frame

    Uint32* texture[8];
    for(int i = 0; i < 8; i++) {
        texture[i] = (Uint32*)malloc(texWidth * texHeight * sizeof(Uint32));
        if (texture[i] == NULL) {
            fprintf(stderr, "Failed to allocate memory for texture %d\n", i);
            return 1;
        }
    }

    generate_textures(texture);

    screen(screenWidth, screenHeight, 0, "Raycaster");

    while(!done()) {
        for(int x = 0; x < screenWidth; x++) {
            double cameraX = 2 * x / (double)screenWidth - 1;
            double rayDirX = dirX + planeX * cameraX;
            double rayDirY = dirY + planeY * cameraX;

            int mapX = (int)posX;
            int mapY = (int)posY;

            double sideDistX;
            double sideDistY;

            double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
            double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
            double perpWallDist;

            int stepX;
            int stepY;

            int hit = 0;
            int side;

            if(rayDirX < 0) {
                stepX = -1;
                sideDistX = (posX - mapX) * deltaDistX;
            } else {
                stepX = 1;
                sideDistX = (mapX + 1.0 - posX) * deltaDistX;
            }
            if(rayDirY < 0) {
                stepY = -1;
                sideDistY = (posY - mapY) * deltaDistY;
            } else {
                stepY = 1;
                sideDistY = (mapY + 1.0 - posY) * deltaDistY;
            }

            while(hit == 0) {
                if(sideDistX < sideDistY) {
                    sideDistX += deltaDistX;
                    mapX += stepX;
                    side = 0;
                } else {
                    sideDistY += deltaDistY;
                    mapY += stepY;
                    side = 1;
                }
                if(worldMap[mapX][mapY] > 0) hit = 1;
            }

            if(side == 0) perpWallDist = (sideDistX - deltaDistX);
            else          perpWallDist = (sideDistY - deltaDistY);

            int lineHeight = (int)(screenHeight / perpWallDist);

            int pitch = 100;

            int drawStart = -lineHeight / 2 + screenHeight / 2 + pitch;
            if(drawStart < 0) drawStart = 0;
            int drawEnd = lineHeight / 2 + screenHeight / 2 + pitch;
            if(drawEnd >= screenHeight) drawEnd = screenHeight - 1;

            int texNum = worldMap[mapX][mapY] - 1;

            double wallX;
            if(side == 0) wallX = posY + perpWallDist * rayDirY;
            else          wallX = posX + perpWallDist * rayDirX;
            wallX -= floor(wallX);

            int texX = (int)(wallX * (double)texWidth);
            if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
            if(side == 1 && rayDirY < 0) texX = texWidth - texX - 1;

            double step = 1.0 * texHeight / lineHeight;
            double texPos = (drawStart - pitch - screenHeight / 2 + lineHeight / 2) * step;
            for(int y = drawStart; y < drawEnd; y++) {
                int texY = (int)texPos & (texHeight - 1);
                texPos += step;
                Uint32 color = texture[texNum][texHeight * texY + texX];
                if(side == 1) color = (color >> 1) & 8355711;
                buffer[y][x] = color;
            }
        }

        drawBuffer(buffer[0]);
        for(int y = 0; y < screenHeight; y++) {
            for(int x = 0; x < screenWidth; x++) {
                buffer[y][x] = 0;
            }
        }

        oldTime = time;
        time = getTicks();
        double frameTime = (time - oldTime) / 1000.0;
        print(1.0 / frameTime);
        redraw();

        double moveSpeed = frameTime * 5.0;
        double rotSpeed = frameTime * 3.0;

        readKeys();
        if(keyDown(SDLK_UP)) {
            if(worldMap[(int)(posX + dirX * moveSpeed)][(int)(posY)] == 0) posX += dirX * moveSpeed;
            if(worldMap[(int)(posX)][(int)(posY + dirY * moveSpeed)] == 0) posY += dirY * moveSpeed;
        }
        if(keyDown(SDLK_DOWN)) {
            if(worldMap[(int)(posX - dirX * moveSpeed)][(int)(posY)] == 0) posX -= dirX * moveSpeed;
            if(worldMap[(int)(posX)][(int)(posY - dirY * moveSpeed)] == 0) posY -= dirY * moveSpeed;
        }
        if(keyDown(SDLK_RIGHT)) {
            double oldDirX = dirX;
            dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
            dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
            double oldPlaneX = planeX;
            planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
            planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
        }
        if(keyDown(SDLK_LEFT)) {
            double oldDirX = dirX;
            dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
            dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
            double oldPlaneX = planeX;
            planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
            planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
        }
        if(keyDown(SDLK_ESCAPE)) {
            break;
        }
    }

    for(int i = 0; i < 8; i++) {
        free(texture[i]);
    }

    return 0;
}
