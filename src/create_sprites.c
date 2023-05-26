/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhamdouc <zhamdouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 19:00:58 by sbelabba          #+#    #+#             */
/*   Updated: 2023/05/25 13:46:25 by zhamdouc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_sprite_value(char *tab, char **sprite, char *dir, t_game *game)
{
	if (check_dir(tab, dir))
	{
		if (!(*sprite))
		{
			*sprite = split_sprite(tab, dir, game);
			return (0);
		}
		else
		{
			printf("Error: sprite %s already exists.\n", dir);
			free_game_exit(game, 1);
		}
	}
	return (0);
}

int	ft_isdigit(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str && str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

void	check_virgule(t_game *game, char *num)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (num && num[i])
	{
		if (num && num[i] && num[i] == ',')
			c++;
		i++;
	}
	if (c != 2)
	{
		printf("Error : \"%s\" %d virgule au lieu de 2 \n", num, c);
		free_game_exit(game, 1);
	}
}

void	check_color_sprite_2(t_game *game, int *set, int i, char **pos)
{
	while (pos && pos[i])
	{
		set[i] = ft_atoi(pos[i]);
		if (set[i] && (set[i] < 0 || set[i] > 255))
		{
			printf("Error : couleur %d pqs compris entre 0 et 255\n", set[i]);
			if (pos)
				free_tab(pos);
			free_game_exit(game, 1);
		}
		i++;
	}
}

void	check_color_sprite_3(t_game *game, int *set, int i, char **pos)
{
	while (pos && pos[i])
	{
		if (ft_isdigit(pos[i]) == 0)
		{
			printf("Error : couleur %s n'est pas un nombre\n", pos[i]);
			if (pos)
				free_tab(pos);
			free_game_exit(game, 1);
		}
		i++;
	}
}

void	check_color_sprite(t_game *game, char *num, int *set)
{
	char	**pos;

	if (num)
	{
		check_virgule(game, num);
		pos = ft_split(num, ',');
	}
	if (!pos || ft_strlen_tab(pos) != 3)
	{
		if (pos)
			free_tab(pos);
		printf("Error : \"%s\" plus de 3 couleur (R,G,B)\n", num);
		free_game_exit(game, 1);
	}
	check_color_sprite_2(game, set, 0, pos);
	check_color_sprite_3(game, set, 0, pos);
	if (pos)
		free_tab(pos);
}

void	check_colors(t_game *game)
{
	check_color_sprite(game, game->sprite.bot, game->model.bot);
	check_color_sprite(game, game->sprite.top, game->model.top);
}

void	create_sprites(t_game *game)
{
	int			i;

	i = 0;
	while (game->tab && game->tab[i])
	{
		set_sprite_value(game->tab[i], &game->sprite.north, "NO", game);
		set_sprite_value(game->tab[i], &game->sprite.sud, "SO", game);
		set_sprite_value(game->tab[i], &game->sprite.east, "EA", game);
		set_sprite_value(game->tab[i], &game->sprite.west, "WE", game);
		set_sprite_value(game->tab[i], &game->sprite.bot, "F", game);
		set_sprite_value(game->tab[i], &game->sprite.top, "C", game);
		i++;
	}
	check_all_sprite(game);
	check_colors(game);
}
