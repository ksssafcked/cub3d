/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:59:56 by lsaiti            #+#    #+#             */
/*   Updated: 2025/01/18 19:27:16 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	key_press(int keycode, t_map_utils *cub)
{
	if (keycode == XK_w || keycode == XK_W)
		cub->key_w = 1;
	else if (keycode == XK_s || keycode == XK_S)
		cub->key_s = 1;
	else if (keycode == XK_a || keycode == XK_A)
		cub->key_a = 1;
	else if (keycode == XK_d || keycode == XK_D)
		cub->key_d = 1;
	else if (keycode == XK_Left)
		cub->key_left = 1;
	else if (keycode == XK_Right)
		cub->key_right = 1;
	else if (keycode == XK_Escape)
		close_all(cub);
	return (0);
}

int	key_release(int keycode, t_map_utils *cub)
{
	if (keycode == XK_w || keycode == XK_W)
		cub->key_w = 0;
	else if (keycode == XK_s || keycode == XK_S)
		cub->key_s = 0;
	else if (keycode == XK_a || keycode == XK_A)
		cub->key_a = 0;
	else if (keycode == XK_d || keycode == XK_D)
		cub->key_d = 0;
	else if (keycode == XK_Left)
		cub->key_left = 0;
	else if (keycode == XK_Right)
		cub->key_right = 0;
	return (0);
}

void	destroy_textures(t_map_utils *cub)
{
	if (cub->game->tex_so.img)
		mlx_destroy_image(cub->mlx, cub->game->tex_so.img);
	if (cub->game->tex_ea.img)
		mlx_destroy_image(cub->mlx, cub->game->tex_ea.img);
	if (cub->game->tex_we.img)
		mlx_destroy_image(cub->mlx, cub->game->tex_we.img);
	if (cub->game->tex_no.img)
		mlx_destroy_image(cub->mlx, cub->game->tex_no.img);
	if (cub->game->path_ea)
		free(cub->game->path_ea);
	if (cub->game->path_no)
		free(cub->game->path_no);
	if (cub->game->path_so)
		free(cub->game->path_so);
	if (cub->game->path_we)
		free(cub->game->path_we);
}

void destroy_mlx(t_map_utils *cub)
{
	if (cub->img)
		mlx_destroy_image(cub->mlx, cub->img);
	if (cub->window)
		mlx_destroy_window(cub->mlx, cub->window);
	if (cub->mlx)
		mlx_destroy_display(cub->mlx);
}

int	close_all(t_map_utils *cub)
{
	int	i;

	if (cub)
	{
		destroy_mlx(cub);
		i = 0;
		if (cub->map)
		{
			while (cub->map && cub->map[i])
			{
				free(cub->map[i]);
				i++;
			}
		free(cub->map);
		}
		if (cub->game)
		{
			destroy_textures(cub);
			free_map(cub->game->map);
			free(cub->game->player);
			free(cub->game);
		}
	free(cub);
	}
	exit(0);
}
