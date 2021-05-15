/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 16:44:32 by asydykna          #+#    #+#             */
/*   Updated: 2021/05/14 18:23:08 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFS_H
# define DEFS_H

# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdlib.h>
# include <SDL2/SDL.h>
# include <limits.h>
# include "structs.h"
# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include "upng.h"

# define PI 3.14159265
# define TWO_PI 6.28318530
# define TILE_SIZE 64
# define TEXTURE_WIDTH  64
# define TEXTURE_HEIGHT 64
# define MINIMAP_SCALE_FACTOR 0.2
//#define WINDOW_WIDTH 1280
//#define WINDOW_HEIGHT 800


# define MAP_NUM_ROWS 13
# define MAP_NUM_COLS 20
# define WINDOW_WIDTH (MAP_NUM_COLS * TILE_SIZE)
# define WINDOW_HEIGHT (MAP_NUM_ROWS * TILE_SIZE)

# define FOV_ANGLE (60 * (PI / 180))
# define NUM_RAYS WINDOW_WIDTH
# define DIST_PROJ_PLANE ((WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2))
# define FPS 30
# define FRAME_TIME_LENGTH (1000 / FPS)

# define WHITE	0x00FFFFFF
# define BLACK	0x00000000
# define RED	0x00FF0000
# define GREEN	0x0000FF00
# define BLUE	0x000000FF
# define YELLOW	0x00FFFF00
# define FAILED						-1
# define TEXTURES				4
# define SUCCESS				1
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

//ray
extern ray_t	rays[NUM_RAYS];

//graphics
int		initializeWindow(t_cub3d *cub3d);
void	destroyWindow(void);
int		clearColorBuffer(t_cub3d *cub3d, uint32_t color);
void	renderColorBuffer(void);
void	drawPixel(t_cub3d *cub3d, int x, int y, uint32_t color);
void	drawRect(t_cub3d *cub3d, int x, int y, int width, int height, uint32_t color);
void	drawLine(t_cub3d *cub3d, int x0, int y0, int x1, int y1, uint32_t color);

//map
bool	mapHasWallAt(float x, float y);
bool	isInsideMap(float x, float y);
void	renderMapGrid(t_cub3d *cub3d);
int		getMapAt(int i, int j);

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

//sprite
void	renderSpriteProjection(t_cub3d *cub3d);
void	renderMapSprites(t_cub3d *cub3d);

//textures
void	loadTextures(t_cub3d *cub3d);
void	freeTextures(t_cub3d *cub3d);

//utils
void	normalizeAngle(float *angle);
float	distanceBetweenPoints(float x1, float y1, float x2, float y2);

//wall
void	renderWallProjection(t_cub3d *cub3d);

//errors
void	ft_exit_error(t_cub3d *cub3d, char const *message);

void	collocate_sprites(t_cub3d *cub3d);
#endif