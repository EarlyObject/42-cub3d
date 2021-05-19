/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 16:44:32 by asydykna          #+#    #+#             */
/*   Updated: 2021/05/16 15:22:55 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFS_H
# define DEFS_H

# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdlib.h>
# include <fcntl.h>
# include <SDL2/SDL.h>
# include <limits.h>
# include "structs.h"
# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include "upng.h"

# define PI 3.14159265
# define TWO_PI 6.28318530
# define EPSILON 0.2
# define TILE_SIZE 64
# define TEXTURE_WIDTH  64
# define TEXTURE_HEIGHT 64
# define MINIMAP_SCALE_FACTOR 0.2

# define FOV_ANGLE (60 * (PI / 180))
# define FPS 30
# define FRAME_TIME_LENGTH (1000 / FPS)

# define WHITE	0x00FFFFFF
# define BLACK	0x00000000
# define RED	0x00FF0000
# define GREEN	0x0000FF00
# define BLUE	0x000000FF
# define YELLOW	0x00FFFF00
# define FAILED	-1
# define SUCCESS	1
# define Y		0
# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE		3
# define X_EVENT_KEY_EXIT		17 //Exit program key code
# define KEY_ESC			53
# define KEY_Q			12
# define KEY_W			13
# define KEY_E			14
# define KEY_R			15
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2
# define KEY_1			18
# define KEY_2			19
# define KEY_3			20
# define KEY_4			21
# define KEY_Q			12
# define KEY_E			14
# define KEY_R			15
# define KEY_I			34
# define KEY_O			31
# define KEY_P			35
# define KEY_J			38
# define KEY_K			40
# define KEY_L			37
# define KEY_LEFT		123
# define KEY_RIGHT		124
# define KEY_FORWARD 	126
# define KEY_BACKWARD	125
# define KEY_TAB	48
# define KEY_MAJ	257

# define C_R				0
# define C_NO				1
# define C_SO				2
# define C_WE				3
# define C_EA				4
# define C_S				5
# define C_F				6
# define C_C				7
# define C_MAP				8

# define DIRECTIONS "NSEW"
# define VALID_MAP_CHARACTERS " 01234NSEW"

# define TEXTURES			7
# define TEX_NORTH			0
# define TEX_SOUTH			1
# define TEX_WEST			2
# define TEX_EAST			3
# define TEX_SKY			4
# define TEX_FLOOR			5
# define TEX_SPRITE			6

# define PTR_CAST(a)	(void*)((uintptr_t)(a))

//graphics
int		initializeWindow(t_cub3d *cub3d);
void	destroyWindow(void);
int		clearColorBuffer(t_cub3d *cub3d, uint32_t color);
void	renderColorBuffer(void);
void	drawPixel(t_cub3d *cub3d, int x, int y, uint32_t color);
void	drawRect(t_cub3d *cub3d, t_rectangle rectangle, uint32_t color);
void	drawLine(t_cub3d *cub3d, t_line line, uint32_t color);

//map
bool	mapHasWallAt(t_config *config, float x, float y);
bool	isInsideMap(t_config *config, float x, float y);
void	renderMapGrid(t_cub3d *cub3d);
int		getMapAt(t_config *config, int i, int j);
//plr
void	movePlayer(t_cub3d *cub3d, float dTime);
void	renderMapPlayer(t_cub3d *cub3d);

bool	isRayFacingUp(float angle);
bool	isRayFacingDown(float angle);
bool	isRayFacingLeft(float angle);
bool	isRayFacingRight(float angle);
void	castRay(t_cub3d *cub3d, float rayAngle, int stripId);
void	castAllRays(t_cub3d *cub3d);
void	renderMapRays(t_cub3d *cub3d);
//textures
void	loadTextures(t_cub3d *cub3d);
void	freeTextures(t_cub3d *cub3d);
//utils
void	normalizeAngle(float *angle);
float	distanceBetweenPoints(float x1, float y1, float x2, float y2);
int		get_delta(int x1, int x0);
//wall
void	renderWallProjection(t_cub3d *cub3d);
//errors
void	ft_exit_error(t_cub3d *cub3d, char const *message);
//sprite
void	renderSpriteProjection(t_cub3d *cub3d);
void	renderMapSprites(t_cub3d *cub3d);
void	collocate_sprites(t_cub3d *cub3d);
void	render_vsbl_sprites(t_cub3d *cub3d, t_sprite *vsbl_sprites, int i);
void	draw_sprite(t_cub3d *cub3d, t_sprite *sprite, int x);
int		find_visible_sprites(t_cub3d *cub3d, t_sprite *vsblSprites);

//parse
int		parse_color(t_config *config, int key, char const *line);
int		parse_dimensions(t_config *config, char const *line);
int		parse_line(t_config *config, char const *line, t_str **map_buffer);
int		str_length(t_str *str);
t_str	*str_add_back(t_str **str, char *content);
int		parse_config(t_config *config, char const *conf_path);
int		str_clear(t_str **list);
int		ft_in_set(t_config *config, char c, char const *set);
int		get_next_line(int fd, char **line);
int		parse_texture(t_config *config, int key, char const *line);
int		check_valid(t_config *config, t_str *map_buffer);
t_str	*ft_split_new(char const *org, char sep);
int		check_top_bottom_borders(t_str *map_buffer);
int		check_left_right_borders(t_str *map_buffer);
int		copy_map(t_config *config, t_str *map_buffer, int *map);
static char	*path_from_line(int start, char const *line);
static int	config_key(char const *line);
static int	str_to_color(t_str *str);
static int	texture_index(int key);
int		ft_endwith(char const *str, char const *end);
t_str	*str_last(t_str *str);

#endif

/* ************************************************************************** */
