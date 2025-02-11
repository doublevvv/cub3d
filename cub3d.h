/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlaggoun <vlaggoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:20:14 by vlaggoun          #+#    #+#             */
/*   Updated: 2025/02/11 16:35:26 by vlaggoun         ###   ########.fr       */
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
int		verify_textures(t_game *game);
int		verify_colors(t_game *game);
int		overflow(unsigned char **tab);
void	colors_in_structure(t_game *game, unsigned char **floor, unsigned char **ceiling);
// void	parsing_map(t_game *game);
int		verify_map(t_game *game);
int	everything_filled(t_game *game);
// void	check_x_walls(t_game *game);
// void	check_y_walls(t_game *game);

// ***********************************
// *             SIZE                *
// ***********************************

void	get_size_map(t_list *head, t_game *game);
char	*ft_strdup(const char *src);
void	verify_size_map(t_list *head, t_game *game);
void	check_size_map(t_list *head, int width, t_game *game);
size_t	map_len(char *str);


// ***********************************
// *             FREE                *
// ***********************************

void	free_linked_list(t_list **lst);
void	free_array(t_game *game);

// ***********************************
// *          LINKED LIST            *
// ***********************************

t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);

// ***********************************
// *             OTHERS              *
// ***********************************

int	error_msg(char *str);


# endif
