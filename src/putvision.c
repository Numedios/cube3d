/*
void put_vision(t_game *game)
{
	int i;
	int box;
	int w;
	double camerax;
	double raydirx;
	double raydiry;
	int mapX;
    int mapY;
	double sideDistX;
    double sideDistY;
	double deltadisty;
	double deltadistx;
	double perpwalldist;
	int stepX;
    int stepY;
	int hit;
	int side;
	int lineHeight;
	int drawStart;
	int drawEnd;

	box = game->player.hitbox;
	i = 0;
	w = 64 * game->map_p.max_widht;
	while(i < w)
	{
		camerax = 2 * i / (double)w - 1;
		raydirx = game->player.dirx + game->player.planex * camerax;
		raydiry = game->player.diry + game->player.planey * camerax;

		mapX = (int)game->player.posy;
		mapY = (int)game->;

		deltadistx = (raydirx == 0) ? 1e30 : fabs(1 / raydirx);
		deltadisty = (raydiry == 0) ? 1e30 : fabs(1 / raydiry);

		hit = 0;

		if(raydirx < 0)
		{
			stepX = -1;
			sideDistX = (game->player.posx - mapX) * deltadistx;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - game->player.posx ) * deltadistx;
		}
		if(raydiry < 0)
		{
			stepY = -1;
			sideDistY = (game->player.posy - mapY) * deltadisty;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - game->player.posy) * deltadisty;
		}
		while(hit == 0)
      	{
			//jump to next map square, either in x-direction, or in y-direction
			if(sideDistX < sideDistY)
			{
				sideDistX += deltadistx;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltadisty;
				mapY += stepY;
				side = 1;
        	}
			mlx_pixel_put(game->mlx, game->win, (game->player.posx + (game->player.dirx * i)), (game->player.posy + (game->player.diry  * i)), 0x00FF0000);
			if(game->map[(mapX)/64][(mapY)/64] == '1')
			{
				hit = 1;
				break
			}

		}
		if(side == 0)
			perpwalldist = (sideDistX - deltadistx);
		else
			perpwalldist = (sideDistY - deltadisty);
		lineHeight = (int)(game->map_p.height / perpwalldist);
		drawStart = -lineHeight / 2 + game->map_p.height / 2;
		if(drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + game->map_p.height / 2;
		if(drawEnd >= game->map_p.height)
			drawEnd = game->map_p.height - 1;
		i++;
	}

}*/
/*
void put_visionn(t_game *game)
{
	int w;

	w = 64*game->map_p.max_widht;
    for(int x = 0; x < w; x++)
    {
      //calculate ray position and direction
      double camerax = 2 * x / (double)w - 1; //x-coordinate in camera space
      double raydirx = game->player.dirx + game->player.planex * camerax;
      double raydiry = game->player.diry + game->player.planey * camerax;
      //which box of the map we're in
      int mapX = (int) (game->player.posx);
      int mapY = (int) (game->player.posx);

      //length of ray from current position to next x or y-side
      double sideDistX;
      double sideDistY;

      //length of ray from one x or y-side to next x or y-side
      //these are derived as:
      //deltadistx = sqrt(1 + (raydiry * raydiry) / (raydirx * raydirx))
      //deltadisty = sqrt(1 + (raydirx * raydirx) / (raydiry * raydiry))
      //which can be simplified to abs(|rayDir| / raydirx) and abs(|rayDir| / raydiry)
      //where |rayDir| is the length of the vector (raydirx, raydiry). Its length,
      //unlike (dirX, dirY) is not 1, however this does not matter, only the
      //ratio between deltadistx and deltadisty matters, due to the way the DDA
      //stepping further below works. So the values can be computed as below.
      // Division through zero is prevented, even though technically that's not
      // needed in C++ with IEEE 754 floating point values.
      double deltadistx = (raydirx == 0) ? 1e30 : fabs(1 / raydirx);
      double deltadisty = (raydiry == 0) ? 1e30 : fabs(1 / raydiry);

      double perpwalldist;

      //what direction to step in x or y-direction (either +1 or -1)
      int stepX;
      int stepY;

      int hit = 0; //was there a wall hit?
      int side; //was a NS or a EW wall hit?
      //calculate step and initial sideDist
      if(raydirx < 0)
      {
        stepX = -1;
        sideDistX = (game->player.posx - mapX) * deltadistx;
      }
      else
      {
        stepX = 1;
        sideDistX = (mapX + 1.0 - game->player.posx) * deltadistx;
      }
      if(raydiry < 0)
      {
        stepY = -1;
        sideDistY = (game->player.posy - mapY) * deltadisty;
      }
      else
      {
        stepY = 1;
        sideDistY = (mapY + 1.0 - game->player.posy) * deltadisty;
      }
      //perform DDA
      while(hit == 0)
      {
        //jump to next map square, either in x-direction, or in y-direction
        if(sideDistX < sideDistY)
        {
          sideDistX += deltadistx;
          mapX += stepX;
          side = 0;
        }
        else
        {
          sideDistY += deltadisty;
          mapY += stepY;
          side = 1;
        }
        //Check if ray has hit a wall
        if(game->map[mapY][mapX] > 0) hit = 1;
      }
      //Calculate distance projected on camera direction. This is the shortest distance from the point where the wall is
      //hit to the camera plane. Euclidean to center camera point would give fisheye effect!
      //This can be computed as (mapX - posX + (1 - stepX) / 2) / raydirx for side == 0, or same formula with Y
      //for size == 1, but can be simplified to the code below thanks to how sideDist and deltaDist are computed:
      //because they were left scaled to |rayDir|. sideDist is the entire length of the ray above after the multiple
      //steps, but we subtract deltaDist once because one step more into the wall was taken above.
      if(side == 0) perpwalldist = (sideDistX - deltadistx);
      else          perpwalldist = (sideDistY - deltadisty);

      //Calculate height of line to draw on screen
      int lineHeight = (int)(64*game->map_p.height / perpwalldist);

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + 64*game->map_p.height / 2;
      if(drawStart < 0) drawStart = 0;
      int drawEnd = lineHeight / 2 + 64*game->map_p.height / 2;
      if(drawEnd >= 64*game->map_p.height) drawEnd = 64*game->map_p.height - 1;


      //draw the pixels of the stripe as a vertical line
     	print_trait(x, drawStart, drawEnd, game);
	}
}*/