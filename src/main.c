#include "minishell.h"

void put_player(t_game *game)
{
	int i;
	int j;
	int box;

	box = game->player.hitbox;
	i = 0;
	j = 0;
	while(i < 8)
	{
		j = 0;
		while(j < 8)
		{
			mlx_pixel_put(game->mlx, game->win, (game->player.x - box), (game->player.y - box), 0x00FF0000);
			mlx_pixel_put(game->mlx, game->win, (game->player.x + box), (game->player.y + box), 0x00FF0000);
			mlx_pixel_put(game->mlx, game->win, (game->player.x - box), (game->player.y + box), 0x00FF0000);
			mlx_pixel_put(game->mlx, game->win, (game->player.x + box), (game->player.y - box), 0x00FF0000);
			j++;
		}
		i++;
	}
	mlx_pixel_put(game->mlx, game->win, (game->player.x), game->player.y, 0x000000FF);
}

void put_vision(t_game *game)
{
	int i;
	int box;

	box = game->player.hitbox;
	i = 0;
	while(i < 100)
	{
		mlx_pixel_put(game->mlx, game->win, (game->player.x), (game->player.y - box) - i, 0x00FF0000); // north x = 0, y = -1
		mlx_pixel_put(game->mlx, game->win, (game->player.x), (game->player.y + box) + i, 0x00FF0000); //sud dirX = 0 dirY = 1
		mlx_pixel_put(game->mlx, game->win, (game->player.x + box) + i, (game->player.y), 0x00FF0000); //east dirX = 1 dirY = 0
		mlx_pixel_put(game->mlx, game->win, (game->player.x - box) - i, (game->player.y), 0x00FF0000); //weast dirX = -1 dirY = 0
		i++;
	}
}

void	window_image_loop(t_game *game)
{
	int	j;
	int i;

	j = 0;
	i = 0;
	while (game->map && game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game -> map[i][j] == ' ')
				mlx_put_image_to_window(game->mlx, game-> win,
					game->model.north, j * 64, i * 64);
			if (game -> map[i][j] == '1')
				mlx_put_image_to_window(game->mlx, game-> win,
					game->model.sud, j * 64, i * 64);
			if (game -> map[i][j] == '0')
				mlx_put_image_to_window(game->mlx, game-> win,
					game->model.east, j * 64, i * 64);
			if (game -> map[i][j] == 'S')
				mlx_put_image_to_window(game->mlx, game-> win,
					game->model.east, j * 64, i * 64);
			j++;
		}
		i++;
	}
	put_player(game);
	put_vision(game);
}


void	check_hitbox(t_game *game, int x, int y )
{
	int box;

	box = game->player.hitbox;
	if (game->map[((game->player.y + box + y) / 64)] && game->map[((game->player.y + box + y) / 64)][(game->player.x + box + x) / 64] && game->map[((game->player.y + box + y) / 64)][(game->player.x + box + x) / 64] == '1') // bas droite
		return ;
	if (game->map[((game->player.y - box + y) / 64)] && game->map[((game->player.y - box + y) / 64)][(game->player.x + box + x) / 64] && game->map[((game->player.y - box + y) / 64)][(game->player.x + box + x)  / 64] == '1') // haut gauche
		return ;
	if (game->map[((game->player.y - box + y) / 64)] && game->map[((game->player.y - box + y) / 64)][(game->player.x - box + x) / 64] && game->map[((game->player.y - box + y) / 64)][(game->player.x - box + x) / 64] == '1') // bas droit
		return ;
	if (game->map[((game->player.y + box + y) / 64)] && game->map[((game->player.y + box +y) / 64)][(game->player.x - box + x) / 64] && game->map[((game->player.y + box + y) / 64)][(game->player.x - box + x) / 64] == '1') // bas gauche
		return ;
	game->player.y = game->player.y + y;
	game->player.x = game->player.x + x;
}


int	move_control(int keycode, t_game *game)
{
	if (keycode == 119)
		check_hitbox(game, 0, -game->player.speed);
	if (keycode == 100)
		check_hitbox(game, game->player.speed, 0);
	if (keycode == 97)
		check_hitbox(game, -game->player.speed, 0);
	if (keycode == 115)
		check_hitbox(game, 0, game->player.speed);
	if (keycode == 65307)
		mlx_loop_end(game->mlx);
	window_image_loop(game);
	return (0);
}

void start_game(t_game *game)
{

	game->win = mlx_new_window(game->mlx, 64*game->map_p.max_widht, 64*game->map_p.height, "Hello world!");
	window_image_loop(game);
	mlx_hook(game->win, 2, (1L<<0), move_control, game);
	mlx_loop(game->mlx);
}

int main(int argc, char **argv)
{
	t_game	game;

	argc--;
	argv++;
	set_game(&game);
	parsing_arg(argc, argv); // parse les arguments
	parsing(argv[0], &game); // creer les sprites
	//printf("x = %d / y =%d\n", game.player.x, game.player.y);
	start_game(&game);
	free_game_exit(&game, 1);
}