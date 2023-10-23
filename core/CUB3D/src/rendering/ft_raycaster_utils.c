/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycaster_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 15:01:56 by katchogl          #+#    #+#             */
/*   Updated: 2023/03/01 07:25:21 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// get any color from texture
unsigned int	ft_get_color(mlx_texture_t *img, int x, int y)
{
	unsigned int	*colour;

	colour = (unsigned int *)
		(img->pixels + (x + y * img->width) * sizeof (uint8_t) * 4);
	return (*colour);
}

// set any color in texture
void	ft_put_color(mlx_image_t *img, int x, int y, unsigned int colour)
{
	unsigned int	*dst;

	dst = (unsigned int *)
		(img->pixels + (x + y * img->width) * sizeof (uint8_t) * 4);
	*dst = colour;
}

// set correct texture to display
void	ft_set_texture(t_game *game)
{
	if (game->side == 0)
	{
		if (game->temp_step.x < 0)
			game->attr.texture = game->texture_no;
		else
			game->attr.texture = game->texture_so;
	}
	else
	{
		if (game->temp_step.y < 0)
			game->attr.texture = game->texture_we;
		else
			game->attr.texture = game->texture_ea;
	}
}

static void	ft_set_player_delta_dist(t_game *game)
{
	game->player_delta_dist.x = (game->ray_cell.x
			+ 1.0 - game->player.x) * game->delta_dist.x;
	game->player_delta_dist.y = (game->ray_cell.y
			+ 1.0 - game->player.y) * game->delta_dist.y;
	game->temp_step.x = 1;
	game->temp_step.y = 1;
	if (game->ray.x < 0)
	{
		game->player_delta_dist.x = (game->player.x
				- game->ray_cell.x) * game->delta_dist.x;
		game->temp_step.x = -1;
	}
	if (game->ray.y < 0)
	{
		game->player_delta_dist.y = (game->player.y
				- game->ray_cell.y) * game->delta_dist.y;
		game->temp_step.y = -1;
	}
}

//	set attrs for dda
void	ft_prep_dda(t_game *game, int x)
{
	game->camera_x = 2 * x / (double) game->width - 1;
	game->ray.x = game->dir.x + game->camera_plane.x * game->camera_x;
	game->ray.y = game->dir.y + game->camera_plane.y * game->camera_x;
	game->ray_cell.x = game->player.x;
	game->ray_cell.y = game->player.y;
	if (game->ray.x == 0)
		game->delta_dist.x = 1e30;
	else
		game->delta_dist.x = fabs (1 / game->ray.x);
	if (game->ray.y == 0)
		game->delta_dist.y = 1e30;
	else
		game->delta_dist.y = fabs (1 / game->ray.y);
	ft_set_player_delta_dist (game);
}
