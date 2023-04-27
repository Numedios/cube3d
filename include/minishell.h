
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include "../mlx_linux/mlx.h"

typedef struct map_p
{
	int	start;
	int	height;
	int max_widht;

}			t_map_p;


typedef struct sprite
{
	char    *north;
	char    *sud;
	char 	*east;
	char	*west;
	char		*bot;
	char		*top;
}			t_sprite;


typedef struct s_game
{
	char **tab;
	char **map;
	t_sprite	sprite;
}		t_game;




/* get_next_line.c */

char	*get_next_line(int fd);

/* get_next_line.c */

int			check_end(char	*line);
char		*ft_strjoin_gnl(char *line, char *buf);
void		get_line(char *line, char *buf);
int			ft_strlen(char *str);

/* parsing_arg.c*/
void		ft_strstrend(char *str, char *search);
void		ft_try_open(char *file);
void		parsing_arg(int argc, char **argv);

/* free.c */

void		free_tab(char **tab);
void		free_sprite_char(t_sprite *sprite);
void		free_game_exit(t_game *game, int exit_code);

/* supp.c */

void    	print_tab(char **tab);

/* create_tab.c */

int			count_char(char *str);
int			open_fd(char *file);
int			count_ligne(char *str);
char		**create_tab(char *file);

/* set_struc.c */

void		set_sprite(t_sprite *sprite);

/* create_sprites.c */

char		*cut_split_sprite(char *line, t_game *game);
char		*split_sprite(char *line, char *dir, t_game *game);
int 		set_sprite_value(char *tab, char **sprite, char *dir, t_game *game);
void		create_sprites(t_game *game);

/* create_sprites_utils.c */

int			check_sprite(char *str, void *mlx);
int			check_all_sprite(t_game *game);
int			size_path(char *line);
int			ft_compstr(char *line, char *cmp);
int			check_dir(char *line, char *dir);


int			main(int argc, char **argv);


#endif