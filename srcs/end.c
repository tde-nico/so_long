/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <tde-nico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 08:59:28 by tde-nico          #+#    #+#             */
/*   Updated: 2022/02/17 08:07:25 by tde-nico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	raise(int err)
{
	if (err == 1)
		return (0 * printf("Error\n[!!] Need a valid <map.ber> as argument\n"));
	else if (err == 2)
		return (0 * printf("Error\n[!!] The map is not valid\n"));
	else if (err == 3)
		return (0 * printf("Error\n[!!] The map is not rectangular\n"));
	else if (err == 4)
		return (0 * printf("Error\n[!!] The map is not closed on side\n"));
	else if (err == 5)
		return (0 * printf("Error\n[!!] The map is not closed on top\n"));
	else if (err == 6)
		return (0 * printf("Error\n[!!] The map is not closed on bottom\n"));
	else if (err == 7)
		return (0 * printf("Error\n[!!] There is no Exit on the map\n"));
	else if (err == 8)
		return (0 * printf("Error\n[!!] There is no Collectible on the map\n"));
	else if (err == 9)
		return (0 * printf("Error\n[!!] You must have one Spawn on the map\n"));
	else if (err == 10)
		return (0 * printf("Error\n[!!] Error allocating memory\n"));
	return (1);
}

void	free_map(char **map)
{
	int	i;

	i = -1;
	while (map[++i])
		free(map[i]);
	free(map);
}

void	free_imgs(t_game *game)
{
	int	i;

	i = -1;
	while (++i < (int)(ft_strlen(MAPSET) - 1))
		mlx_destroy_image(game->mlx, game->st_imgs[i]);
	i = -1;
	while (++i < game->player.frame_count)
		mlx_destroy_image(game->mlx, game->player.frames[i]);
}

int	end(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	mlx_destroy_window(game->mlx, game->win);
	free_map(game->map);
	free_imgs(game);
	exit(0);
}

void	print(t_game *game, char c)
{
	int	i;
	int	j;

	i = -1;
	if (c == 'a' || c == 'm')
	{
		printf("map\n");
		while (++i < (game->win_size.y - 1))
		{
			j = -1;
			while (++j < game->win_size.x)
				printf(" %c", game->map[i][j]);
			printf("\n");
		}
	}
	if (c == 'a' || c == 'p')
		printf("player\n%d %d\n", game->player.pos.x, game->player.pos.y);
}
