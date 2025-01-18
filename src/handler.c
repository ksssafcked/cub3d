/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:59:56 by lsaiti            #+#    #+#             */
/*   Updated: 2025/01/18 15:07:34 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	key_press(int keycode, t_map_utils *fdf)
{
	if (keycode == XK_w || keycode == XK_W)
		fdf->key_w = 1;
	else if (keycode == XK_s || keycode == XK_S)
		fdf->key_s = 1;
	else if (keycode == XK_a || keycode == XK_A)
		fdf->key_a = 1;
	else if (keycode == XK_d || keycode == XK_D)
		fdf->key_d = 1;
	else if (keycode == XK_Left)
		fdf->key_left = 1;
	else if (keycode == XK_Right)
		fdf->key_right = 1;
	else if (keycode == XK_Escape)
		close_all(fdf);
	return (0);
}

int	key_release(int keycode, t_map_utils *fdf)
{
	if (keycode == XK_w || keycode == XK_W)
		fdf->key_w = 0;
	else if (keycode == XK_s || keycode == XK_S)
		fdf->key_s = 0;
	else if (keycode == XK_a || keycode == XK_A)
		fdf->key_a = 0;
	else if (keycode == XK_d || keycode == XK_D)
		fdf->key_d = 0;
	else if (keycode == XK_Left)
		fdf->key_left = 0;
	else if (keycode == XK_Right)
		fdf->key_right = 0;
	return (0);
}

void	destroy_textures(t_map_utils *fdf)
{
	if (fdf->game->tex_so.img)
		mlx_destroy_image(fdf->mlx, fdf->game->tex_so.img);
	if (fdf->game->tex_ea.img)
		mlx_destroy_image(fdf->mlx, fdf->game->tex_ea.img);
	if (fdf->game->tex_we.img)
		mlx_destroy_image(fdf->mlx, fdf->game->tex_we.img);
	if (fdf->game->tex_no.img)
		mlx_destroy_image(fdf->mlx, fdf->game->tex_no.img);
	if (fdf->game->path_ea)
		free(fdf->game->path_ea);
	if (fdf->game->path_no)
		free(fdf->game->path_no);
	if (fdf->game->path_so)
		free(fdf->game->path_so);
	if (fdf->game->path_we)
		free(fdf->game->path_we);
}

int	close_all(t_map_utils *fdf)
{
	int	i;

	mlx_destroy_image(fdf->mlx, fdf->img);
	destroy_textures(fdf);
	mlx_destroy_window(fdf->mlx, fdf->window);
	mlx_destroy_display(fdf->mlx);
	free(fdf->mlx);
	i = 0;
	while (fdf->map[i])
	{
		free(fdf->map[i]);
		i++;
	}
	free(fdf->map);
	free_map(fdf->game->map);
	free(fdf->game->player);
	free(fdf->game);
	free(fdf);
	exit(0);
}
