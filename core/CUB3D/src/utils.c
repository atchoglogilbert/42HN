/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 07:23:29 by katchogl          #+#    #+#             */
/*   Updated: 2023/03/03 19:05:55 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// safe get map value
char	ft_map_at(t_game *game, double x, double y)
{
	if (game == NULL || game->map == NULL)
		ft_throw (game, "null ptr");
	if (x < 0 || y < 0)
		ft_throw (game, "invalid negative coordinates");
	if ((int) x >= game->row || (int) y >= game->column)
		ft_throw (game, "coordinates out of bounds");
	return (game->map[(int) x][(int) y]);
}

// throw an error
void	ft_throw(t_game *game, char *err)
{
	ft_putstr_fd ("\001\033[0;31m\002Error\n", 2);
	ft_putendl_fd (err, 2);
	ft_putstr_fd ("\001\033[0m\002", 2);
	ft_destroy_game (game);
	exit (1);
}
