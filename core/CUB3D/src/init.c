/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 03:31:10 by rrajaobe          #+#    #+#             */
/*   Updated: 2023/03/03 18:44:20 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	ft_init_parser(t_game *game)
{
	game->wall_no = NULL;
	game->wall_so = NULL;
	game->wall_ea = NULL;
	game->wall_we = NULL;
	game->floor = NULL;
	game->ceiling = NULL;
}

static void	ft_init_raycaster(t_game *game)
{
	game->dir.x = -1;
	game->dir.y = 0;
	game->camera_plane.x = 0;
	game->camera_plane.y = 0.66;
	game->time = 0;
	game->old_time = 0;
	game->texture_no = NULL;
	game->texture_so = NULL;
	game->texture_ea = NULL;
	game->texture_we = NULL;
	game->foregr = NULL;
}

// set some game attrs to default values and init others
void	ft_init_game(t_game *game)
{
	game->map = NULL;
	game->row = 0;
	game->column = 0;
	game->name = "Cub3D";
	mlx_set_setting (MLX_STRETCH_IMAGE, true);
	game->backgr = NULL;
	ft_init_parser (game);
	ft_init_raycaster (game);
	game->width = 1920;
	game->height = 1280;
	game->mlx = mlx_init (game->width, game->height, game->name, false);
}

// set game->player: the player's coordinates
static void	ft_init_player(t_game *game)
{
	char	c;

	game->player.x = -1;
	while (++game->player.x < game->row)
	{
		game->player.y = -1;
		while (++game->player.y < game->column)
		{
			c = ft_map_at (game, game->player.x, game->player.y);
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				return ;
		}
	}
	ft_throw (game, "failed to set player coordinates");
}

void	ft_init_game_post_parsing(t_game *game)
{
	if (game->wall_no == NULL || game->wall_so == NULL
		|| game->wall_ea == NULL || game->wall_we == NULL)
		ft_throw (game, "textures' paths not found");
	game->texture_no = mlx_load_png (game->wall_no);
	game->texture_so = mlx_load_png (game->wall_so);
	game->texture_ea = mlx_load_png (game->wall_ea);
	game->texture_we = mlx_load_png (game->wall_we);
	if (game->texture_no == NULL || game->texture_so == NULL
		|| game->texture_ea == NULL || game->texture_we == NULL)
		ft_throw (game, "failed to load textures");
	ft_init_player (game);
	if (ft_map_at (game, game->player.x, game->player.y) == '1')
		ft_throw (game, "player coordinates already filled by wall");
	game->temp_player_dir = game->map[(int) game->player.x]
	[(int) game->player.y];
	game->map[(int) game->player.x][(int) game->player.y] = '0';
}
