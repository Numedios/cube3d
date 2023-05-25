/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 18:46:36 by sbelabba          #+#    #+#             */
/*   Updated: 2023/05/25 17:47:29 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_wall_line(t_game *game, int j)
{
	int	last_line;

	last_line = 0;
	while (game->map[last_line])
		last_line++;
	last_line--;
	if (!game->map)
	{
		printf("ERROR : pas de map");
		free_game_exit(game, 1);
	}
	while (game->map[0] && game-> map[0][j])
	{
		if (game->map[0][j] != ' ' && game->map[last_line]
			&& game->map[0][j] != '1')
		{
			printf("ERROR : map premiere ligne pas composer uniquement de 1\n");
			free_game_exit(game, 1);
		}
		if (game->map[last_line][j] != ' ' && game->map[last_line][j] != '1')
		{
			printf("ERROR : map derniere ligne pas composer uniquement de 1\n");
			free_game_exit(game, 1);
		}
		j++;
	}
}

void	check_adjacent_2(int row, int col, t_game *game)
{
	if (game->map[row] && game->map[row][col + 1]
		&& comparerCaractere(game->map[row][col + 1], " 1\r", 3)) //game->map[row][col + 1] != '1' && game->map[row][col + 1] != ' ')
	{
		printf("ERROR : col + 1 map non fermer \n %s // *%c*\n", game->map[row],
			game->map[row][col + 1]);
		free_game_exit(game, 1);
	}
	if (col > 0 && game->map[row] && game->map[row][col - 1]
		&& comparerCaractere(game->map[row][col - 1], " 1\r", 3))// game->map[row][col - 1] != '1' && game->map[row][col - 1] != ' ')
	{
		printf("ERROR : col -1 map non fermer \n %s // *%c*\n", game->map[row],
			game->map[row][col - 1]);
		free_game_exit(game, 1);
	}
}

void	check_adjacent(int row, int col, t_game *game)
{
	if (game->map[row + 1] && game->map[row + 1][col]
		&& comparerCaractere(game->map[row + 1][col], " 1\r", 3)) //game->map[row + 1][col] != '1' && game->map[row + 1][col] != ' ')
	{
		printf("ERROR : row + 1 map non fermer \n %s // *%c*\n", game->map[row],
			game->map[row + 1][col]);
		free_game_exit(game, 1);
	}
	if (row > 0 && game->map[row - 1] && game->map[row - 1][col]
		&& comparerCaractere(game->map[row - 1][col], " 1\r", 3)) //game->map[row - 1][col] != '1' && game->map[row - 1][col] != ' ')
	{
		printf("ERROR : row - 1 map non fermer \n %s // *%c*\n", game->map[row],
			game->map[row - 1][col]);
		free_game_exit(game, 1);
	}
	check_adjacent_2(row, col, game);
}

int comparerCaractere(char c, const char* caracteres, int taille)
{
	int i;
	
	i = 0;
    while(i < taille)
	{
		if (c == caracteres[i])
			return (0);
		i++;
	}
	return (1);
}

void	check_adjacent_4(int row, int col, t_game *game)
{
	if (game->map[row] && game->map[row][col + 1]
		&& comparerCaractere(game->map[row][col + 1], "01EWSN", 6)) //game->map[row][col + 1] != '1' && game->map[row][col + 1] != '0' && game->map[row][col + 1] != 'E')
	{
		printf("ERROR : col + 1 map non fermer \n %s // *%c*\n", game->map[row],
			game->map[row][col + 1]);
		free_game_exit(game, 1);
	}
	if (col > 0 && game->map[row] && game->map[row][col - 1]
		&& comparerCaractere(game->map[row][col - 1], "01EWSN", 6)) // game->map[row][col - 1] != '1' && game->map[row][col - 1] != '0' && game->map[row][col - 1] != 'E')
	{
		printf("ERROR : col -1 map non fermer \n %s // *%c*\n", game->map[row],
			game->map[row][col - 1]);
		free_game_exit(game, 1);
	}
}

void	check_adjacent_3(int row, int col, t_game *game)
{
	if (game->map[row + 1] && game->map[row + 1][col]
		&& comparerCaractere(game->map[row + 1][col], "01EWSN", 6)) //game->map[row + 1][col] != '1' && game->map[row + 1][col] != '0' && game->map[row + 1][col] != 'E')
	{
		printf("ERROR : row + 1 map non fermer \n %s // *%c*\n", game->map[row],
			game->map[row + 1][col]);
		free_game_exit(game, 1);
	}
	if (row > 0 && game->map[row - 1] && game->map[row - 1][col]
		&& comparerCaractere(game->map[row - 1][col], "01EWSN", 6)) // game->map[row - 1][col] != '1' && game->map[row - 1][col] != '0' && game->map[row - 1][col] != 'E')
	{
		printf("ERROR : row - 1 map non fermer \n %s // *%c*\n", game->map[row],
			game->map[row - 1][col]);
		free_game_exit(game, 1);
	}
	check_adjacent_4(row, col, game);
}

void	check_wall_map(t_game *game)
{
	int	i;
	int	j;

	check_wall_line(game, 0);
	i = 0;
	while (game->map && game->map[i])
	{
		j = 0;
		while (game->map && game->map[i] && game->map[i][j])
		{
			if (game->map[i][j] == ' ')
				check_adjacent(i, j, game);
			if (game->map[i][j] == '0')
				check_adjacent_3(i, j, game);
			j++;
		}
		i++;
	}
}
