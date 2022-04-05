/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <tde-nico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 17:29:17 by tde-nico          #+#    #+#             */
/*   Updated: 2022/02/16 09:42:06 by tde-nico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <stdio.h>
# include <fcntl.h>

# define IMG_SIZE 32
# define MAPSET "CE01KP"

# define K_W 13
# define K_A 0
# define K_S 1
# define K_D 2
# define K_ESC 53

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_player
{
	t_point	pos;
	int		frame_duration;
	int		curr_frame_duration;
	int		curr_frame;
	int		frame_count;
	void	*frames[2];
	int		height;
	int		width;
}	t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_point		win_size;
	int			loop;
	t_player	player;
	int			collects;
	int			moves;
	char		**map;
	void		*st_imgs[5];
	int			st_heights[5];
	int			st_widths[5];
	void		*col_second;
}	t_game;

char	*ft_charjoin(char *s1, char s2);
char	**init_map(char *file, t_game *game);
int		init_animations(t_game *game);
int		render(t_game *game);
int		input(int key, t_game *game);
int		raise(int err);
void	free_map(char **map);
int		end(t_game *game);
void	print(t_game *game, char c);

#endif
