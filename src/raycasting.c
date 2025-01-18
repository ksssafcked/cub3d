/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:46:38 by qudomino          #+#    #+#             */
/*   Updated: 2025/01/18 19:01:53 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	set_pixel_color(t_map_utils *fdf, int x, int y, unsigned int color)
{
	int	pixel_index;

	if (x < 0 || x >= LENGTH || y < 0 || y >= HEIGHT)
		return ;
	pixel_index = (y * fdf->size_line) + (x * (fdf->bpp / 8));
	fdf->img_data[pixel_index + 0] = color & 0xFF;
	fdf->img_data[pixel_index + 1] = (color >> 8) & 0xFF;
	fdf->img_data[pixel_index + 2] = (color >> 16) & 0xFF;
}

void	init_player_pos(t_map_utils *fdf, t_view *view)
{
	view->pos_x = fdf->game->player->x;
	view->pos_y = fdf->game->player->y;
	view->dir_x = cos(fdf->game->player->angle);
	view->dir_y = sin(fdf->game->player->angle);
	view->plane_x = -view->dir_y * 0.66;
	view->plane_y = view->dir_x * 0.66;
}

void	draw_3d(t_map_utils *fdf, t_view *view)
{
	unsigned int	color;

	view->y = view->draw_start;
	while (view->y < view->draw_end)
	{
		view->tex_y = (int)view->tex_pos & (view->tex->height - 1);
		view->tex_pos += view->step;
		if (view->tex_x < 0 || view->tex_x >= view->tex->width
			|| view->tex_y < 0 || view->tex_y >= view->tex->height)
			continue ;
		color = ((unsigned int *)view->tex->addr)[view->tex->size_line / 4
			* view->tex_y + view->tex_x];
		set_pixel_color(fdf, view->x, view->y, color);
		view->y++;
	}
}

void	draw_3d_view(t_map_utils *fdf)
{
	t_view	view;

	if (!fdf || !fdf->game || !fdf->game)
	{
		fprintf(stderr, "Error: Game structure not initialized.\n");
		close_all(fdf);
		exit(1);
	}
	init_player_pos(fdf, &view);
	draw_background(fdf, fdf->game);
	view.x = 0;
	while (view.x < LENGTH)
	{
		change_values(&view);
		change_dist(&view);
		change_side(fdf, &view);
		change_draw(&view);
		if (!get_texture(fdf, &view))
			return ;
		change_wall(&view);
		draw_3d(fdf, &view);
		view.x++;
	}
}
