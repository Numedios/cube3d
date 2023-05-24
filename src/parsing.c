/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelabba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 19:14:12 by sbelabba          #+#    #+#             */
/*   Updated: 2023/05/24 19:14:13 by sbelabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_cord_player(t_game *game)
{
	game->player.x = (((game->player.x + 1) * 64)) - 32;
	game->player.y = (((game->player.y + 1) * 64)) - 32;
}

void	parsing(char *file, t_game *game)
{
	game->tab = create_tab(file);
	bad_char(game);
	create_sprites(game);
	init_mlx(game);
	parsing_map(game);
	change_cord_player(game);
	free_tab((game->tab));
	game->tab = NULL;
}
