/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 15:45:52 by lsaiti            #+#    #+#             */
/*   Updated: 2025/01/18 19:02:02 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	change_dist(t_view *view)
{
	if (view->raydir_x < 0)
	{
		view->step_x = -1;
		view->sidedist_x = (view->pos_x - view->map_x) * view->deltadist_x;
	}
	else
	{
		view->step_x = 1;
		view->sidedist_x = (view->map_x + 1.0 - view->pos_x)
			* view->deltadist_x;
	}
	if (view->raydir_y < 0)
	{
		view->step_y = -1;
		view->sidedist_y = (view->pos_y - view->map_y) * view->deltadist_y;
	}
	else
	{
		view->step_y = 1;
		view->sidedist_y = (view->map_y + 1.0 - view->pos_y)
			* view->deltadist_y;
	}
}

void	change_side(t_map_utils *fdf, t_view *view)
{
	view->hit = 0;
	while (view->hit == 0)
	{
		if (view->sidedist_x < view->sidedist_y)
		{
			view->sidedist_x += view->deltadist_x;
			view->map_x += view->step_x;
			view->side = 0;
		}
		else
		{
			view->sidedist_y += view->deltadist_y;
			view->map_y += view->step_y;
			view->side = 1;
		}
		if (view->map_x < 0 || (size_t)view->map_x >= fdf->game->length_max
			|| view->map_y < 0 || (size_t)view->map_y >= fdf->game->height_max)
		{
			view->hit = 1;
			break ;
		}
		if (fdf->map[view->map_y][view->map_x] == '1')
			view->hit = 1;
	}
}

void	change_draw(t_view *view)
{
	if (view->side == 0)
		view->permawall_dist = (view->sidedist_x - view->deltadist_x);
	else
		view->permawall_dist = (view->sidedist_y - view->deltadist_y);
	if (view->permawall_dist <= 0)
		view->permawall_dist = 0.01;
	view->line_height = (int)(HEIGHT / view->permawall_dist);
	if (view->line_height <= 0)
		view->line_height = 1;
	view->draw_start = -view->line_height / 2 + HEIGHT / 2;
	if (view->draw_start < 0)
		view->draw_start = 0;
	view->draw_end = view->line_height / 2 + HEIGHT / 2;
	if (view->draw_end >= HEIGHT)
		view->draw_end = HEIGHT - 1;
}

void	change_values(t_view *view)
{
	view->camera_x = 2.0 * view->x / (double)LENGTH - 1.0;
	view->raydir_x = view->dir_x + view->plane_x * view->camera_x;
	view->raydir_y = view->dir_y + view->plane_y * view->camera_x;
	view->map_x = (int)view->pos_x;
	view->map_y = (int)view->pos_y;
	if (view->raydir_x == 0)
		view->deltadist_x = 1e30;
	else
		view->deltadist_x = fabs(1.0 / view->raydir_x);
	if (view->raydir_y == 0)
		view->deltadist_y = 1e30;
	else
		view->deltadist_y = fabs(1.0 / view->raydir_y);
}

void	change_wall(t_view *view)
{
	if (view->side == 0)
		view->wall_x = view->pos_y + view->permawall_dist * view->raydir_y;
	else
		view->wall_x = view->pos_x + view->permawall_dist * view->raydir_x;
	view->wall_x -= floor(view->wall_x);
	view->tex_x = (int)(view->wall_x * (double)(view->tex->width));
	if ((view->side == 0 && view->raydir_x < 0) || (view->side == 1
			&& view->raydir_y > 0))
		view->tex_x = view->tex->width - view->tex_x - 1;
	view->step = 1.0 * view->tex->height / view->line_height;
	view->tex_pos = (view->draw_start - HEIGHT / 2 + view->line_height / 2)
		* view->step;
}
