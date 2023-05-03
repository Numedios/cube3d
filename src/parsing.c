#include "minishell.h"

void parsing(char *file, t_game *game)
{
	game->tab = create_tab(file); // get next line
	bad_char(game); // verifie aucun caractere chelou
	create_sprites(game); // rajoute la verification si sa depasse la taille d'un int
	init_mlx(game); // crer la mlx et set les model des texture
	parsing_map(game); // creation map
	free_tab((game->tab));
	free_sprite_char(&game->sprite);
	game->tab = NULL;
}