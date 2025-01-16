/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:53:22 by lsaiti            #+#    #+#             */
/*   Updated: 2025/01/16 17:25:51 by lsaiti           ###   ########.fr       */
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
	fdf->key_left = 0;
	fdf->key_right = 0;
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		return (NULL);
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
	int i = 0;
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
double	biggest(double a, double b)
{
	if (a < b)
		return (b);
	return (a);
}

int	is_wall(t_map_utils *fdf, double x, double y)
{
	double oldx = (int)fdf->game->player->x;
	double oldy = (int)fdf->game->player->y;
	if (x < 0 || y < 0)
		return (1);
	x = (int)x;
	y = (int)y;
	if (x == oldx && y == oldy)
		return (0);
	if (fdf->map[(int)y][(int)x] == '1')
		return (1);
	return (0);
}

int key_press(int keycode, t_map_utils *fdf)
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

int key_release(int keycode, t_map_utils *fdf)
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

int change_dir(t_map_utils *fdf)
{
    double angle = fdf->game->player->angle;
    double move_speed = 0.015;
    double rot_speed = M_PI_4 / 20;
    double new_x = fdf->game->player->x;
    double new_y = fdf->game->player->y;

    if (fdf->key_w) {
        new_x += cos(angle) * move_speed;
        new_y += sin(angle) * move_speed;
    }
    if (fdf->key_s) {
        new_x -= cos(angle) * move_speed;
        new_y -= sin(angle) * move_speed;
    }
    if (fdf->key_a) {
        new_x += sin(angle) * move_speed;
        new_y -= cos(angle) * move_speed;
    }
    if (fdf->key_d) {
        new_x -= sin(angle) * move_speed;
        new_y += cos(angle) * move_speed;
    }
    if (!is_wall(fdf, new_x, new_y)) {
        fdf->game->player->x = new_x;
        fdf->game->player->y = new_y;
    }
    if (fdf->key_left) {
        angle -= rot_speed;
    }
    if (fdf->key_right) {
        angle += rot_speed;
    }
    fdf->game->player->angle = angle;
    fdf->game->dirX = cos(angle);
    fdf->game->dirY = sin(angle);
    draw_3d_view(fdf);
    mlx_clear_window(fdf->mlx, fdf->window);
    mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->img, 0, 0);
    return (0);
}

char	*strcpy_no_nl(t_game *game, char *source, char *dest, int size)
{
	int	i;

	i = 0;
	while (source[i] && source[i] != '\n' && i < size)
	{
		if (source[i] == '1')
			dest[i] = source[i];
		else
		{
			if (source[i] == 'N' || source[i] == 'W' || source[i] == 'S' || source[i] == 'E')
				game->player->direction = source[i];
			dest[i] = '0';
		}
		i++;
	}
	while (i < size)
		dest[i++] = '\0';
	dest[i] = '\0';
	return (dest);
}

double	get_angle(char c)
{
	if (c == 'N')
		return (-M_PI_2);
	else if (c == 'S')
		return (M_PI_2);
	else if (c == 'E')
		return (M_PI);
	else
		return (0);
}

void	get_player_pos(t_game *game)
{
	t_map *current = game->map;
	int	i;
	int	j;

	j = 0;
	while (current)
	{
		i = 0;
		while (current->coor[i])
		{
			if (current->coor[i] == 'N' || current->coor[i] == 'W' || current->coor[i] == 'S' || current->coor[i] == 'E')
			{
				game->player->x = i + 0.5;
				game->player->y = j + 0.5;
				game->posX = i + 0.5;
				game->posY = j + 0.5;
				game->player->angle = get_angle(current->coor[i]);
				game->dirX = cos(game->player->angle);
				game->dirY = sin(game->player->angle);
				game->planeX = -sin(game->player->angle) * 0.66;
                game->planeY = cos(game->player->angle) * 0.66;
			}
			i++;
		}
		current = current->next;
		j++;
	}
}

char	**get_full_map(t_game *game)
{
	char	**map;
	t_map *current = game->map;
	int i;

	map = malloc(sizeof(char *) * (game->height_max + 1));
	if (!map)
		return (NULL);
	i = 0;
	get_player_pos(game);
	while (current)
	{
		map[i] = malloc(sizeof(char) * (game->length_max + 1));
		map[i] = strcpy_no_nl(game, current->coor, map[i], game->length_max);
		i++;
		current = current->next;
	}
	map[i] = NULL;
	return (map);
}

void	printer_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_map_utils	*fdf;
	t_game		*game;
	int			len;

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
	printer_map(fdf->map);
	fdf->game = game;
	fdf->img = mlx_new_image(fdf->mlx, LENGTH, HEIGHT);
	fdf->img_data = mlx_get_data_addr(fdf->img, &fdf->bpp, &fdf->size_line,
			&fdf->endian);
	draw_3d_view(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->img, 0, 0);
	mlx_hook(fdf->window, 2, 1L<<0, key_press, fdf);    // KeyPress
    mlx_hook(fdf->window, 3, 1L<<1, key_release, fdf);  // KeyRelease
    mlx_hook(fdf->window, 17, 0, close_all, fdf);       // CloseWindow
    mlx_loop_hook(fdf->mlx, change_dir, fdf);            // Game loop
	mlx_loop(fdf->mlx);
	return (0);
}
