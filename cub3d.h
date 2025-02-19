/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:20:14 by vlaggoun          #+#    #+#             */
/*   Updated: 2025/02/19 18:21:25 by vlaggoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./getnextline/ft_printf.h"
# include "./getnextline/get_next_line.h"
# include "./getnextline/libft.h"
// # include "mlx/mlx.h"
// # include "mlx/mlx_int.h"
// # include <X11/X.h>
// # include <X11/keysym.h>
// # include <X11/keysymdef.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <stdbool.h>

# define B_RED "\001\033[1;31m\002"
# define BG_GREEN "\001\033[42m\002"
# define BHI_WHITE "\001\033[1;97m\002"
# define RESET "\001\033[0m\002"


// FREE ARRAY !! DON'T BE DUMB
typedef union u_colors
{
	unsigned char rgb[3];
	unsigned int	color;
}	u_colors;

typedef struct s_list
{
	void			*data;
	struct s_list	*next;

}		t_list;

enum	e_object
{
	WALL,
	FLOOR,
	VOID,
	//DOOR ?
};

//structu Union for colors

typedef struct s_map
{
	int				fd;
	unsigned int	width;
	unsigned int	height;
	char 			**map_copy;
	char			**parse_map;
	int			one_time;

}		t_map;

typedef struct s_texture
{
	char	**floor;
	char 	**ceiling;
	void	*door;
	char	*north;
	char	*south;
	char	*east;
	char	*west;
}		t_texture;

typedef struct	t_list
{
	t_map	map;
	t_texture	texture;
	u_colors	color_fl;
	u_colors	color_ce;
	int			player;
	// void	*winmlx;
	// void	*ptrmlx;
}		t_game;


// ***********************************
// *             PARSING             *
// ***********************************

int		is_cub(char *argv, char *find);
void	init_map(t_game *game);
void	read_map(char **argv, t_game *game);
void	read_map_2(t_game *game, t_list *node, t_list *new);
int		parse(t_game *game);
char	*verify_identifiers(char **s1, char *s2, int map);
bool	is_space(char c);
int		compare_identifiers(char *s1, char *s2, int map);
char	*recover_path(char *str);
int		verify_textures(t_game *game);
int		open_textures(t_game *game);
int		check_comma(char *str);
char 	*recover_colors(char *str);
char	**verify_rgb(char **s1, char *s2, int map);
int		overflow(unsigned char **tab);
void	colors_in_structure(t_game *game, unsigned char **floor, unsigned char **ceiling);
int		verify_colors(t_game *game);
int		overflow(unsigned char **tab);
void	colors_in_structure(t_game *game, unsigned char **floor, unsigned char **ceiling);
int		check_map(char *str);
int		longest_line(char **str);
char 	*fill_with_space(char *str, t_game *game);
int		copy_map(char **str, t_game *game);
int		verify_map_copy(char **s1, char *s2, int map, t_game *game);
int		nbr_player(char **str, t_game *game);
int		check_position(char **map, int y, int x, t_game *game);
int		surrounded_walls(char **map, t_game *game);
int		verify_map(t_game *game);
int		check_differents_identifiers(t_game *game);

// ***********************************
// *             SIZE                *
// ***********************************

void	linkedlist_map(t_list *head, t_game *game);
char	*ft_strdup(const char *src);
void	verify_size_map(t_list *head, t_game *game);
void	check_size_map(t_list *head, int width, t_game *game);
size_t	map_len(char *str);
int	get_size_map(t_game *game);


// ***********************************
// *             FREE                *
// ***********************************

void	free_linked_list(t_list **lst);
void	free_array(t_game *game);
void	free_array_map(t_game *game);

// ***********************************
// *          LINKED LIST            *
// ***********************************

t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	free_array_floor(t_game *game);
void	free_array_ceiling(t_game *game);

// ***********************************
// *             OTHERS              *
// ***********************************

int	error_msg(char *str);


# endif
