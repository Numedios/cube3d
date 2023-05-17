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
		printf("perpwall = %f\n", perpWallDist);
		printf("//posx = %f // posy = %f\n", game->player.posx/64,  game->player.posy/64); //test a faire ici
		int line = (int)(game->screen.height / game->wall);
		if (line > 200000)
		line = 200000;
		int start = -line / 2 + game->screen.height / 2;
		if (start < 0)
			start = 0; 
		int end = line / 2 + game->screen.height/ 2;
		if (end >= game->screen.height)
			end = game->screen.height - 1;
		printf("wall = %f // height = %d\n", game->wall, game->screen.height); //test a faire ici
		printf("end = %d // start = %d\n", end, start);
		exit (1);
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