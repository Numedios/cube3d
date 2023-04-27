#include "minishell.h"



int	start_line_map(t_game *game)
{
	int	i;
	int j;

	i = 0;
	
	while (game->tab && game->tab[i])
	{
		j = 0;
		while (game->tab && game->tab[i] && game->tab[i][j]  && game->tab[i][j] == ' ')
			j++;
		if (game->tab && game->tab[i] && game->tab[i][j]  && game->tab[i][j] == '1')
			return (i);
		i++;
	}
	return (-1);
}


int	start_height_map(t_game *game, t_map_p	map_p)
{
	int	i;
	int j;

	i = map_p.start;
	if (i == -1)
	{
		printf("Error : start_height");	
		free_game_exit(game, 1);
	}
	while (game->tab && game->tab[i])
	{
		j = 0;
		while (game->tab && game->tab[i] && game->tab[i][j]  && game->tab[i][j] == ' ')
			j++;
		if (game->tab && game->tab[i] && game->tab[i][j]  && game->tab[i][j] != '1')
			return (i - map_p.start);
		i++;
	}
	return (i - map_p.start);
}

void	set_map_p(t_map_p *map)
{
	map->height = -1;
	map->max_widht = -1;
	map->start = -1;
}

/* check si la map est en 1 block */

void	check_map_block(t_game *game, t_map_p	map_p)
{
	int	i;
	int j;

	i = map_p.start;
	if (i == -1)
	{
		printf("Error : start_height");	
		free_game_exit(game, 1);
	}
	while (game->tab && game->tab[i])
	{
		j = 0;
		while (game->tab && game->tab[i] && game->tab[i][j]  && game->tab[i][j] == ' ')
			j++;
		if (game->tab && game->tab[i] && game->tab[i][j]  && game->tab[i][j] != '1')
			break ;
		i++;
	}
	while (game->tab && game->tab[i])
	{
		j = 0;
		while (game->tab && game->tab[i] && game->tab[i][j]  && game->tab[i][j] == ' ')
			j++;
		if (game->tab && game->tab[i] && game->tab[i][j]  && game->tab[i][j] == '1')
		{
			printf("ERROR : map en plusieurs block\n");
			free_game_exit(game, 1);
		}
		i++;
	}

}
int	start_width_map(t_game *game, t_map_p map_p)
{
	int	i;
	int j;
	int c;
	int max;

	i = map_p.start;
	max = 0;
	if (i == -1)
	{
		printf("Error : start_width map"); // pas besoin maybe	
		free_game_exit(game, 1);
	}
	while (game->tab && game->tab[i])
	{
		j = 0;
		while (game->tab && game->tab[i] && game->tab[i][j])
		{
			if (game->tab[i][j] != ' ' && game->tab[i][j] != '\n' && game->tab[i][j] != '\r')
				c = j;
			j++;
		}
		if (c > max)
			max = c;
		i++;
	}
	return (max + 1);
}

void	create_map(t_game *game, t_map_p map_p)
{
	int	i;
	int j;
	int	k;

	k = 0;
	i = map_p.start;
	game->map = malloc(sizeof(char * ) * (map_p.height + 1));
	if (!game->map)
		free_game_exit(game, 1);
	while (game->tab && game->tab[i])
	{
		j = 0;
		game->map[k] = malloc(sizeof(char) * (map_p.max_widht + 1));
		if (!game->map[k])
			free_game_exit(game, 1);
		while (game->tab[i][j] && j < (map_p.max_widht) &&  game->tab[i][j] != '\n' && game->tab[i][j] != '\r')
		{
			game->map[k][j] = game->tab[i][j];
			j++;
		}
		while (j < (map_p.max_widht))
		{
			game->map[k][j] = ' ';
			j++;
		}
		game->map[k][j] = '\0';
		i++;
		k++;
	}
	game->map[k] = 0;

}

