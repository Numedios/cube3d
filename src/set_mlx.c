/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelabba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 19:38:05 by sbelabba          #+#    #+#             */
/*   Updated: 2023/05/24 19:38:06 by sbelabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*create_sprite(char *str, t_game *game)
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

void	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		free_game_exit(game, 1);
}
