#include "../inc/cub3d.h"

int draw_line(void *mlx, void *win, int beginX, int beginY, int endX, int endY, int color)
{
	double deltaX = endX - beginX; // -640
	double deltaY = endY - beginY; // -360
	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));//tamanho da reta = hipotenusa
	printf("deltaX=%f, deltaY=%f\npixels=%d\n", deltaX, deltaY, pixels);
	deltaX = deltaX / pixels; // -0.871935
	deltaY = deltaY / pixels; // -0.490463
	printf("deltaX=%f, deltaY=%f\npixels=%d\n", deltaX, deltaY, pixels);
	double pixelX = beginX; //640
	double pixelY = beginY; //360
	while (pixels) //tamanho da reta em pixels 
	{
        printf("pixelX=%f, pixelY=%f\n", pixelX, pixelY);
		mlx_pixel_put(mlx, win, pixelX, pixelY, color);
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}
	return 0;
}

int main()
{
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 640, 360, "Tutorial Window - Draw Line");

    draw_line(mlx, win, 640, 360, 290, 0, 0xFFFFFF);

    mlx_loop(mlx);
}