int	check_sep(char c, char *sep)
{
	int i;

	i = 0;
	while (sep && sep[i])
	{
		if (sep[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void check_char_map(t_game *game)
{
	int i;
	int j;

	i = 0;
	while (game->map && game->map[i])
	{
		j = 0;
		while (game->map[i] && game->map[i][j])
		{
			if (game->map[i][j] && !check_sep(game->map[i][j]," 10NSWE"))
			{
				printf("ERROR : Map L%d = %s // *%c*\n", i, game->map[i], game->map[i][j]);
				free_game_exit(game, 1);
			}
			j++;
		}
		i++;
	}
}

void check_wall_line(t_game *game)
{
	int j;

	j = 0;
	if (!game->map)
	{
		printf("ERROR : pas de map");
		free_game_exit(game, 1);
	}
	while (game->map[0] && game-> map[0][j])
	{
		if (game->map[0][j] != ' ' && game->map[0][j] != '1')
		{
			printf("ERROR : map premiere ligne pas composer uniquement de 1\n");
			free_game_exit(game, 1);
		}
		j++;
	}
}

void check_adjacent(int row, int col, t_game *game)
{
	if (game->map[row + 1] && game->map[row + 1][col] && game->map[row + 1][col] != '1' && game->map[row + 1][col] != ' ')
	{
		printf("ERROR : row + 1 map non fermer \n %s // *%c*\n", game->map[row], game->map[row + 1][col]);
		free_game_exit(game, 1);
	}
	if (game->map[row - 1] && game->map[row - 1][col] && game->map[row - 1][col] != '1' && game->map[row - 1][col] != ' ')
	{
		printf("ERROR : row - 1 map non fermer \n %s // *%c*\n", game->map[row], game->map[row - 1][col]);
		free_game_exit(game, 1);
	}
	if (game->map[row] && game->map[row][col + 1] && game->map[row][col + 1] != '1' && game->map[row][col + 1] != ' ')
	{
		printf("ERROR : col + 1 map non fermer \n %s // *%c*\n", game->map[row], game->map[row][col + 1]);
		free_game_exit(game, 1);
	}
	if (game->map[row] && game->map[row][col - 1] && game->map[row][col - 1] != '1' && game->map[row][col - 1] != ' ')
	{
		printf("ERROR : col -1 map non fermer \n %s // *%c*\n", game->map[row], game->map[row][col - 1]);
		free_game_exit(game, 1);
	}

}

void check_wall_map(t_game *game)
{
	int i;
	int j;

	check_wall_line(game);
	i = 1;
	while (game->map && game->map[i])
	{
		j = 0;
		while (game->map && game->map[i] && game->map[i][j])
		{
			if (game->map[i][j] == ' ')
				check_adjacent(i, j, game);
			j++;
		}
		i++;
	}
}

void	check_map(t_game *game)
{
	check_char_map(game);
	check_wall_map(game);
}


void	parsing_map(t_game *game)
{
	t_map_p	map_p;


	set_map_p(&map_p);
	map_p.start = start_line_map(game);
	check_map_block(game, map_p);
	map_p.height = start_height_map(game, map_p);
	map_p.max_widht = start_width_map(game, map_p);
	create_map(game, map_p);
	check_map(game);
}




void bad_char(t_game *game)
{
	int i;
	int	j;

	i = 0;
	while (game->tab && game->tab[i])
	{	
		j = 0;
		while (game->tab && game->tab[i] && game->tab[i][j]  && game->tab[i][j] == ' ')
		{
			j++;
		}
		if (!ft_compstr(game->tab[i] + j, "NO ") && !ft_compstr(game->tab[i] + j, "SO ") && !ft_compstr(game->tab[i] + j, "WE ") && !ft_compstr(game->tab[i] + j, "EA ") && !ft_compstr(game->tab[i] + j, "F ") &&   !ft_compstr(game->tab[i] + j, "C ") && !ft_compstr(game->tab[i] + j, "1") && (game->tab[i][j]) != '\r' && (game->tab[i][j]) != '\n')
		{
			printf("ERROR : L%d %s\n", i + 1, game->tab[i] + j);
			free_game_exit(game, 1);
		}
		i++;
	}
}


void parsing(char *file, t_game *game)
{
	game->tab = create_tab(file);
	bad_char(game);
	create_sprites(game);
	parsing_map(game); // finir sa
	free_tab((game->tab));
	game->tab = NULL;
}

int main(int argc, char **argv)
{
	t_game	game;

	argc--;
	argv++;
	parsing_arg(argc, argv); // parse les arguments
	parsing(argv[0], &game); // creer les sprites
	print_tab(game.map);
	//printf("no = %s\n", game.sprite.north);
	free_game_exit(&game, 1);
}