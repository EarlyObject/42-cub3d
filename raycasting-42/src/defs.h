/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 16:44:32 by asydykna          #+#    #+#             */
/*   Updated: 2021/06/13 19:44:15 by asydykna         ###   ########.fr       */
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
# define TEXTURES				7
# define TEX_NORTH				0
# define TEX_SOUTH				1
# define TEX_WEST				2
# define TEX_EAST				3
# define TEX_SKY				4
# define TEX_FLOOR				5
# define TEX_SPRITE				6
# define ROT 0.05
# define MOVE_SPEED 0.1

int				init_window(t_cub3d *cub3d);
void			init_cub3d(t_cub3d *cub3d);
void			init_config(t_config *config);
void			init_keys(t_cub3d *cub3d);
void			resume_init_config(t_cub3d *cub3d);
void			init_screen(t_cub3d *cub3d);
void			init_wall(t_cub3d *cub3d);
void			init_parts(t_cub3d *cub3d, char *conf_path);
void			ft_exit_error(t_cub3d *cub3d, char const *message);
void			ft_error_close(int error_code);
void			load_textures(t_cub3d *cub3d);
void			draw_pixel(t_cub3d *cub3d, int x, int y, uint32_t color);
void			draw_sprites(t_cub3d *cub3d);
void			draw_single_sprite(t_cub3d *cub3d);
void			draw_floor_ceiling(t_cub3d *cub3d, int start,
					int end, int texnum);
void			setup(t_cub3d *cub3d, t_config *config, char *conf_path);
int				ft_endwith(char const *str, char const *end);
int				get_next_line(int fd, char **line);
void			screenshot(t_cub3d *cub3d);
void			parse_color(t_cub3d *cub3d, const char *str, t_config *config);
int				exit_game(t_cub3d *cub3d, int code);
void			find_sprites(t_cub3d *cub3d, t_config *config);
int				deal_key(int key_code, t_cub3d *cub3d);
int				release_key(int key_code, t_cub3d *cub3d);
void			move_player(t_cub3d *cub3d);
void			look_left(t_cub3d *cub3d, double oldDirX, double oldPlaneX);
void			look_right(t_cub3d *cub3d, double oldDirX, double oldPlaneX);
void			move_forward(t_cub3d *cub3d);
void			move_backward(t_cub3d *cub3d);
void			move_left(t_cub3d *cub3d);
void			move_right(t_cub3d *cub3d);
int				close_win(void);
int				main_loop(t_cub3d *cub3d);
void			perform_dda(t_cub3d *cub3d);
void			calc_step_and_side_dist(t_cub3d *cub3d);
void			calc_ray(t_cub3d *cub3d, int x);
void			calc_wall_x(t_cub3d *cub3d);
void			draw_walls(t_cub3d *cub3d, int x, int start, int end);
void			manage_walls(t_cub3d *cub3d);
void			sort_sprites(double *order, double *distance,
					int num_spr, int index);
void			bmp_builder(t_cub3d *cub3d, char *file_name);
void			check_mem_alloc(void *p);
void			parse_args(t_cub3d *cub3d, int ac, char *filename, char *save);
void			parse_color(t_cub3d *cub3d, const char *str, t_config *config);
void			parse_map(t_cub3d *cub3d);
void			check_line_content(char *str, t_cub3d *cub3d,
					bool *is_map_started);
char			**free_twod_array(char **array);
void			check_map_bits(t_cub3d *cub3d);
void			create_map(t_cub3d *cub3d, t_config *config, int i);
size_t			two_d_map_counter(char ***s);
void			manage_color(t_cub3d *cub3d, const char *str, t_config *config);
void			parse_resolution(t_cub3d *cub3d, char *str, t_config *config);
bool			count_commas(const char *str);
void			free_lst_content(void *content);
bool			is_all_print(const char *s);
char			*ft_replace(const char *str, const char *rmv, const char *pst);
bool			is_all_digits(const char *s);
size_t			find_max_len(t_cub3d *cub3d);
void			check_sign(const char *str, const char *previous,
					const char *next, t_cub3d *cub3d);
void			check_vertical_borders(t_cub3d *cub3d);
void			check_horizontal_border(const char *str);
void			ft_my_lstclear(t_d_list **lst, void (*del)(void *));
void			manage_textures(t_cub3d *cub3d, const char *str,
					t_config *config);
t_d_list		*ft_my_lstnew(void *content, t_d_list **prev);
bool			is_map_valid(t_checklist *chk);
void			fill_c_colors(t_cub3d *cub3d, t_config *config,
					char **rgb, int j);
void			set_color(t_cub3d *cub3d, const char *str,
					t_config *config, char **rgb);
void			calc_sprite(t_cub3d *cub3d, int i);
void			set_player_vectors(t_cub3d *cub3d, int j, int i);
#endif
