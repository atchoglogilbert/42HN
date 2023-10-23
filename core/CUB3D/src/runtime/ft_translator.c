/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_translator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:48:17 by katchogl          #+#    #+#             */
/*   Updated: 2023/02/27 22:39:50 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	ft_move_up(t_game *game)
{
	if (ft_map_at (game, game->player.x + game->dir.x * game->transl_speed
			, game->player.y) == '0')
		game->player.x += game->dir.x * game->transl_speed;
	if (ft_map_at (game, game->player.x
			, game->player.y + game->dir.y * game->transl_speed) == '0')
		game->player.y += game->dir.y * game->transl_speed;
}

static void	ft_move_down(t_game *game)
{
	if (ft_map_at (game, game->player.x - game->dir.x * game->transl_speed
			, game->player.y) == '0')
		game->player.x -= game->dir.x * game->transl_speed;
	if (ft_map_at (game, game->player.x
			, game->player.y - game->dir.y * game->transl_speed) == '0')
		game->player.y -= game->dir.y * game->transl_speed;
}

static void	ft_move_left(t_game *game)
{
	if (ft_map_at (game, game->player.x - game->dir.y * game->transl_speed
			, game->player.y) == '0')
		game->player.x -= game->dir.y * game->transl_speed;
	if (ft_map_at (game, game->player.x
			, game->player.y + game->dir.x * game->transl_speed) == '0')
		game->player.y += game->dir.x * game->transl_speed;
}

static void	ft_move_right(t_game *game)
{
	if (ft_map_at (game, game->player.x + game->dir.y * game->transl_speed
			, game->player.y) == '0')
		game->player.x += game->dir.y * game->transl_speed;
	if (ft_map_at (game, game->player.x
			, game->player.y - game->dir.x * game->transl_speed) == '0')
		game->player.y -= game->dir.x * game->transl_speed;
}

void	ft_translator(void *param)
{
	t_game		*game;

	if (param == NULL)
		ft_throw (NULL, "null pointer");
	game = (t_game *) param;
	if (mlx_is_key_down (game->mlx, MLX_KEY_W))
		ft_move_up (game);
	if (mlx_is_key_down (game->mlx, MLX_KEY_S))
		ft_move_down (game);
	if (mlx_is_key_down (game->mlx, MLX_KEY_A))
		ft_move_left (game);
	if (mlx_is_key_down (game->mlx, MLX_KEY_D))
		ft_move_right (game);
}
