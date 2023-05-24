#include "minishell.h"

void set_sprite(t_sprite *sprite)
{
	sprite->north = NULL;
	sprite->sud = NULL;
	sprite->east = NULL;
	sprite->west = NULL;
	sprite->bot = NULL;
	sprite->top = NULL;
}



void set_game(t_game *game)
{
	game->tab = NULL;
	game->map = NULL;
	game->mlx = NULL;
	game->win = NULL;
	game->player.speed = 5;
	game->player.hitbox = 4;
	set_sprite(&game->sprite);
}