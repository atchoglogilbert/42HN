/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 01:18:52 by katchogl          #+#    #+#             */
/*   Updated: 2023/03/03 21:10:46 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	ft_validate(t_game *game, int i, int j, bool *player)
{
	if ((game->trimmed[j] != '1' && game->trimmed[j] != ' ')
		&& ((game->row > 1 && (i == 0 || i == game->row - 1))
			|| ((game->row == 1 || game->row > 1)
				&& (j == 0 || j == (int) ft_strlen (game->trimmed) - 1))))
		ft_throw (game, "invalid border");
	else if (game->trimmed[j] == 'N' || game->trimmed[j] == 'S'
		|| game->trimmed[j] == 'W' || game->trimmed[j] == 'E')
	{
		if (!*player)
			*player = true;
		else
			ft_throw (game, "ambiguous player location");
	}	
}

static void	ft_validate_map(t_game *game)
{
	int		i;
	int		j;
	bool	player;

	i = -1;
	player = false;
	while (++i < game->row)
	{
		game->trimmed = ft_strtrim (game->map[i], " ");
		j = -1;
		while (game->trimmed[++j])
			ft_validate (game, i, j, &player);
		free (game->trimmed);
	}
	if (!player)
		ft_throw (game, "player not found");
}

static void	ft_fix_map(t_game *game)
{
	char	*temp;
	int		i;
	int		j;

	i = -1;
	while (++i < game->row)
	{
		j = -1;
		while (game->map[i][++j] != '\0')
			if (game->map[i][j] == ' ')
				game->map[i][j] = '1';
	}
	i = -1;
	while (++i < game->row)
	{
		while ((int) ft_strlen (game->map[i]) < game->column)
		{
			temp = ft_strjoin (game->map[i], "1");
			free (game->map[i]);
			game->map[i] = temp;
		}
	}
}

static void	ft_raw_map(t_game *game, int fd, char *ln)
{
	int		i;

	if (ln == NULL)
		ln = get_next_line (fd);
	while (ln != NULL && ft_strlen (ln) > 1)
	{
		ln = ft_str_rm_endl (ln);
		if (ft_isempty (game, ln))
			ft_throw (game, "empty row");
		i = -1;
		while (ln[++i])
		{
			if (ln[i] != ' ' && ln[i] != '0' && ln[i] != '1' && ln[i] != 'N'
				&& ln[i] != 'S' && ln[i] != 'W' && ln[i] != 'E')
				ft_throw (game, "invalid map character");
		}
		ft_push (game, &game->map, ln);
		free (ln);
		ln = get_next_line (fd);
	}
	free (ln);
}

void	ft_parse_map(t_game *game, int fd)
{
	char	*ln;

	ln = get_next_line (fd);
	while (ln != NULL && ft_isempty (game, ln))
	{
		free (ln);
		ln = get_next_line (fd);
	}
	ft_raw_map (game, fd, ln);
	if (game->map == NULL)
		ft_throw (game, "failed to get raw map");
	--game->row;
	while (game->map[++game->row])
		if ((int) ft_strlen (game->map[game->row]) > game->column)
			game->column = ft_strlen (game->map[game->row]);
	if (game->row < 3)
		ft_throw (game, "map count of rows not allowed");
	ft_validate_map (game);
	ft_fix_map (game);
}
