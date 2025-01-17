/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:53:22 by lsaiti            #+#    #+#             */
/*   Updated: 2025/01/17 14:15:26 by lsaiti           ###   ########.fr       */
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

int main(int argc, char **argv)
{
	t_map_utils *fdf;
	t_game *game;
	int len;

	(void)argv;
	if (argc != 2)
	{
		write(2, "Bad arguments!\n", 15);
		return (1);
	}
	len = ft_strlen(argv[1]);
	if (len < 4 || ft_strcmp(argv[1] + (len - 4), ".cub") != 0)
	{
		write(2, "Error\nFile must end with .cub\n", 30);
		return (1);
	}
	game = game_parser(argv[1]);
	if (!game)
	{
		perror("Failed to parse the map");
		return (1);
	}
	fdf = map_init();
	if (!fdf)
	{
		write(2, "FAILED TO INIT MAP!\n", 20);
		return (1);
	}
	fdf->map = get_full_map(game);
	if (!fdf->map) {
		fprintf(stderr, "Error: Failed to load map.\n");
		close_all(fdf);
		return (1);
	}
	printer_map(fdf->map);
	fdf->game = game;
	fdf->img = mlx_new_image(fdf->mlx, LENGTH, HEIGHT);
	if (!fdf->img) {
		fprintf(stderr, "Error: Failed to create image.\n");
		close_all(fdf);
		return (1);
	}
	fdf->img_data = mlx_get_data_addr(fdf->img, &fdf->bpp, &fdf->size_line, &fdf->endian);

	// Vérifiez et chargez la texture nord
	printf("Loading north texture from path: %s\n", fdf->game->path_no);
	fdf->game->tex_no.img = mlx_xpm_file_to_image(fdf->mlx, fdf->game->path_no, &fdf->game->tex_no.width, &fdf->game->tex_no.height);
	if (!fdf->game->tex_no.img)
	{
		perror("Failed to load north texture");
		close_all(fdf);
		return (1);
	}
	fdf->game->tex_no.addr = (int *)mlx_get_data_addr(fdf->game->tex_no.img, &fdf->game->tex_no.bpp, &fdf->game->tex_no.size_line, &fdf->game->tex_no.endian);
	printf("North texture loaded: width=%d, height=%d\n", fdf->game->tex_no.width, fdf->game->tex_no.height);

	// Vérifiez et chargez la texture sud
	printf("Loading south texture from path: %s\n", fdf->game->path_so);
	fdf->game->tex_so.img = mlx_xpm_file_to_image(fdf->mlx, fdf->game->path_so, &fdf->game->tex_so.width, &fdf->game->tex_so.height);
	if (!fdf->game->tex_so.img)
	{
		perror("Failed to load south texture");
		close_all(fdf);
		return (1);
	}
	fdf->game->tex_so.addr = (int *)mlx_get_data_addr(fdf->game->tex_so.img, &fdf->game->tex_so.bpp, &fdf->game->tex_so.size_line, &fdf->game->tex_so.endian);
	printf("South texture loaded: width=%d, height=%d\n", fdf->game->tex_so.width, fdf->game->tex_so.height);

	// Vérifiez et chargez la texture ouest
	printf("Loading west texture from path: %s\n", fdf->game->path_we);
	fdf->game->tex_we.img = mlx_xpm_file_to_image(fdf->mlx, fdf->game->path_we, &fdf->game->tex_we.width, &fdf->game->tex_we.height);
	if (!fdf->game->tex_we.img)
	{
		perror("Failed to load west texture");
		close_all(fdf);
		return (1);
	}
	fdf->game->tex_we.addr = (int *)mlx_get_data_addr(fdf->game->tex_we.img, &fdf->game->tex_we.bpp, &fdf->game->tex_we.size_line, &fdf->game->tex_we.endian);
	printf("West texture loaded: width=%d, height=%d\n", fdf->game->tex_we.width, fdf->game->tex_we.height);

	// Vérifiez et chargez la texture est
	printf("Loading east texture from path: %s\n", fdf->game->path_ea);
	fdf->game->tex_ea.img = mlx_xpm_file_to_image(fdf->mlx, fdf->game->path_ea, &fdf->game->tex_ea.width, &fdf->game->tex_ea.height);
	if (!fdf->game->tex_ea.img)
	{
		perror("Failed to load east texture");
		close_all(fdf);
		return (1);
	}
	fdf->game->tex_ea.addr = (int *)mlx_get_data_addr(fdf->game->tex_ea.img, &fdf->game->tex_ea.bpp, &fdf->game->tex_ea.size_line, &fdf->game->tex_ea.endian);
	printf("East texture loaded: width=%d, height=%d\n", fdf->game->tex_ea.width, fdf->game->tex_ea.height);

	draw_3d_view(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->img, 0, 0);
	mlx_hook(fdf->window, 2, 1L << 0, key_press, fdf);    // KeyPress
	mlx_hook(fdf->window, 3, 1L << 1, key_release, fdf);  // KeyRelease
	mlx_hook(fdf->window, 17, 0, close_all, fdf);         // CloseWindow
	mlx_loop_hook(fdf->mlx, change_dir, fdf);             // Game loop
	mlx_loop(fdf->mlx);

	return (0);
}
