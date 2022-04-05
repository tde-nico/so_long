/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tde-nico <tde-nico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 09:26:55 by tde-nico          #+#    #+#             */
/*   Updated: 2022/02/16 08:57:00 by tde-nico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**alloc_columns(char *file)
{
	char	**map;
	int		lines;
	int		fd;
	int		bytes;
	char	buffer;

	fd = open(file, O_RDONLY);
	if (!fd)
		return (NULL);
	lines = 1;
	bytes = read(fd, &buffer, 1);
	while (bytes > 0)
	{
		if (buffer == '\n')
			lines++;
		bytes = read(fd, &buffer, 1);
	}
	close(fd);
	map = malloc(sizeof(char *) * lines);
	return (map);
}

int	readline(int fd, char **map)
{
	int		byte;
	char	buffer;
	int		chr;

	byte = 1;
	chr = 0;
	*map = malloc(1 * sizeof(char));
	(*map)[0] = '\0';
	while (byte)
	{
		byte = read(fd, &buffer, 1);
		if (buffer == '\n' || !byte)
		{
			if (!byte)
				free(*map);
			break ;
		}
		chr++;
		*map = ft_charjoin(*map, buffer);
	}
	return (chr);
}

int	is_wall_valid(char **map)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(map[0]);
	i = -1;
	while (map[++i])
	{
		if (ft_strlen(map[i]) != len)
			return (raise(3));
		if (map[i][len - 1] != '1' || map[i][0] != '1')
			return (raise(4));
	}
	while (--len > 0)
	{
		if (map[0][len] != '1')
			return (raise(5));
		if (map[i - 1][len] != '1')
			return (raise(6));
	}
	return (1);
}

int	is_map_valid(t_game *game)
{
	int	ij[2];
	int	pec[3];

	ij[0] = -1;
	pec[0] = 0;
	pec[1] = 0;
	pec[2] = 0;
	while (game->map[++ij[0]])
	{
		ij[1] = -1;
		while (game->map[ij[0]][++ij[1]])
		{
			if (!ft_strchr(MAPSET, game->map[ij[0]][ij[1]]))
				return (raise(2));
			pec[0] += (game->map[ij[0]][ij[1]] == 'P');
			pec[1] += (game->map[ij[0]][ij[1]] == 'E');
			pec[2] += (game->map[ij[0]][ij[1]] == 'C');
		}
		(game->win_size.y)++;
	}
	if (!is_wall_valid(game->map))
		return (0);
	game->win_size.x = ij[1];
	game->collects = pec[2];
	return (raise((pec[0] != 1) * 9) * raise(!pec[1] * 7) * raise(!pec[2] * 8));
}

char	**init_map(char *file, t_game *game)
{
	int	fd;
	int	i;

	game->map = alloc_columns(file);
	if (!game->map)
	{
		raise(10);
		return (NULL);
	}
	fd = open(file, O_RDONLY);
	i = -1;
	while (readline(fd, &(game->map[++i])))
		;
	game->map[i] = NULL;
	close(fd);
	game->win_size.y = 0;
	if (!is_map_valid(game))
	{
		free_map(game->map);
		return (NULL);
	}
	return (game->map);
}
