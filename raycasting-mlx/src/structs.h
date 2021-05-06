#ifndef STRUCTS_H
#define STRUCTS_H

#include "../minilibx/mlx.h"

# define FAILED						-1
# define TEXTURES				4
# define SUCCESS				1
# define Y		0

#define X_EVENT_KEY_PRESS		2
#define X_EVENT_KEY_EXIT		17 //Exit program key code
#define KEY_ESC			53
#define KEY_Q			12
#define KEY_W			13
#define KEY_E			14
#define KEY_R			15
#define KEY_A			0
#define KEY_S			1
#define KEY_D			2

typedef	struct		s_mlx
	{
		void			*mlx;
		void			*window;
		void			*img;
	}					t_mlx;

	typedef	struct		s_data {
		char			*addr;
		int				bits_per_pixel;
		int				line_length;
		int				endian;
	}					t_data;

	typedef struct s_image
	{
		void		*img;
		char		*addr;
		int			bits_per_pixel;
		int			line_length;
		int			endian;
	} t_image;


	typedef	struct s_cub3d
	{
		//void			*mlx; не было
		void			*win;
		t_image 		image;
		//t_map			map;
		//player_t		player;
		//ray_t			rays;
		t_mlx			mlx;
		t_data			data;
	}					t_cub3d;

	

#endif