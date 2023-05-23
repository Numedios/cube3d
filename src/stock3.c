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
		sideY = (mapX + 1.0 - game->player.posy/64) * deltaDistX ;
		sideX = (mapY + 1.0 - game->player.posx/64) * deltaDistY;
		hit = 0;
		if (game->rayDirX  < 0)
		{
			stepX = -1;
			sideY = (game->player.posy/64 - mapX ) * deltaDistX ;
			printf("ici 1\n");
		}
		if (game->rayDirY < 0)
		{
			stepY = -1;
			sideX = (game->player.posx/64 - mapY) * deltaDistY;
				printf("ici 2\n");
		}
		printf("2 sidex = %f  // sidey = %f\n", sideX, sideY);
		while(hit == 0)
      	{
			//jump to next map square, either in x-direction, or in y-direction
			if(sideX < sideY)
			{
				sideX += deltaDistY;
				mapX += stepX;
				game->side = 0;
				printf("1 sidex = %f  // sidey = %f\n", sideX, sideY);
				printf("1 mapx = %d // mapy = %d\n",mapX, mapY);
				//printf(" 0 sidex = %f  // sidey = %f\n", sideX, sideY);
			}
			else
			{
				sideY += deltaDistX;
				mapY += stepY;
				game->side = 1;
				printf("0 sidex = %f  // sidey = %f\n", sideX, sideY);
				printf("0 mapx = %d // mapy = %d\n",mapX, mapY);
	
				//printf("1  sidex = %f  // sidey = %f\n", sideX, sideY);
        	}
			if (mapY < 0)
				mapY = 0;
			if (mapX < 0)
				mapX = 0;
			if(game->map[(mapY)][(mapX)] == '1')
			{
				hit = 1;
			}
		}
		//if (mapX == 4 && mapY == 0 )
		//printf("mapx = %d // mapy = %d\n",mapX, mapY);
		if (game->side == 0)
		{
			//printf("0 ,  mapx = %d , mapy = %d\n", mapX, mapY);
			//printf("0 ,  x = %f , y = %f\n", game->player.posx/64 , game->player.posy/64);
			game->wall = (mapX - game->player.posy/64 +  (1 - stepX) / 2) / game->rayDirX;
			if (game->wall > 1.00)
			{
				//rintf("0 wall = %f \n", game->wall);
				//printf("0 rayx =%f\n",  game->rayDirX);
				//printf("0 stepX = %d \n", stepX);
				//printf("0 , y = %f\n", game->player.posy);
			//	printf("0 ,  mapx = %d \n", mapX);
			}
		}
		else
		{
			//printf("1 ,  mapx = %d , mapy = %d\n", mapX, mapY);
			//printf("1 ,  x = %f , y = %f\n", game->player.posx/64 , game->player.posy/64);
			game->wall = (mapY - (game->player.posx/64) + (1 - stepY) / 2) / game->rayDirY;
			if (game->wall > 1.00)
			{
				//printf("1 stepy = %d \n", stepY);
				//printf("1 wall = %f \n", game->wall);
				//printf("1rayy = %f\n",  game->rayDirY);
				//printf("1 ,  x = %f \n", game->player.posx);
				//printf("1 ,  mapx = %d , mapy = %d\n", mapX, mapY);
			}
		}
		int line;
		int start;
		int end;
		int	color;
		//printf("wall = %f \n", game->wall);
		if (game->wall < 0)
			return ;
		line = (int)(game->screen.height / game->wall);
		if (line > 200000)
			line = 200000;
		start = -line / 2 + game->screen.height / 2;
		if (start < 0)
			start = 0; 
		end = line / 2 + game->screen.height / 2;
		if (end >= game->screen.height)
			end = game->screen.height - 1;
		//printf("end = %d // start = %d\n", end ,start);
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