/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:17:43 by katchogl          #+#    #+#             */
/*   Updated: 2023/03/03 19:01:17 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	ft_set_rgb(t_game *game, int *rgb, int value, int pos)
{
	if (pos == 0)
		*rgb |= (value << 24);
	else if (pos == 1)
		*rgb |= (value << 16);
	else if (pos == 2)
		*rgb |= (value << 8);
	else
		ft_throw (game, "invalid rgb pos");
}

static void	ft_subargs_to_rgb(t_game *game, char **subargs, int *rgb, int *pos)
{
	int	value;

	while (*subargs)
	{
		if (ft_isnbr (*subargs))
		{
			value = ft_atoi (*subargs);
			if (value >= 0 && value <= 255)
				ft_set_rgb (game, rgb, value, *pos);
			else
				ft_throw (game, "not a valid rgb number");
			(*pos)++;
			if (*pos == 3 && ft_tablen (subargs + 1) > 0)
				ft_throw (game, "too many rgbs /subargs");
		}
		else if (ft_strncmp (*subargs, ",", 2) != 0)
			ft_throw (game, "rgb value not a number");
		subargs++;
	}
}

// convert multiple color (string) rgb values to final (int) color
int	ft_to_rgb(t_game *game, char **args)
{
	char	**subargs;
	int		pos;
	int		rgb;

	pos = 0;
	rgb = 255;
	while (*args)
	{
		subargs = ft_split (*args, ',');
		if (subargs != NULL)
		{
			ft_subargs_to_rgb (game, subargs, &rgb, &pos);
			ft_destroy_tab (subargs);
			if (pos == 3 && ft_tablen (args + 1) > 0 && ft_isnbr (*(args + 1)))
				ft_throw (game, "too many rgbs /tab");
			else if (pos == 3 && ft_tablen (args + 1) > 0
				&& !ft_isnbr (*(args + 1)))
				ft_throw (game, "invalid color extra arguments /tab");
			else if (pos == 3)
				return (rgb);
		}
		args++;
	}
	ft_throw (game, "insufficient rgbs");
	return (0);
}
