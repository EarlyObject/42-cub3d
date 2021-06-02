/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 08:48:51 by asydykna          #+#    #+#             */
/*   Updated: 2021/05/28 09:47:04 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

static	int
	make_bmp(t_cub3d *cub3d, char *file_name)
{
	int	fd;

	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd <= 0)
		ft_exit_error(cub3d, "ERROR: ERROR CREATING BMP FILE");
	return (fd);
}

static void
	make_header(t_config *config, t_screenshot *screenshot)
{
	screenshot->byte_type[0] = 0x42;
	screenshot->byte_type[1] = 0x4D;
	screenshot->byte_size = (config->width * config->height * 4) + 54;
	screenshot->byte_reserved = 0x00000000;
	screenshot->byte_offset = 0x36;
	screenshot->header_size = 40;
	screenshot->image_width = config->width;
	screenshot->image_height = -config->height;
	screenshot->color_planes = 1;
	screenshot->bpp = 32;
	screenshot->compression = 0;
	screenshot->image_size = (config->width * config->height * 4);
	screenshot->bits_xpels_per_meter = 2835;
	screenshot->bits_xpels_per_meter = 2835;
	screenshot->total_colors = 0;
	screenshot->important_colors = 0;
}

static void
	write_header(int fd, t_screenshot screenshot)
{
	write(fd, &screenshot.byte_type, 2);
	write(fd, &screenshot.byte_size, 4);
	write(fd, &screenshot.byte_reserved, 4);
	write(fd, &screenshot.byte_offset, 4);
	write(fd, &screenshot.header_size, 4);
	write(fd, &screenshot.image_width, 4);
	write(fd, &screenshot.image_height, 4);
	write(fd, &screenshot.color_planes, 2);
	write(fd, &screenshot.bpp, 2);
	write(fd, &screenshot.compression, 4);
	write(fd, &screenshot.image_size, 4);
	write(fd, &screenshot.bits_xpels_per_meter, 4);
	write(fd, &screenshot.bits_ypels_per_meter, 4);
	write(fd, &screenshot.total_colors, 4);
	write(fd, &screenshot.important_colors, 4);
}

static void
	write_to_bmp(t_cub3d *cub3d, int fd, int imagesize)
{
	char		*pixel_array;
	int			i;
	int			j;

	pixel_array = malloc(sizeof(char) * imagesize * 4);
	if (!pixel_array)
		ft_exit_error(cub3d, "ERROR: ERROR WHILE WRITE TO BMP FILE.");
	i = 0;
	j = 0;
	imagesize /= 4;
	while (i < imagesize)
	{
		pixel_array[j++] = cub3d->image.addr[i] & 255;
		pixel_array[j++] = (cub3d->image.addr[i] & 255 << 8) >> 8;
		pixel_array[j++] = (cub3d->image.addr[i] & 255 << 16) >> 16;
		pixel_array[j++] = 0;
		i++;
	}
	write(fd, pixel_array, imagesize *= 4);
	free(pixel_array);
}

void
	bmp_builder(t_cub3d *cub3d, char *file_name)
{
	t_screenshot	screenshot;
	int				fd;

	ft_bzero(&screenshot, sizeof(t_screenshot));
	fd = make_bmp(cub3d, file_name);
	make_header(cub3d->config, &screenshot);
	write_header(fd, screenshot);
	write_to_bmp(cub3d, fd, screenshot.image_size);
	close(fd);
}

void
	screenshot(t_cub3d *cub3d)
{
	//update(cub3d);
	//render(cub3d);
	bmp_builder(cub3d, "screenshot.bmp");
	printf("SCREENSHOT MADE SUCCESSFULLY.");
	exit_game(cub3d, EXIT_SUCCESS);
}