/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <tde-nico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 11:30:33 by tde-nico          #+#    #+#             */
/*   Updated: 2022/02/16 10:30:20 by tde-nico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	render_player(t_game *game, int x, int y)
{
	if (game->player.curr_frame_duration >= game->player.frame_duration)
	{
		game->player.curr_frame_duration = 0;
		game->player.curr_frame++;
	}
	if (game->player.curr_frame >= game->player.frame_count)
		game->player.curr_frame = 0;
	mlx_put_image_to_window(game->mlx, game->win,
		game->player.frames[game->player.curr_frame],
		x * IMG_SIZE, y * IMG_SIZE);
	game->player.curr_frame_duration++;
}

void	render_simple_tile(t_game *game, int x, int y, int *col_frame)
{
	int			pos;

	pos = ft_strchr(MAPSET, game->map[y][x]) - MAPSET;
	if (pos == 0)
	{
		if (*col_frame == 0)
			mlx_put_image_to_window(game->mlx, game->win,
				game->st_imgs[0], x * IMG_SIZE, (y + 1) * IMG_SIZE);
		if (*col_frame == 1)
			mlx_put_image_to_window(game->mlx, game->win,
				game->col_second, x * IMG_SIZE, (y + 1) * IMG_SIZE);
	}
	else
		mlx_put_image_to_window(game->mlx, game->win,
			game->st_imgs[pos], x * IMG_SIZE, (y + 1) * IMG_SIZE);
}

int	render_text(t_game *game)
{
	char	*str;

	str = ft_itoa(game->moves);
	if (game->collects > 0)
		mlx_string_put(game->mlx, game->win,
			(game->win_size.x - 1) * IMG_SIZE, IMG_SIZE / 2 + 5, -1, str);
	else
		mlx_string_put(game->mlx, game->win,
			(game->win_size.x - 1) * IMG_SIZE, IMG_SIZE / 2 + 5, 15921152, str);
	free(str);
	return (0);
}

int	render(t_game *game)
{
	static int	col_frame = 0;
	int			y;
	int			x;

	mlx_clear_window(game->mlx, game->win);
	y = -1;
	while (game->map[++y])
	{
		x = -1;
		while (game->map[y][++x])
		{
			if (game->map[y][x] == 'P')
			{
				mlx_put_image_to_window(game->mlx, game->win,
					game->st_imgs[2], x * IMG_SIZE, (y + 1) * IMG_SIZE);
				render_player(game, x, y + 1);
			}
			else
				render_simple_tile(game, x, y, &col_frame);
		}
	}
	col_frame++;
	if (col_frame > 1)
		col_frame = 0;
	return (render_text(game));
}
