/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 10:10:58 by rrajaobe          #+#    #+#             */
/*   Updated: 2023/03/03 22:23:21 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	ft_destroy_textures(t_game *game)
{
	if (game->texture_no != NULL)
		mlx_delete_texture (game->texture_no);
	if (game->texture_so != NULL)
		mlx_delete_texture (game->texture_so);
	if (game->texture_ea != NULL)
		mlx_delete_texture (game->texture_ea);
	if (game->texture_we != NULL)
		mlx_delete_texture (game->texture_we);
	mlx_delete_image (game->mlx, game->backgr);
	mlx_delete_image (game->mlx, game->foregr);
}

void	ft_destroy_tab(char **tab)
{
	int	i;

	if (tab == NULL)
		return ;
	i = -1;
	while (tab[++i] != NULL)
		free (tab[i]);
	free (tab);
}

void	ft_destroy_game(void *ptr)
{
	t_game	*game;

	if (ptr == NULL)
		return ;
	game = (t_game *) ptr;
	ft_destroy_textures (game);
	free (game->wall_no);
	free (game->wall_so);
	free (game->wall_we);
	free (game->wall_ea);
	free (game->ceiling);
	free (game->floor);
	ft_destroy_tab (game->map);
	exit (0);
}
