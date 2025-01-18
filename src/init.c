/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 15:40:44 by lsaiti            #+#    #+#             */
/*   Updated: 2025/01/18 18:00:10 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_map_utils	*map_init(void)
{
	t_map_utils	*fdf;

	fdf = malloc(sizeof(t_map_utils));
	if (!fdf)
		return (NULL);
	fdf->key_w = 0;
	fdf->key_s = 0;
	fdf->key_d = 0;
	fdf->key_a = 0;
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		return (NULL);
	fdf->window = mlx_new_window(fdf->mlx, LENGTH, HEIGHT, "Cub3d");
	if (!fdf->window)
		free_all(fdf);
	return (fdf);
}

void	init_image(t_map_utils *fdf)
{
	fdf->img = mlx_new_image(fdf->mlx, LENGTH, HEIGHT);
	fdf->img_data = mlx_get_data_addr(fdf->img, &fdf->bpp, &fdf->size_line,
			&fdf->endian);
}

t_map_utils	*init_textures(t_map_utils *fdf)
{
	fdf->game->tex_no.img = mlx_xpm_file_to_image(fdf->mlx, fdf->game->path_no,
			&fdf->game->tex_no.width, &fdf->game->tex_no.height);
	fdf->game->tex_no.addr = (int *)mlx_get_data_addr(fdf->game->tex_no.img,
			&fdf->game->tex_no.bpp, &fdf->game->tex_no.size_line,
			&fdf->game->tex_no.endian);
	fdf->game->tex_so.img = mlx_xpm_file_to_image(fdf->mlx, fdf->game->path_so,
			&fdf->game->tex_so.width, &fdf->game->tex_so.height);
	fdf->game->tex_so.addr = (int *)mlx_get_data_addr(fdf->game->tex_so.img,
			&fdf->game->tex_so.bpp, &fdf->game->tex_so.size_line,
			&fdf->game->tex_so.endian);
	fdf->game->tex_we.img = mlx_xpm_file_to_image(fdf->mlx, fdf->game->path_we,
			&fdf->game->tex_we.width, &fdf->game->tex_we.height);
	fdf->game->tex_we.addr = (int *)mlx_get_data_addr(fdf->game->tex_we.img,
			&fdf->game->tex_we.bpp, &fdf->game->tex_we.size_line,
			&fdf->game->tex_we.endian);
	fdf->game->tex_ea.img = mlx_xpm_file_to_image(fdf->mlx, fdf->game->path_ea,
			&fdf->game->tex_ea.width, &fdf->game->tex_ea.height);
	fdf->game->tex_ea.addr = (int *)mlx_get_data_addr(fdf->game->tex_ea.img,
			&fdf->game->tex_ea.bpp, &fdf->game->tex_ea.size_line,
			&fdf->game->tex_ea.endian);
	if (!fdf->game->tex_no.img || !fdf->game->tex_so.img
		|| !fdf->game->tex_we.img || !fdf->game->tex_ea.img)
		return (close_all(fdf), write(STDERR_FILENO,
				"Failed to load north texture\n", 28), NULL);
	return (fdf);
}

t_map_utils	*init_fdf(t_game *game)
{
	t_map_utils	*fdf;

	fdf = map_init();
	if (!fdf)
		return (write(2, "FAILED TO INIT MAP!\n", 20), NULL);
	fdf->map = get_full_map(game);
	if (!fdf->map)
		return (close_all(fdf), write(2, "Error: Failed to load map.\n", 26),
			NULL);
	fdf->game = game;
	init_image(fdf);
	if (!fdf->img)
		return (close_all(fdf), write(2, "Error: Failed to create image.\n",
				31), NULL);
	fdf = init_textures(fdf);
	return (fdf);
}
