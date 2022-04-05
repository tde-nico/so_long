/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <tde-nico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 08:46:49 by tde-nico          #+#    #+#             */
/*   Updated: 2022/02/16 11:42:10 by tde-nico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	map_check(char *name)
{
	int	len;
	int	fd;

	len = ft_strlen(name);
	if (name[len - 4] != '.')
		return (0);
	if (name[len - 3] != 'b')
		return (0);
	if (name[len - 2] != 'e')
		return (0);
	if (name[len - 1] != 'r')
		return (0);
	fd = open(name, O_RDONLY);
	len = fd;
	close(fd);
	if (len == -1)
		return (0);
	return (1);
}

void	init_game(t_game *game)
{
	int	i;
	int	j;

	game->moves = 0;
	game->collects = 0;
	i = -1;
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
		{
			if (game->map[i][j] == 'P')
			{
				game->player.pos.x = j;
				game->player.pos.y = i;
			}
			else if (game->map[i][j] == 'C')
				game->collects += 1;
		}
	}
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2 || !map_check(argv[1]))
		return (raise(1) + 1);
	game.map = init_map(argv[1], &game);
	if (!game.map)
		return (1);
	init_game(&game);
	game.mlx = mlx_init();
	init_animations(&game);
	game.win_size.y++;
	game.win = mlx_new_window(game.mlx, game.win_size.x * IMG_SIZE,
			game.win_size.y * IMG_SIZE, "so_long");
	render(&game);
	mlx_hook(game.win, 2, 0, input, (void *)&game);
	mlx_hook(game.win, 17, 0, end, (void *)&game);
	game.loop = mlx_loop(game.mlx);
	return (0);
}
