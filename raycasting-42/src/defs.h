/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 16:44:32 by asydykna          #+#    #+#             */
/*   Updated: 2021/06/07 11:37:22 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFS_H
# define DEFS_H

# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>
# include "structs.h"
# include "../mlx/mlx.h"
# include "../libft/libft.h"

# define TEXTURE_WIDTH  64
# define TEXTURE_HEIGHT 64
# define MINIMAP_SCALE_FACTOR 0.2
# define WHITE	0x00FFFFFF
# define BLACK	0x00000000
# define GREEN	0x0000FF00
# define BLUE	0x000000FF
# define RED	0x00FF0000
# define YELLOW	0x00FFFF00
# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_KEY_EXIT		17
# define KEY_ESC				53
# define KEY_W					13
# define KEY_A					0
# define KEY_S					1
# define KEY_D					2
# define KEY_LEFT				123
# define KEY_RIGHT				124
# define KEY_FORWARD 			126
# define KEY_BACKWARD			125
# define C_R					0
# define C_NO					1
# define C_SO					2
# define C_WE					3
# define C_EA					4
# define C_S					5
# define C_F					6
# define C_C					7
# define C_MAP					8
# define DIRECTIONS 			"NSEW"
# define VALID_MAP_CHARACTERS 	" 01234NSEW"
# define TEXTURES				7
# define TEX_NORTH				0
# define TEX_SOUTH				1
# define TEX_WEST				2
# define TEX_EAST				3
# define TEX_SKY				4
# define TEX_FLOOR				5
# define TEX_SPRITE				6
# define U_DIV 1
# define V_DIV 1
# define V_MOVE 0.0

int				initialize_window(t_cub3d *cub3d);
int				clear_color_buffer(t_cub3d *cub3d, uint32_t color);
void			ft_exit_error(t_cub3d *cub3d, char const *message);
void			init_cub3d(t_cub3d *cub3d);
void			init_config(t_config *config);
void			init_player(t_cub3d *cub3d);
void			load_textures(t_cub3d *cub3d);
void			draw_pixel(t_cub3d *cub3d, int x, int y, uint32_t color);
void			draw_sprites(t_cub3d *cub3d);
void			setup(t_cub3d *cub3d, t_config *config, char *conf_path);
int				parse_config(t_config *config, char const *conf_path);
int				check_top_bottom_borders(t_str *map_buffer);
int				check_left_right_borders(t_str *map_buffer);
int				check_valid(t_config *config, t_str *map_buffer);
int				copy_map(t_config *config, t_str *map_buffer, int *map);
int				ft_endwith(char const *str, char const *end);
int				get_next_line(int fd, char **line);
int				parse_line(t_config *config,
					char const *line, t_str **map_buffer);
int				string_length(t_str *str);
t_str			*string_add_back(t_str **str, char *content);
int				string_clear(t_str **list);
void			screenshot(t_cub3d *cub3d);
t_str			*string_last(t_str *str);
int				ft_in_set(t_config *config, char c, char const *set);
t_str			*ft_split_new(char const *org, char sep);
int				parse_color(t_config *config, int key, char const *line);
int				parse_dimensions(t_config *config, char const *line);
int				parse_texture(t_config *config, int key, char const *line);
int				exit_game(t_cub3d *cub3d, int code);
int				count_sprites(t_config *config);
void			resume_init_config(t_config *config);
void			find_sprites(t_config *config);
int				deal_key(int key_code, t_cub3d *cub3d);
void			look_left(t_cub3d *cub3d, double oldDirX, double oldPlaneX);
void			look_right(t_cub3d *cub3d, double oldDirX, double oldPlaneX);
void			move_aside(int key_code, t_cub3d *cub3d);
void			move_forward(t_cub3d *cub3d);
void			move_backward(t_cub3d *cub3d);
void			draw_floor_ceiling(t_cub3d *cub3d, int start,
					int end, int texnum);
int				close_win(void);
void			perform_dda(t_cub3d *cub3d);
void			calc_step_and_side_dist(t_cub3d *cub3d);
void			draw_walls(t_cub3d *cub3d, int x, int start, int end);
void			calc_ray(t_cub3d *cub3d, int x);
void			calc_wall_x(t_cub3d *cub3d);
void			manage_walls(t_cub3d *cub3d);
void			init_wall(t_cub3d *cub3d);
void			sort_sprites(t_cub3d *cub3d, t_config *config);
int				main_loop(t_cub3d *cub3d);
void			bmp_builder(t_cub3d *cub3d, char *file_name);
void			draw_rect(t_cub3d *cub3d, t_rectangle rectangle, uint32_t color);
void			init_screen(t_cub3d *cub3d);
#endif