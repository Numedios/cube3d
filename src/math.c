/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 18:05:21 by sbelabba          #+#    #+#             */
/*   Updated: 2023/05/25 14:09:05 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_math(t_game *game, int i)
{
	game->camerax = (2 * i) / (double) game->screen.length - 1;
	game->raydirx = game->player.dirx + game->player.planex * game->camerax;
	game->raydiry = game->player.diry + game->player.planey * game->camerax;
	game->mapX = (int)game->x;
	game->mapY = (int)game->y;
	game->stepX = 1;
	game->stepY = 1;
	game->deltadistx = fabs(1 / game->raydirx);
	game->deltadisty = fabs(1 / game->raydiry);
	game->sidex = (game->mapX + 1.0 - game->x) * game->deltadistx ;
	game->sidey = (game->mapY + 1.0 - game->y) * game->deltadisty;
	if (game->raydirx < 0)
	{
		game->stepX = -1;
		game->sidex = (game->x - game->mapX) * game->deltadistx ;
	}
	if (game->raydiry < 0)
	{
		game->stepY = -1;
		game->sidey = (game->y - game->mapY) * game->deltadisty;
	}
}

int	check_hit(t_game *game)
{
	while (1)
	{
		if (game->sidex < game->sidey)
		{
			game->sidex += game->deltadistx;
			game->mapX += game->stepX;
			game->side = 0;
		}
		else
		{
			game->sidey += game->deltadisty;
			game->mapY += game->stepY;
			game->side = 1;
		}
		if (game->mapY < 0)
			game->mapY = 0;
		if (game->mapX < 0)
			game->mapX = 0;
		if (!game->map[game->mapY] || !game->map[game->mapY][game->mapX]
			|| game->map[game->mapY][game->mapX] == ' ')
			return (0);
		if (game->map[(game->mapY)][(game->mapX)] == '1')
			return (1);
	}
	return (0);
}

void	check_side(t_game *game)
{
	if (game->side == 0)
	{
		game->wall = (game->mapX - game->x + (1 - game->stepX) / 2)
			/ game->raydirx;
	}
	else
	{
		game->wall = (game->mapY - game->y + (1 - game->stepY) / 2)
			/ game->raydiry;
	}
	if (game->wall < 0)
		return ;
}

void	put_pic(t_game *game, int i)
{
	int	line;
	int	start;
	int	end;
	int	color;

	line = (int)(game->screen.height / game->wall);
	if (line > 200000)
		line = 200000;
	start = -line / 2 + game->screen.height / 2;
	if (start < 0)
		start = 0;
	end = line / 2 + game->screen.height / 2;
	if (end >= game->screen.height)
		end = game->screen.height - 1;
	while (start < end)
	{
		game->pic->buf[(game->pic->width * start) + i] = put_texture(game,
				start, line);
		start++;
	}
}

void	window_image_loop(t_game *game)
{
	int	i;

	i = 0;
	game->pic = new_pic(game, game->screen.length, game->screen.height, 0);
	get_on_the_floor(game);
	while (i < game->screen.length)
	{
		set_math(game, i);
		if (check_hit(game))
		{
			check_side(game);
			put_pic(game, i);
		}
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->pic->img, 0, 0);
	mlx_destroy_image(game->mlx, game->pic->img);
	free(game->pic);
}
