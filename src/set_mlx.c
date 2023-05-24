#include "minishell.h"

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



void init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		free_game_exit(game, 1);
}