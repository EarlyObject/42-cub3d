#ifndef STRUCTS_H
#define STRUCTS_H

#include "../mlx/mlx.h"
//#include "player.h"

uint32_t *colorBuffer;

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

#define X_EVENT_KEY_PRESS		2
#define X_EVENT_KEY_RELEASE		3

#define X_EVENT_KEY_EXIT		17 //Exit program key code
#define KEY_ESC			53
#define KEY_Q			12
#define KEY_W			13
#define KEY_E			14
#define KEY_R			15
#define KEY_A			0
#define KEY_S			1
#define KEY_D			2

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
		void			*img_ptr;
		uint32_t		*addr;
		int				bits_per_pixel;
		int				line_length;
		int				endian;
	} t_image;

	//мое:
	typedef struct s_player
	{
		float x;
		float y;
		float width;
		float height;
		int turnDirection; //-1 for left, +1 for right
		int walkDirection; //-1 for back, +1 for front
		float rotationAngle;
		float walkSpeed;
		float turnSpeed;
	} t_player;

	typedef	struct s_cub3d
	{
		void			*win;
		t_image 		image;
		t_player		player;
		t_mlx			mlx;
		t_data			data;
		uint32_t		*colorBuffer;
		//t_map			map;
		//ray_t			rays;
	} t_cub3d;



#endif