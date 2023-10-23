/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 20:52:29 by katchogl          #+#    #+#             */
/*   Updated: 2023/02/27 20:55:46 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	ft_rotate_left(t_game *game, double old_dir_x,
	double old_camera_plane_x)
{
	game->dir.x = game->dir.x * cos(game->rotat_speed)
		- game->dir.y * sin(game->rotat_speed);
	game->dir.y = old_dir_x * sin(game->rotat_speed)
		+ game->dir.y * cos(game->rotat_speed);
	game->camera_plane.x = game->camera_plane.x * cos(game->rotat_speed)
		- game->camera_plane.y * sin(game->rotat_speed);
	game->camera_plane.y = old_camera_plane_x * sin(game->rotat_speed)
		+ game->camera_plane.y * cos(game->rotat_speed);
}

static void	ft_rotate_right(t_game *game, double old_dir_x,
	double old_camera_plane_x)
{
	game->dir.x = game->dir.x * cos(-game->rotat_speed)
		- game->dir.y * sin(-game->rotat_speed);
	game->dir.y = old_dir_x * sin(-game->rotat_speed)
		+ game->dir.y * cos(-game->rotat_speed);
	game->camera_plane.x = game->camera_plane.x * cos(-game->rotat_speed)
		- game->camera_plane.y * sin(-game->rotat_speed);
	game->camera_plane.y = old_camera_plane_x * sin(-game->rotat_speed)
		+ game->camera_plane.y * cos(-game->rotat_speed);
}

void	ft_rotator(void *param)
{
	t_game	*game;
	double	old_dir_x;
	double	old_camera_plane_x;

	if (param == NULL)
		ft_throw (NULL, "null pointer");
	game = (t_game *) param;
	old_dir_x = game->dir.x;
	old_camera_plane_x = game->camera_plane.x;
	if (mlx_is_key_down (game->mlx, MLX_KEY_LEFT))
		ft_rotate_left (game, old_dir_x, old_camera_plane_x);
	else if (mlx_is_key_down (game->mlx, MLX_KEY_RIGHT))
		ft_rotate_right (game, old_dir_x, old_camera_plane_x);
}
