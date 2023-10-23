/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 03:26:56 by rrajaobe          #+#    #+#             */
/*   Updated: 2023/03/03 20:09:44 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// paint ceiling and floor by putting one px one at a time on the entire window
static void	ft_background(t_game *game)
{
	int					x;
	int					y;

	game->backgr = mlx_new_image (game->mlx, game->width, game->height);
	if (game->backgr == NULL)
		ft_throw (game, "failed to create backgr image");
	x = -1;
	while (++x < game->width)
	{
		y = -1;
		while (++y < game->height)
		{
			if (y < game->height / 2)
				mlx_put_pixel (game->backgr, x, y, *game->ceiling);
			else
				mlx_put_pixel (game->backgr, x, y, *game->floor);
		}
	}
	mlx_image_to_window (game->mlx, game->backgr, 0, 0);
}

// orientate player in correct dir if dir is diff from north
static void	ft_orientate_player(t_game *game)
{
	if (game->temp_player_dir == 'S')
	{
		game->dir.x = 1;
		game->camera_plane.y = -0.66;
	}
	else if (game->temp_player_dir == 'W')
	{
		game->dir.x = 0;
		game->dir.y = -1;
		game->camera_plane.x = -0.66;
		game->camera_plane.y = 0;
	}
	else if (game->temp_player_dir == 'E')
	{
		game->dir.x = 0;
		game->dir.y = 1;
		game->camera_plane.x = 0.66;
		game->camera_plane.y = 0;
	}
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		ft_throw (NULL, "invalid number of arguments");
	ft_init_game(&game);
	ft_parse (&game, argv[1]);
	ft_init_game_post_parsing (&game);
	ft_orientate_player (&game);
	ft_background (&game);
	mlx_loop_hook (game.mlx, ft_raycaster, &game);
	mlx_loop_hook (game.mlx, ft_translator, &game);
	mlx_loop_hook (game.mlx, ft_rotator, &game);
	mlx_loop_hook (game.mlx, ft_on_close_key_press_handler, &game);
	mlx_close_hook (game.mlx, ft_destroy_game, &game);
	mlx_loop (game.mlx);
	return (0);
}
