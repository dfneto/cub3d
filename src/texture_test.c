#include "cub3d.h"


#define NUM_TEXTURES 8

void *loadTexture2(void *mlx, char *file_path, int *width, int *height)
{
    void *img = mlx_xpm_file_to_image(mlx, file_path, width, height);
    if (!img)
    {
        printf("Failed to load texture: %s\n", file_path);
        exit(1);
    }
    return img;
}

int main2(void)
{
    void *mlx;
    void *window;
    void *texture[NUM_TEXTURES];
    int width, height;

    // Initialize MiniLibX
    mlx = mlx_init();
    if (!mlx)
    {
        printf("Failed to initialize MiniLibX\n");
        return 1;
    }

    // Create a new window
    window = mlx_new_window(mlx, 800, 600, "XPM Textures");
    if (!window)
    {
        printf("Failed to create window\n");
        return 1;
    }

    // Load textures
    texture[0] = loadTexture2(mlx, "textures/south.xpm", &width, &height);
    texture[1] = loadTexture2(mlx, "textures/west.xpm", &width, &height);
    texture[2] = loadTexture2(mlx, "textures/south.xpm", &width, &height);
    texture[3] = loadTexture2(mlx, "textures/south.xpm", &width, &height);
    texture[4] = loadTexture2(mlx, "textures/south.xpm", &width, &height);
    texture[5] = loadTexture2(mlx, "textures/south.xpm", &width, &height);
    texture[6] = loadTexture2(mlx, "textures/south.xpm", &width, &height);
    texture[7] = loadTexture2(mlx, "textures/south.xpm", &width, &height);

    // Example of putting the first texture on the window at position (100, 100)
    mlx_put_image_to_window(mlx, window, texture[0], 100, 100);

    // Add event handling, such as closing the window
    mlx_loop(mlx);

    // Free textures (not necessary here since we never leave mlx_loop)
    for (int i = 0; i < NUM_TEXTURES; i++)
    {
        if (texture[i])
        {
            mlx_destroy_image(mlx, texture[i]);
        }
    }

    return 0;
}
