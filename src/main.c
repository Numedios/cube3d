#include "minishell.h"

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
	if (map_p.start < 0)
	{
		printf("ERROR : map introuvable\n");
		free_game_exit(game, 1);
	}
	check_map_block(game, map_p);
	map_p.height = start_height_map(game, map_p);
	if (map_p.height <= 0)
	{
		printf("ERROR : map pas assez haute\n");
		free_game_exit(game, 1);
	}
	map_p.max_widht = start_width_map(game, map_p);
	if (map_p.max_widht <= 0)
	{
		printf("ERROR : map pas assez longue \n");
		free_game_exit(game, 1);
	}
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

void	*create_sprite(char *str, t_game *game) // rajouter game et tout free
{
	void	*img;
	int		img_width;
	int		img_height;

	img = mlx_xpm_file_to_image(game->mlx, str,
			&img_width, &img_height);
	if (!img)
		free_game_exit(game, 1);
	return (img);
}

void	add_model(t_game *game)
{
	game->model.north = create_sprite(game->sprite.north ,game);
	game->model.sud =  create_sprite(game->sprite.sud ,game);
	game->model.east =  create_sprite(game->sprite.east ,game);
	game->model.west =  create_sprite(game->sprite.west ,game);
}


void init_mlx(t_game *game)
{

	game->mlx = mlx_init();
	if (!game->mlx)
		free_game_exit(game, 1);
	add_model(game);
}


void parsing(char *file, t_game *game)
{
	game->tab = create_tab(file); // get next line
	bad_char(game); // verifie aucun caractere chelou
	create_sprites(game); // verier F et C
	init_mlx(game); // crer la mlx et set les model des texture
	parsing_map(game); // creation map
	free_tab((game->tab));
	free_sprite_char(&game->sprite);
	game->tab = NULL;
}

void set_game(t_game *game)
{
	game->tab = NULL;
	game->map = NULL;
}

int main(int argc, char **argv)
{
	t_game	game;

	argc--;
	argv++;
	set_game(&game);
	parsing_arg(argc, argv); // parse les arguments
	parsing(argv[0], &game); // creer les sprites
	free_game_exit(&game, 1);
}