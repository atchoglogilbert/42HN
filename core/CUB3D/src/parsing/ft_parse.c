/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 06:53:52 by katchogl          #+#    #+#             */
/*   Updated: 2023/03/03 18:20:33 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// set textures and colors with checked and safe arguments
static void	ft_set(t_game *game, t_type t, char **args)
{
	int	**ptr;

	ptr = NULL;
	if (t == T_TEXT_NO)
		game->wall_no = ft_strdup (args[0]);
	else if (t == T_TEXT_SO)
		game->wall_so = ft_strdup (args[0]);
	else if (t == T_TEXT_WE)
		game->wall_we = ft_strdup (args[0]);
	else if (t == T_TEXT_EA)
		game->wall_ea = ft_strdup (args[0]);
	else if (t == T_CLR_CEIL)
		ptr = &game->ceiling;
	else if (t == T_CLR_FLOOR)
		ptr = &game->floor;
	if (ptr != NULL)
	{
		*ptr = (int *) malloc (sizeof (int));
		if (*ptr == NULL)
			ft_throw (game, "malloc fail");
		**ptr = ft_to_rgb (game, args);
	}
}

// catch all exception related to textures and colors data
static void	ft_catch(t_game *game, t_type t, t_type g, char **args)
{
	if (t == T_NOT_FOUND || t == T_MAP)
		ft_throw (game, "configuration not recognized");
	else if (ft_isset (game, t) == 0)
		ft_throw (game, "configuration already set");
	else if (args == NULL || *args == NULL)
		ft_throw (game, "configuration arguments not found");
	else if (g == T_TEXT && ft_tablen (args) > 1)
		ft_throw (game, "ambiguous texture pathname");
}

// iterate file until all texts and colors are set, map causes error or eof
void	ft_parse_texts_colors(t_game *game, int fd)
{
	char	*ln;
	char	**tab;

	ln = get_next_line (fd);
	while (ln != NULL)
	{
		ln = ft_str_rm_endl (ln);
		tab = ft_split (ln, ' ');
		if (ft_tablen (tab) > 0)
		{
			ft_catch (game, ft_type (tab[0]), ft_group (tab[0]), tab + 1);
			ft_set (game, ft_type (tab[0]), tab + 1);
		}
		ft_destroy_tab (tab);
		free (ln);
		if (ft_isset (game, T_ANY_XCPT_MAP) == 0)
			return ;
		ln = get_next_line (fd);
	}
}

// throw an config str error if the errno is valid
static void	ft_catch_all(t_game *game, int errno)
{
	if (errno < 0 || errno > 7)
		ft_throw (game, "invalid errno");
	if (errno == 1)
		ft_throw (game, "north texture path name not found");
	if (errno == 2)
		ft_throw (game, "south texture path name not found");
	if (errno == 3)
		ft_throw (game, "west texture path name not found");
	if (errno == 4)
		ft_throw (game, "east texture path name not found");
	if (errno == 5)
		ft_throw (game, "ceiling color not found");
	if (errno == 6)
		ft_throw (game, "floor color not found");
	if (errno == 7)
		ft_throw (game, "map not found");
	if (errno != 0)
		ft_throw (game, "failed to throw errno");
}

// parse a .cub file
void	ft_parse(t_game *game, char *pathname)
{
	int		fd;

	if (pathname == NULL)
		ft_throw (game, "pathname not found");
	if (ft_strlen (pathname) < 4
		|| ft_strncmp (pathname + ft_strlen (pathname) - 4, ".cub", 5) != 0)
		ft_throw (game, "invalid map extension");
	fd = open (pathname, O_RDONLY);
	if (fd == -1)
		ft_throw (game, "failed to open file");
	ft_parse_texts_colors (game, fd);
	ft_catch_all (game, ft_isset (game, T_ANY_XCPT_MAP));
	ft_parse_map (game, fd);
	close (fd);
	ft_catch_all (game, ft_isset (game, T_ANY));
}
