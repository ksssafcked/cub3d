/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:53:22 by lsaiti            #+#    #+#             */
/*   Updated: 2025/01/09 17:06:52 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_all(t_map_utils *fdf)
{
	mlx_destroy_display(fdf->mlx);
	free(fdf->mlx);
	free(fdf);
	exit(0);
}

t_map_utils	*map_init(void)
{
	t_map_utils	*fdf;

	fdf = malloc(sizeof(t_map_utils));
	if (!fdf)
		return (NULL);
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		return (free(fdf), NULL);
	fdf->window = mlx_new_window(fdf->mlx, LENGTH, HEIGHT, "Cub3d");
	if (!fdf->window)
		free_all(fdf);
	return (fdf);
}

int	close_all(t_map_utils *fdf)
{
	mlx_destroy_image(fdf->mlx, fdf->img);
	mlx_destroy_window(fdf->mlx, fdf->window);
	mlx_destroy_display(fdf->mlx);
	free(fdf->mlx);
	free_map(fdf->game->map);
	free(fdf->game);
	free(fdf);
	exit(0);
}

int	handle(int keycode, t_map_utils *fdf)
{
	if (keycode == 65307)
		close_all(fdf);
	return (0);
}

int	main(int argc, char **argv)
{
	t_map_utils	*fdf;
	t_game		*game;

	(void)argv;
	if (argc != 2)
	{
		write(2, "BAD ARGUMENTS!\n", 15);
		return (1);
	}
	fdf = map_init();
	if (!fdf)
	{
		write(2, "FAILED TO INIT MAP!\n", 20);
		return (1);
	}
	game = game_parser(argv[1]);
	if (!game)
	{
		perror("Failed to parse the map");
		return (1);
	}
	fdf->game = game;
	fdf->img = mlx_new_image(fdf->mlx, LENGTH, HEIGHT);
	mlx_key_hook(fdf->window, &handle, fdf);
	draw_map(fdf, game);
	// mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->img, 0, 0);
	mlx_hook(fdf->window, 17, 0, close_all, fdf);
	mlx_loop(fdf->mlx);
	return (0);
}
