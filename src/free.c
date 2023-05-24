
#include "minishell.h"

void	free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		i++;
	}
	if (tab)
		free(tab);
	tab = NULL;
}

void    free_sprite_char(t_sprite *sprite)
{
	if (sprite->north)
		free(sprite->north);
	sprite->north = NULL;
	if (sprite->sud)
		free(sprite->sud);
	sprite->sud = NULL;
	if (sprite->east)
		free(sprite->east);
	sprite->east = NULL; 
	if (sprite->west)
		free(sprite->west);
	sprite->west = NULL; 
	if (sprite->bot)
		free(sprite->bot);
	sprite->bot = NULL; 
	if (sprite->top)
		free(sprite->top);
	sprite->top = NULL; 
}


void    free_pic(t_game *game)
{
	mlx_destroy_image(game->mlx, game->north->img);
	mlx_destroy_image(game->mlx, game->east->img);
	mlx_destroy_image(game->mlx, game->west->img);
	mlx_destroy_image(game->mlx, game->south->img);
	free(game->north);
	free(game->east);
	free(game->west);
	free(game->south);
}

void free_game_exit(t_game *game, int exit_code)
{
	if (game->tab)
		free_tab(game->tab);
	game->tab = NULL;
	
	if (game->map)
		free_tab(game->map);
	game->map = NULL;
	free_sprite_char(&game->sprite);
	free_pic(game);
	if (game->win)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
	
	exit(exit_code);
}