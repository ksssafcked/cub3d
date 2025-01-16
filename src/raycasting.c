/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:46:38 by qudomino          #+#    #+#             */
/*   Updated: 2025/01/16 18:07:00 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	set_pixel_color(t_map_utils *fdf, int x, int y, unsigned int color)
{
	int	pixel_index;
	if (x < 0 || x >= LENGTH || y < 0 || y >= HEIGHT)
		return ;
	pixel_index = (y * fdf->size_line) + (x * (fdf->bpp / 8));
	fdf->img_data[pixel_index + 0] = color & 0xFF;
	fdf->img_data[pixel_index + 1] = (color >> 8) & 0xFF;
	fdf->img_data[pixel_index + 2] = (color >> 16) & 0xFF;
}


unsigned int get_texture_color(void *img, int texX, int texY)
{
    int bpp, size_line, endian;
    unsigned char *data;

    data = (unsigned char *)mlx_get_data_addr(img, &bpp, &size_line, &endian);
    int pixel_index = (texY * size_line) + (texX * (bpp / 8));
    unsigned char red = data[pixel_index + 2];
    unsigned char green = data[pixel_index + 1];
    unsigned char blue = data[pixel_index];
    unsigned int color = (red << 16) | (green << 8) | blue;
    
    return color;
}

void draw_3d_view(t_map_utils *fdf)
{
    int x, y;
    double cameraX, rayDirX, rayDirY;
    double sideDistX, sideDistY, deltaDistX, deltaDistY, perpWallDist;
    double posX, posY, dirX, dirY, planeX, planeY;
    int stepX, stepY, hit, side, mapX, mapY;
    int lineHeight, drawEnd, drawStart;

    draw_background(fdf, fdf->game);

    dirX = cos(fdf->game->player->angle);
    dirY = sin(fdf->game->player->angle);
    posX = fdf->game->player->x;
    posY = fdf->game->player->y;
    planeX = -dirY * 0.66;
    planeY = dirX * 0.66;

    x = 0;
    int w, h;
    void *texture = mlx_xpm_file_to_image(fdf->mlx, "textures/wall_east.xpm", &w, &h);
    
    if (!texture)
        printf("Error loading texture\n");

    while (x < LENGTH)
    {
        cameraX = 2.0 * x / (double)LENGTH - 1.0;
        rayDirX = dirX + planeX * cameraX;
        rayDirY = dirY + planeY * cameraX;
        mapX = (int)posX;
        mapY = (int)posY;

        deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1.0 / rayDirX);
        deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1.0 / rayDirY);

        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (posX - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - posX) * deltaDistX;
        }

        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (posY - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - posY) * deltaDistY;
        }

        hit = 0;
        while (hit == 0)
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

            if (fdf->map[mapY][mapX] == '1') // Mur trouvé
                hit = 1;
        }

        if (side == 0)
            perpWallDist = (sideDistX - deltaDistX);
        else
            perpWallDist = (sideDistY - deltaDistY);

        // Calcul de la hauteur du mur
        lineHeight = (int)(HEIGHT / perpWallDist);
        drawStart = -lineHeight / 2 + HEIGHT / 2;
        if (drawStart < 0)
            drawStart = 0;
        drawEnd = lineHeight / 2 + HEIGHT / 2;
        if (drawEnd >= HEIGHT)
            drawEnd = HEIGHT - 1;

        // Calcul de texX une seule fois pour chaque rayon
        int texX;
        if (side == 0) // Mur vertical (est/ouest)
        {
            texX = (int)(posY + perpWallDist * rayDirY) % w;
        }
        else // Mur horizontal (nord/sud)
        {
            texX = (int)(posX + perpWallDist * rayDirX) % w;
        }

        // Clamping des coordonnées de la texture
        if (texX < 0) texX = 0;
        if (texX >= w) texX = w - 1;

        // Calcul de l'incrément pour texY
        double wallX = (side == 0) ? posY + perpWallDist * rayDirY : posX + perpWallDist * rayDirX;
        wallX -= floor(wallX); // Trouver le "fractional" de la position de la texture
        texX = (int)(wallX * w); // Multiplier par la largeur de la texture pour obtenir texX

        // Incrémentation pour texY : calculer une fois pour toute la ligne
        double step = 1.0 * h / lineHeight;
        double texPos = (drawStart - HEIGHT / 2 + lineHeight / 2) * step;
		int texY;
        y = drawStart;
        while (y < drawEnd)
        {
            texY = (int)texPos;
            texPos += step;

            // Clamping de texY
            if (texY < 0) texY = 0;
            if (texY >= h) texY = h - 1;

            unsigned int color = get_texture_color(texture, texX, texY);
            set_pixel_color(fdf, x, y, color);
            y++;
        }

        x++;
    }
	mlx_destroy_image(fdf->mlx, texture);
}
