/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycaster.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 14:50:55 by katchogl          #+#    #+#             */
/*   Updated: 2023/03/03 18:58:14 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// draw a single wall
static void	ft_draw_wall(t_game *game, int x)
{
	--game->attr.y_begin;
	while (++game->attr.y_begin < game->attr.y_end)
	{
		game->attr.tex_pos.y = game->attr.text_pos;
		if ((uint32_t)game->attr.tex_pos.y >= game->attr.texture->height)
			game->attr.tex_pos.y = game->attr.texture->height;
		game->attr.text_pos += game->attr.skip_len;
		ft_put_color(game->foregr, x, game->attr.y_begin, \
			ft_get_color(game->attr.texture, game->attr.tex_pos.x,
				game->attr.tex_pos.y));
	}
}

// find which loc of texture to get color from
static void	ft_calculate_texture_dims(t_game *game)
{
	double	wall_x;

	if (game->side == 0)
		wall_x = game->player.y + game->attr.perp_dist * game->ray.y;
	else
		wall_x = game->player.x + game->attr.perp_dist * game->ray.x;
	wall_x -= floor (wall_x);
	game->attr.tex_pos.x = (int)(wall_x * (double) game->attr.texture->width);
	if ((game->side == 0 && game->ray.x < 0)
		|| (game->side == 1 && game->ray.y > 0))
		game->attr.tex_pos.x = game->attr.texture->width
			- game->attr.tex_pos.x - 1;
	game->attr.skip_len = (double) game->attr.texture->height
		/ game->attr.height;
	game->attr.text_pos = (game->attr.y_begin - game->height / 2
			+ game->attr.height / 2) * game->attr.skip_len;
}

// calculate perpendicular dist or distance to avoid fisheye effect
static void	ft_calculate_perp_dist(t_game *game)
{
	if (game->side == 0)
		game->attr.perp_dist = game->player_delta_dist.x
			- game->delta_dist.x;
	else
		game->attr.perp_dist = game->player_delta_dist.y
			- game->delta_dist.y;
	game->attr.height = (int)(game->height / game->attr.perp_dist);
	game->attr.y_begin = -game->attr.height / 2 + game->height / 2;
	if (game->attr.y_begin < 0)
		game->attr.y_begin = 0;
	game->attr.y_end = game->attr.height / 2 + game->height / 2;
	if (game->attr.y_end >= game->height)
		game->attr.y_end = game->height - 1;
}

// lengthen ray until it hits an opaque object or final walls: dda
static void	ft_find_object(t_game *game)
{
	while (true)
	{
		game->side = 0;
		if (game->player_delta_dist.x < game->player_delta_dist.y
			&& game->ray.x < 0)
			--game->ray_cell.x;
		else if (game->player_delta_dist.x < game->player_delta_dist.y)
			++game->ray_cell.x;
		else if (game->player_delta_dist.x >= game->player_delta_dist.y
			&& game->ray.y < 0)
			--game->ray_cell.y;
		else if (game->player_delta_dist.x >= game->player_delta_dist.y)
			++game->ray_cell.y;
		if (game->player_delta_dist.x >= game->player_delta_dist.y)
			game->side = 1;
		if (game->player_delta_dist.x < game->player_delta_dist.y)
			game->player_delta_dist.x += game->delta_dist.x;
		else
			game->player_delta_dist.y += game->delta_dist.y;
		if (ft_map_at (game, game->ray_cell.x, game->ray_cell.y) == '1')
			return ;
	}
}

//	Cast rays on each column of the window until they hit an opaque object
void	ft_raycaster(void *ptr)
{
	t_game	*game;
	int		x;

	if (ptr == NULL)
		return ;
	game = (t_game *) ptr;
	x = -1;
	if (game->foregr != NULL)
		mlx_delete_image (game->mlx, game->foregr);
	game->foregr = mlx_new_image (game->mlx, game->width, game->height);
	while (++x < game->width)
	{
		ft_prep_dda (game, x);
		ft_find_object (game);
		ft_calculate_perp_dist (game);
		ft_set_texture (game);
		ft_calculate_texture_dims (game);
		ft_draw_wall (game, x);
	}
	game->old_time = game->time;
	game->time = mlx_get_time ();
	game->fps = game->time - game->old_time;
	mlx_image_to_window (game->mlx, game->foregr, 0, 0);
	game->transl_speed = game->fps * 5.0;
	game->rotat_speed = game->fps * 3.0;
}
