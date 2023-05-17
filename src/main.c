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

t_pic	*new_pic(t_game *img, int width, int height, int x)
{
	t_pic	*new;
	int		bpp;
	int		endian;

	bpp = 32;
	endian = 1;
	new = malloc(sizeof(t_pic));
	new->width = width;
	new->height = height;
	if (x == 1)
		new->img = mlx_xpm_file_to_image(img->mlx, img->sprite.north, \
		&new->width, &new->height);
	else if (x == 2)
		new->img = mlx_xpm_file_to_image(img->mlx, img->sprite.east, \
		&new->width, &new->height);
	else if (x == 3)
		new->img = mlx_xpm_file_to_image(img->mlx, img->sprite.west, \
		&new->width, &new->height);
	else if (x == 4)
		new->img = mlx_xpm_file_to_image(img->mlx, img->sprite.sud, \
		&new->width, &new->height);
	else
		new->img = mlx_new_image(img->mlx, width, height);
	new->buf = (int *)mlx_get_data_addr(new->img, &bpp, &x, &endian);
	return (new);
}
static int	put_texture(t_game *img, float start, int line)
{
	int		color;
	t_pic	*texture;
	double	x_text;
	double	x_wall;
	double	y_text;

	if (img->rayDirX > 0 && !img->side)
		texture = img->east;
	if (img->rayDirX < 0 && !img->side)
		texture = img->west;
	if (img->rayDirY < 0 && img->side)
		texture = img->north;
	if (img->rayDirY > 0 && img->side)
		texture = img->south;
	if (img->side == 0)
		x_wall = img->player.posx/64 + img->wall * img->rayDirY;
	else
		x_wall = img->player.posy/64 + img->wall * img->rayDirX;
	x_wall -= floor((x_wall));
	x_text = (int)(x_wall * (double)(64));
	if (img->side == 0 && img->rayDirX > 0)
		x_text = 64 - x_text - 1;
	if (img->side == 1 && img->rayDirY < 0)
		x_text = 64 - x_text - 1;
	color = start * 256 - img->screen.height * 128 + line * 128;
	y_text = ((color * 64) / line) / 256;
	color = texture->buf[(int)(y_text * 64 + x_text)];
	return (color);
}


void put_visionn(t_game *game)
{
	int i;
	int box;
	int w;
	double cameraX;
	int mapX;
    int mapY;
	double sideX;
    double sideY;
	double deltaDistY;
	double deltaDistX;
	double perpWallDist;
	int stepX;
    int stepY;
	int hit;
	int lineHeight;
	int drawStart;
	int drawEnd;

	box = game->player.hitbox;
	i = 0;
	game->pic = new_pic(game, game->screen.length , game->screen.height, 0);
	w =  game->screen.length;
	while(i < w)
	{
		cameraX = (2 * i) / (double) w - 1;
		game->rayDirX = game->player.diry + game->player.planey * cameraX;
		game->rayDirY = game->player.dirx + game->player.planex * cameraX;
		mapX = (int)game->player.y / 64;
		mapY = (int)game->player.x / 64;
		stepX = 1;
		stepY= 1;
		deltaDistX = fabs(1 / game->rayDirX);
		deltaDistY = fabs(1 / game->rayDirY);
		sideX = (mapX + 1.0 - game->player.posy/64) * deltaDistX ;
		sideY = (mapY + 1.0 - game->player.posx/64) * deltaDistY;
		hit = 0;
		if (game->rayDirX  < 0)
		{
			stepX = -1;
			sideX = (game->player.posy/64 - mapX ) * deltaDistX ;
		}
		if (game->rayDirY < 0)
		{
			stepY = -1;
			sideY = (game->player.posx/64 - mapY) * deltaDistY;
		}
		while(hit == 0)
      	{
			//jump to next map square, either in x-direction, or in y-direction
			//printf("sidex = %f  // sidey = %f", sideX, sideY);
			if(sideX < sideY)
			{
				sideX += deltaDistX;
				mapX += stepX;
				game->side = 0;
			}
			else
			{
				sideY += deltaDistY;
				mapY += stepY;
				game->side = 1;
        	}
			if (mapY < 0)
				mapY = 0;
			if (mapX < 0)
				mapX = 0;
			if(game->map[(mapY)][(mapX)] == '1')
				hit = 1;
		}
		//printf("mapx = %d // mapy = %d\n",mapX, mapY);
		if (!game->side)
		{
			//printf("0\n");
			game->wall = (mapX - game->player.posy/64 +  (1 - stepX) / 2) / game->rayDirX;
		}
		else
		{
			//printf("1\n");
			game->wall = (mapY - game->player.posx/64 + (1 - stepY) / 2) / game->rayDirY;
		}
		int line;
		int start;
		int end;
		int	color;
		//printf("wall = %f \n", game->wall);
		if (game->wall < 0)
			return ;
		line = (int)(game->screen.height/ game->wall);
		if (line > 200000)
			line = 200000;
		start = -line / 2 + game->screen.height / 2;
		if (start < 0)
			start = 0; 
		end = line / 2 + game->screen.height / 2;
		if (end >= game->screen.height)
			end = game->screen.height - 1;
		//printf("end = %d // start = %d\n", end ,start);
		if (game->side == 1)
    		color = 0x00CC3300; // Rouge
		if (game->side == 0)
			color = 0x00CC6666; // Rose
		//draw_ver_line(game, i ,0 , start,0x00CC9966);
		//printf("start = %d // end = %d\n", start, end);
		while (start < end)
		{
			game->pic->buf[(game->pic->width * start) + i] = put_texture(game, start, line);
			start++;
		}
		//draw_ver_line(game, i ,end  , game->screen.height  , 0x0033CCCC);
		//exit(1);
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->pic->img, 0, 0);
	mlx_destroy_image(game->mlx, game->pic->img);
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
	game->north = new_pic(game, 0, 0, 1);
	game->east = new_pic(game, 0, 0, 2);
	game->west = new_pic(game, 0, 0, 3);
	game->south = new_pic(game, 0, 0, 4);
	free_sprite_char(&game->sprite);
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