/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:53:22 by lsaiti            #+#    #+#             */
/*   Updated: 2025/01/18 19:07:29 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_all(t_map_utils *cub)
{
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
	free(cub);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_map_utils	*cub;
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
	cub = init_cub(game);
	if (!cub)
		return (1);
	draw_3d_view(cub);
	mlx_put_image_to_window(cub->mlx, cub->window, cub->img, 0, 0);
	mlx_hook(cub->window, 2, 1L << 0, key_press, cub);
	mlx_hook(cub->window, 3, 1L << 1, key_release, cub);
	mlx_hook(cub->window, 17, 0, close_all, cub);
	mlx_loop_hook(cub->mlx, change_dir, cub);
	mlx_loop(cub->mlx);
	return (0);
}
