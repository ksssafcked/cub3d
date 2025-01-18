/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:53:22 by lsaiti            #+#    #+#             */
/*   Updated: 2025/01/18 15:42:22 by lsaiti           ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_map_utils	*fdf;
	t_game		*game;
	int			len;

	(void)argv;
	if (argc != 2)
		return (write(2, "Bad arguments!\n", 15), 1);
	len = ft_strlen(argv[1]);
	if (len < 4 || ft_strcmp(argv[1] + (len - 4), ".cub") != 0)
		return (write(2, "Error\nFile must end with .cub\n", 30), 1);
	game = game_parser(argv[1]);
	if (!game)
		return (write(2, "Failed to parse the map\n", 27), 1);
	fdf = init_fdf(game);
	if (!fdf)
		return (1);
	draw_3d_view(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->img, 0, 0);
	mlx_hook(fdf->window, 2, 1L << 0, key_press, fdf);
	mlx_hook(fdf->window, 3, 1L << 1, key_release, fdf);
	mlx_hook(fdf->window, 17, 0, close_all, fdf);
	mlx_loop_hook(fdf->mlx, change_dir, fdf);
	mlx_loop(fdf->mlx);
	return (0);
}
