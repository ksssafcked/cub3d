/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:46:38 by qudomino          #+#    #+#             */
/*   Updated: 2025/01/15 16:26:12 by lsaiti           ###   ########.fr       */
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

void draw_3d_view(t_map_utils *fdf) {
    // Vérification des structures principales
    if (!fdf || !fdf->game) {
        fprintf(stderr, "Error: Game structure not initialized.\n");
        close_all(fdf);
        exit(1);
    }

    if (!fdf->map) {
        fprintf(stderr, "Error: Map not initialized.\n");
        close_all(fdf);
        exit(1);
    }

    int x, y, mapX, mapY, stepX, stepY, hit, side, lineHeight, drawStart, drawEnd;
    double cameraX, rayDirX, rayDirY, sideDistX, sideDistY, deltaDistX, deltaDistY, perpWallDist;
    double posX = fdf->game->player->x;
    double posY = fdf->game->player->y;
    double dirX = cos(fdf->game->player->angle);
    double dirY = sin(fdf->game->player->angle);
    double planeX = -dirY * 0.66;
    double planeY = dirX * 0.66;

    draw_background(fdf, fdf->game);

    x = 0;
    while (x < LENGTH) {
        cameraX = 2.0 * x / (double)LENGTH - 1.0;
        rayDirX = dirX + planeX * cameraX;
        rayDirY = dirY + planeY * cameraX;

        mapX = (int)posX;
        mapY = (int)posY;
        deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1.0 / rayDirX);
        deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1.0 / rayDirY);

        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = (posX - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - posX) * deltaDistX;
        }

        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (posY - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - posY) * deltaDistY;
        }

        hit = 0;
        while (hit == 0) {
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            } else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }

            if (mapX < 0 || (size_t)mapX >= fdf->game->length_max || mapY < 0 || (size_t)mapY >= fdf->game->height_max) {
                hit = 1;
                break;
            }

            if (fdf->map[mapY][mapX] == '1')
                hit = 1;
        }

        if (side == 0)
            perpWallDist = (sideDistX - deltaDistX);
        else
            perpWallDist = (sideDistY - deltaDistY);

        if (perpWallDist <= 0)
            perpWallDist = 0.01;

        lineHeight = (int)(HEIGHT / perpWallDist);
        if (lineHeight <= 0)
            lineHeight = 1;

        drawStart = -lineHeight / 2 + HEIGHT / 2;
        if (drawStart < 0)
            drawStart = 0;

        drawEnd = lineHeight / 2 + HEIGHT / 2;
        if (drawEnd >= HEIGHT)
            drawEnd = HEIGHT - 1;

        t_texture *tex;
        if (side == 0) {
            if (rayDirX > 0)
                tex = &fdf->game->tex_ea; // Mur est
            else
                tex = &fdf->game->tex_we; // Mur ouest
        } else {
            if (rayDirY > 0)
                tex = &fdf->game->tex_so; // Mur sud
            else
                tex = &fdf->game->tex_no; // Mur nord
        }

        // Vérifiez que la texture est bien initialisée
        if (!tex || !tex->img || !tex->addr) {
            fprintf(stderr, "Error: Texture not initialized.\n");
            return;
        }

        // Vérifiez les dimensions des textures
        if (tex->width <= 0 || tex->height <= 0) {
            fprintf(stderr, "Error: Invalid texture dimensions.\n");
            return;
        }

        double wallX = (side == 0) ? posY + perpWallDist * rayDirY : posX + perpWallDist * rayDirX;
        wallX -= floor(wallX);

        int texX = (int)(wallX * (double)(tex->width));
        if ((side == 0 && rayDirX < 0) || (side == 1 && rayDirY > 0))
            texX = tex->width - texX - 1;

        double step = 1.0 * tex->height / lineHeight;
        double texPos = (drawStart - HEIGHT / 2 + lineHeight / 2) * step;

        for (y = drawStart; y < drawEnd; y++) {
            int texY = (int)texPos & (tex->height - 1);
            texPos += step;

            if (texX < 0 || texX >= tex->width || texY < 0 || texY >= tex->height)
                continue;

            unsigned int color = ((unsigned int *)tex->addr)[tex->size_line / 4 * texY + texX];
            set_pixel_color(fdf, x, y, color);
        }

        x++;
    }
}
