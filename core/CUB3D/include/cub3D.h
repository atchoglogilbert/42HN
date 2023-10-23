/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 03:25:29 by rrajaobe          #+#    #+#             */
/*   Updated: 2023/03/03 18:47:53 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# include <math.h>
# include "MLX42.h"
# include "libft.h"
# include "libft.h"
# include "get_next_line.h"
# include "containers.h"
# define ERROR "Error\n"

typedef enum e_type
{
	T_NOT_FOUND = -1,
	T_TEXT_NO,
	T_TEXT_SO,
	T_TEXT_WE,
	T_TEXT_EA,
	T_CLR_CEIL,
	T_CLR_FLOOR,
	T_TEXT,
	T_CLR,
	T_MAP,
	T_ANY_XCPT_MAP,
	T_ANY
}	t_type;
typedef struct s_draw_attr
{
	mlx_texture_t	*texture;
	double			perp_dist;
	int				height;
	int				y_begin;
	int				y_end;
	t_dims			tex_dims;
	t_point			tex_pos;
	double			text_pos;
	double			skip_len;
	int				wall_x;
}	t_draw_attr;
typedef struct s_game
{
	int				begin;
	int				end;
	int				prev_begin;
	int				prev_end;
	int				*ceiling;
	int				*floor;
	char			*wall_no;
	char			*wall_so;
	char			*wall_ea;
	char			*wall_we;
	void			*mlx;
	char			*name;
	int				row;
	int				column;
	int				height;
	int				width;
	char			**map;
	mlx_image_t		*foregr;
	mlx_image_t		*backgr;
	t_vector		player;
	t_vector		dir;
	t_vector		camera_plane;
	double			camera_x;
	t_vector		ray;
	t_vector		delta_dist;
	t_vector		player_delta_dist;
	t_point			ray_cell;
	int				side;
	double			time;
	double			old_time;
	double			fps;
	double			transl_speed;
	double			rotat_speed;
	t_draw_attr		attr;
	mlx_texture_t	*texture_no;
	mlx_texture_t	*texture_so;
	mlx_texture_t	*texture_ea;
	mlx_texture_t	*texture_we;
	t_point			temp_step;
	char			temp_player_dir;
	char			*trimmed;
}	t_game;

void			ft_init_game(t_game *game);
void			ft_init_game_post_parsing(t_game *game);
void			ft_destroy_tab(char **tab);

// parsing
void			ft_parse(t_game *game, char *pathname);
size_t			ft_tablen(char **tab);
char			*ft_str_rm_endl(char *str);
bool			ft_isnbr(char *str);
int				ft_to_rgb(t_game *game, char **args);
t_type			ft_type(char *str);
t_type			ft_group(char *str);
int				ft_isset(t_game *game, t_type t);
void			ft_parse_map(t_game *game, int fd);
void			ft_push(t_game *game, char ***tab, char *str);
bool			ft_isempty(t_game *game, char *str);

// rendering
void			ft_prep_dda(t_game *game, int x);
unsigned int	ft_get_color(mlx_texture_t *img, int x, int y);
void			ft_put_color(mlx_image_t *img, int x, int y, unsigned int c);
void			ft_set_texture(t_game *game);
void			ft_raycaster(void *ptr);

// runtime
void			ft_on_close_key_press_handler(void *ptr);
void			ft_destroy_game(void *ptr);
void			ft_translator(void *param);
void			ft_rotator(void *param);

// utils
char			ft_map_at(t_game *game, double x, double y);
void			ft_throw(t_game *game, char *err);
#endif
