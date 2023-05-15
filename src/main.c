#include "minishell.h"

void drawVerticalLine(int x, int drawStart, int drawEnd, int color, t_game *game)
{
    int y = drawStart;
    while (y <= drawEnd)
    {
        mlx_pixel_put(game->mlx, game->win, x, y, color);
        y++;
    }
}

void draw_line(int x1, int y1, int x2, int y2, t_game *game)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = dx - dy;
    
    while (x1 != x2 || y1 != y2) {
        mlx_pixel_put(game->mlx, game->win, y1, x1,  0x000000FF);
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

void draw_ver_line(t_game *game, int x, int y_start, int y_end, int color)
{
    int y;

    for (y = y_start; y <= y_end; y++)
    {
        mlx_pixel_put(game->mlx, game->win, x, y, color);
    }
}


void put_visionn(t_game *game)
{
	int i;
	int box;
	int w;
	double cameraX;
	double rayDirX;
	double rayDirY;
	int mapX;
    int mapY;
	double sideDistX;
    double sideDistY;
	double deltaDistY;
	double deltaDistX;
	double perpWallDist;
	int stepX;
    int stepY;
	int hit;
	int side;
	int lineHeight;
	int drawStart;
	int drawEnd;

	box = game->player.hitbox;
	i = 0;
	w =  game->screen.length;
	while(i < w)
	{
		cameraX = (2 * i) / (double) w - 1;
		rayDirX = game->player.dirx + game->player.planex * cameraX;
		rayDirY = game->player.diry + game->player.planey * cameraX;
		mapX = (int)game->player.posx ;
		mapY = (int)game->player.posy;

		if (rayDirX == 0)
		{
    		deltaDistX = 1e30;
		}
		else
		{
    		deltaDistX = fabs(1 / rayDirX);
		}
		if (rayDirY == 0)
		{
    		deltaDistY = 1e30;
		}
		else
		{
   			deltaDistY = fabs(1 / rayDirY);
		}

		hit = 0;

		if(rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (game->player.posx - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - game->player.posx ) * deltaDistX;
		}
		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (game->player.posy - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - game->player.posy) * deltaDistY;
		}
		while(hit == 0)
      	{
			//jump to next map square, either in x-direction, or in y-direction
			if(sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
        	}
			if(game->map[(mapX)/64][(mapY)/64] == '1')
			{
				//printf("mapx = %d // mapy = %d\n", (mapX)%64, (mapY)%64);
				//draw_line((int)game->player.posx, (int)game->player.posy , mapX , mapY, game);
				hit = 1;
			}

		}
		if(side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);
		lineHeight = (int)(game->screen.height / perpWallDist);
		drawStart = -lineHeight / 2 + game->screen.height / 2;
		if(drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + game->screen.height / 2;
		if(drawEnd >= (game->screen.height))
			drawEnd = (game->screen.height) - 1;

		if(side == 0)
			game->wall = game->player.posy + perpWallDist * rayDirY;
      	else
			game->wall = game->player.posx + perpWallDist * rayDirX;


		int line = (int)(game->screen.height / game->wall);
		if (line > 200000)
		line = 200000;
		int start = -line / 2 + game->screen.height / 2;
		if (start < 0)
			start = 0; 
		int end = line / 2 + game->screen.height/ 2;
		if (end >= game->screen.height)
			end = game->screen.height - 1;
		/*printf("wall = %f // height = %d\n", game->wall, game->screen.height); //test a faire ici
		printf("end = %d // start = %d\n", end, start);
			exit (1);*/
		/*while (start < end)
		{
			game->buf[(game->pic->width * start) + i] \
			= put_texture(img, start, line, img->south);
			start++;
		}*/


		int pitch = 100;
		int color;

		if (mapY % 64 == 0 && mapX % 64 >= 0 && mapX % 64<= 63 && side == 1)
    		color = 0x00CC3300; // Rouge
		else if (mapX % 64 == 63 && mapY % 64 >= 0 && mapY  % 64<= 63 && side == 0)
			color = 0x000000CC; // Bleu
		else if (mapY % 64 == 63 && mapX % 64 >= 0 && mapX % 64<= 63 && side == 1)
			color = 0x0000FF99; // Vert
		else if (mapX % 64 == 0 && mapY % 64 >= 0 && mapY % 64 <= 63 && side == 0)
			color = 0x00CC6666; // Rose
		else
			color = 0x00000033; // Noir
		draw_ver_line(game, i ,0 , drawStart -40,0x00CC9966);
		draw_ver_line(game, i ,drawStart -40 , drawEnd + 40,color);
		draw_ver_line(game, i ,drawEnd + 40 , game->screen.height  , 0x0033CCCC);
		i++;
	}

}


void	window_image_loop(t_game *game)
{
	put_visionn(game);
}


int	check_hitbox_down(t_game *game)
{
	int box;
	int x;
	int y;

	y = (int) game->player.posy - (game->player.diry * 1);
	x = (int) game->player.posx - (game->player.dirx * 1);
	box = game->player.hitbox;
	if (game->map[((x) / 64)] && game->map[((x) / 64)][(y) / 64] && game->map[((x) / 64)][(y) / 64] == '1') // bas droite
		return (0);
	return (1);
}

int	check_hitbox_up(t_game *game)
{
	int box;
	int x;
	int y;

	x = (int) game->player.posx + (game->player.dirx * 1);
	y = (int) game->player.posy + (game->player.diry * 1);
	box = game->player.hitbox;
	if (game->map[((x) / 64)] && game->map[((x) / 64)][(y ) / 64] && game->map[((x) / 64)][(y) / 64] == '1') // bas droite
		return (0);
	return (1);
}

int	move_control(t_game *game)
{
	double oldirx;
	double oldPlanex;
	int keycode;

	keycode = game->key;
	oldPlanex = game->player.planex;
	oldirx = game->player.dirx;
	if (keycode == 119 || keycode == 122)
	{
		//printf("haut\n");
		if (check_hitbox_up(game))
		{
			game->player.posy = game->player.posy + (game->player.diry * 1);
			game->player.posx = game->player.posx + (game->player.dirx * 1);
		}
	}
	if (keycode == 100)
	{
		//printf("droite\n");
		game->player.dirx = game->player.dirx * cos(-(0.2)) - game->player.diry * sin(-(0.2));
     	game->player.diry = oldirx * sin(-(0.2)) + game->player.diry * cos(-(0.2));

		game->player.planex = game->player.planex * cos(-0.2) - game->player.planey * sin(-0.2);
		game->player.planey = oldPlanex * sin(-0.2) + game->player.planey * cos(-0.2);
	}
	if (keycode == 97 || keycode == 113)
	{
		//printf("gauche\n");

		game->player.dirx = game->player.dirx * cos((0.2)) - game->player.diry * sin((0.2));
     	game->player.diry = oldirx * sin(0.2) + game->player.diry * cos((0.2));

		game->player.planex = game->player.planex * cos(0.2) - game->player.planey * sin(0.2);
		game->player.planey = oldPlanex * sin(0.2) + game->player.planey * cos(0.2);
	}
	
	if (keycode == 115)
	{
		//printf("bas\n");
		if (check_hitbox_down(game))
		{
			game->player.posy = game->player.posy - (game->player.diry * 1);
			game->player.posx = game->player.posx - (game->player.dirx * 1);
		}
	}
	if (keycode == 65307)
		mlx_loop_end(game->mlx);
	window_image_loop(game);
	return (0);
}


void set_dir_start(t_game *game)
{
	if (game->map[game->player.x] && game->map[game->player.x][game->player.y] == 'W')
	{
		game->player.dirx = 0;
		game->player.diry = -1;
	}
	if (game->map[game->player.x] && game->map[game->player.x][game->player.y] == 'E')
	{
		game->player.dirx = 0;
		game->player.diry = 1;
	}
	if (game->map[game->player.x] && game->map[game->player.x][game->player.y] == 'S')
	{
		game->player.dirx = 1;
		game->player.diry = 0;
		game->player.planey = -0.66;
    	game->player.planex = 0;
	}
	if (game->map[game->player.x] && game->map[game->player.x][game->player.y] == 'N')
	{
		game->player.dirx = -1;
		game->player.diry = 0;
	}
	if(game->player.dirx > 0)
	{
    	game->player.planey = -0.66;
    	game->player.planex = 0;
	}
	else if(game->player.dirx < 0)
	{
    	game->player.planey = 0.66;
    	game->player.planex = 0;
	}
	else if(game->player.diry > 0)
	{
    	game->player.planex = 0.66;
    	game->player.planey = 0;
	}
	else if(game->player.diry < 0)
	{
    	game->player.planex = -0.66;
    	game->player.planey = 0;
	}
}

void set_vecteur_start(t_game *game)
{
	game->player.posx = (double) game->player.x;
	game->player.posy = (double) game->player.y;
}

void set_screen(t_game *game)
{
	game->screen.height = 720;
	game->screen.length = 1480;
}
static int	press(int keycode, t_game *game)
{
	game->key = 0;
	game->key = keycode;
	return (0);
}

static int	release(int keycode, t_game *game)
{
	(void)keycode;
	game->key = 0;
	return (0);
}

int free_game_exite(t_game *game)
{
	if (game->tab)
		free_tab(game->tab);
	game->tab = NULL;
	
	if (game->map)
		free_tab(game->map);
	game->map = NULL;
	free_sprite_char(&game->sprite);
	free_model(&game->model, game->mlx);
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
	
	exit(1);
}


void start_game(t_game *game)
{
	game->key = 0;
	set_vecteur_start(game);
	set_screen(game);
	game->win = mlx_new_window(game->mlx, game->screen.length, game->screen.height , "Hello world!");
	window_image_loop(game);
	mlx_hook(game->win, 2, 1L << 0, &press, game);
	mlx_hook(game->win, 3, 1L << 1, &release, game);
	mlx_hook(game->win, 17, 0, free_game_exite, game);
	mlx_loop_hook(game->mlx, &move_control, game);
	//mlx_hook(game->win, 2, (1L<<0), move_control, game);
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