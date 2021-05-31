/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asydykna <asydykna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 08:35:01 by asydykna          #+#    #+#             */
/*   Updated: 2021/05/25 21:16:10 by asydykna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defs.h"

static	int
	create_file(char *file_name)
{
	int	fd;

	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (!((fd) > 0))
	{
		ft_putstr_fd("ERROR: ERROR WHILE CREATING BMB\n", 1);
	}
	return (fd);
}

static void
	make_header(t_config *config, t_screenshot *info_bmp_file)
{
	info_bmp_file->byte_type[0] = 0x42;
	info_bmp_file->byte_type[1] = 0x4D;
	info_bmp_file->byte_size = (config->width * config->height * 4) + 54;
	info_bmp_file->byte_reserved = 0x00000000;
	info_bmp_file->byte_offset = 0x36;
	info_bmp_file->header_size = 40;
	info_bmp_file->image_width = config->width;
	info_bmp_file->image_height = -config->height;
	info_bmp_file->color_planes = 1;
	info_bmp_file->bpp = 32;
	info_bmp_file->compression = 0;
	info_bmp_file->image_size = (config->width * config->height * 4);
	info_bmp_file->bits_xpels_per_meter = 2835;
	info_bmp_file->bits_xpels_per_meter = 2835;
	info_bmp_file->total_colors = 0;
	info_bmp_file->important_colors = 0;
}

static void
	write_header(int fd, t_screenshot info_bmp_file)
{
	write(fd, &info_bmp_file.byte_type, 2);
	write(fd, &info_bmp_file.byte_size, 4);
	write(fd, &info_bmp_file.byte_reserved, 4);
	write(fd, &info_bmp_file.byte_offset, 4);
	write(fd, &info_bmp_file.header_size, 4);
	write(fd, &info_bmp_file.image_width, 4);
	write(fd, &info_bmp_file.image_height, 4);
	write(fd, &info_bmp_file.color_planes, 2);
	write(fd, &info_bmp_file.bpp, 2);
	write(fd, &info_bmp_file.compression, 4);
	write(fd, &info_bmp_file.image_size, 4);
	write(fd, &info_bmp_file.bits_xpels_per_meter, 4);
	write(fd, &info_bmp_file.bits_ypels_per_meter, 4);
	write(fd, &info_bmp_file.total_colors, 4);
	write(fd, &info_bmp_file.important_colors, 4);
}

static void
	write_to_bmp(t_cub3d *cub3d, int fd, int imagesize)
{
	char		*pixel_array;
	int			i;
	int			j;

	pixel_array = malloc(sizeof(char) * imagesize * 4);
	if (!pixel_array)
		ft_exit_error(cub3d, "ERROR: ERROR IN WRITE FILE.");
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
	j = write(fd, pixel_array, imagesize *= 4);
	free(pixel_array);
}

void
	bmp_builder(t_cub3d *cub3d, char *file_name)
{
	t_screenshot	info_bmp_file;
	int				fd;

	ft_bzero(&info_bmp_file, sizeof(t_screenshot));
	fd = create_file(file_name);
	make_header(cub3d->config, &info_bmp_file);
	write_header(fd, info_bmp_file);
	write_to_bmp(cub3d, fd, info_bmp_file.image_size);
	close(fd);
	(void)info_bmp_file;
}
