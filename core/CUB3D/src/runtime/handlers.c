/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 21:01:04 by katchogl          #+#    #+#             */
/*   Updated: 2023/02/27 21:13:24 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_on_close_key_press_handler(void *param)
{
	t_game	*game;

	if (param == NULL)
		return ;
	game = (t_game *) param;
	if (mlx_is_key_down (game->mlx, MLX_KEY_ESCAPE))
		ft_destroy_game (game);
}
