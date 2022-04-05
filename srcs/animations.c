/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <tde-nico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 14:42:48 by tde-nico          #+#    #+#             */
/*   Updated: 2022/02/16 09:48:12 by tde-nico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	init_animations(t_game *game)
{
	game->player.frame_count = 2;
	game->player.frame_duration = 1;
	game->player.curr_frame = 0;
	game->player.curr_frame_duration = 0;
	game->player.frames[0] = mlx_xpm_file_to_image(game->mlx,
			"xpm/player_0.xpm", &(game->player.width), &(game->player.height));
	game->player.frames[1] = mlx_xpm_file_to_image(game->mlx,
			"xpm/player_1.xpm", &(game->player.width), &(game->player.height));
	game->st_imgs[0] = mlx_xpm_file_to_image(game->mlx,
			"xpm/collect.xpm", &(game->st_heights[0]), &(game->st_widths[0]));
	game->st_imgs[1] = mlx_xpm_file_to_image(game->mlx,
			"xpm/exit.xpm", &(game->st_heights[1]), &(game->st_widths[1]));
	game->st_imgs[2] = mlx_xpm_file_to_image(game->mlx,
			"xpm/floor.xpm", &(game->st_heights[2]), &(game->st_widths[2]));
	game->st_imgs[3] = mlx_xpm_file_to_image(game->mlx,
			"xpm/wall.xpm", &(game->st_heights[3]), &(game->st_widths[3]));
	game->st_imgs[4] = mlx_xpm_file_to_image(game->mlx,
			"xpm/enemy.xpm", &(game->st_heights[4]), &(game->st_widths[4]));
	game->col_second = mlx_xpm_file_to_image(game->mlx,
			"xpm/collect_1.xpm", &(game->st_heights[0]), &(game->st_widths[0]));
	return (0);
}

int	check_tile(t_game *game, char tile)
{
	if (tile == 'E')
	{
		if (game->collects)
			return (1);
		end(game);
	}
	else if (tile == 'C')
		game->collects -= 1;
	else if (tile == 'K')
		end(game);
	else if (tile == '1')
		return (1);
	return (0);
}

int	checkdest(int key, t_game *game)
{
	if (key == K_W)
	{
		if (!check_tile(game,
				game->map[game->player.pos.y - 1][game->player.pos.x]))
			return (1);
	}
	else if (key == K_A)
	{
		if (!check_tile(game,
				game->map[game->player.pos.y][game->player.pos.x - 1]))
			return (1);
	}
	else if (key == K_S)
	{
		if (!check_tile(game,
				game->map[game->player.pos.y + 1][game->player.pos.x]))
			return (1);
	}
	else if (key == K_D)
	{
		if (!check_tile(game,
				game->map[game->player.pos.y][game->player.pos.x + 1]))
			return (1);
	}
	return (key == K_ESC);
}

int	input(int key, t_game *game)
{
	if (!checkdest(key, game))
		return (1);
	if (key == K_W || key == K_A || key == K_S || key == K_D)
	{
		game->map[game->player.pos.y][game->player.pos.x] = '0';
		if (key == K_W)
			game->map[--game->player.pos.y][game->player.pos.x] = 'P';
		else if (key == K_A)
			game->map[game->player.pos.y][--game->player.pos.x] = 'P';
		else if (key == K_S)
			game->map[++game->player.pos.y][game->player.pos.x] = 'P';
		else if (key == K_D)
			game->map[game->player.pos.y][++game->player.pos.x] = 'P';
		printf("moves : %d\n", ++game->moves);
		render(game);
	}
	if (key == K_ESC)
		end(game);
	return (0);
}
