/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 13:37:50 by katchogl          #+#    #+#             */
/*   Updated: 2023/03/02 03:17:52 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// get specific t_type from str
t_type	ft_type(char *str)
{
	if (ft_strncmp (str, "NO", 3) == 0)
		return (T_TEXT_NO);
	else if (ft_strncmp (str, "SO", 3) == 0)
		return (T_TEXT_SO);
	else if (ft_strncmp (str, "WE", 3) == 0)
		return (T_TEXT_WE);
	else if (ft_strncmp (str, "EA", 3) == 0)
		return (T_TEXT_EA);
	else if (ft_strncmp (str, "C", 2) == 0)
		return (T_CLR_CEIL);
	else if (ft_strncmp (str, "F", 2) == 0)
		return (T_CLR_FLOOR);
	return (T_NOT_FOUND);
}

// get specific t_type group from str
t_type	ft_group(char *str)
{
	if (ft_strncmp (str, "NO", 3) == 0
		|| ft_strncmp (str, "SO", 3) == 0
		|| ft_strncmp (str, "WE", 3) == 0
		|| ft_strncmp (str, "EA", 3) == 0)
		return (T_TEXT);
	if (ft_strncmp (str, "C", 2) == 0
		|| ft_strncmp (str, "F", 2) == 0)
		return (T_CLR);
	return (T_NOT_FOUND);
}

// check if a config or class of config is set
int	ft_isset(t_game *game, t_type t)
{
	if (t <= T_NOT_FOUND || t > T_ANY)
		ft_throw (game, "invalid type");
	if ((t >= T_ANY_XCPT_MAP || t == T_TEXT_NO) && game->wall_no == NULL)
		return (1);
	if ((t >= T_ANY_XCPT_MAP || t == T_TEXT_SO) && game->wall_so == NULL)
		return (2);
	if ((t >= T_ANY_XCPT_MAP || t == T_TEXT_WE) && game->wall_we == NULL)
		return (3);
	if ((t >= T_ANY_XCPT_MAP || t == T_TEXT_EA) && game->wall_ea == NULL)
		return (4);
	if ((t >= T_ANY_XCPT_MAP || t == T_CLR_CEIL) && game->ceiling == NULL)
		return (5);
	if ((t >= T_ANY_XCPT_MAP || t == T_CLR_FLOOR) && game->floor == NULL)
		return (6);
	if ((t > T_ANY_XCPT_MAP || t == T_MAP) && game->map == NULL)
		return (7);
	return (0);
}
