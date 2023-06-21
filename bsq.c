/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adokhnia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:20:06 by adokhnia          #+#    #+#             */
/*   Updated: 2023/06/20 14:20:09 by adokhnia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "bsq.h"

int	sq_can_fit(char **str, int x, int y, int size)
{
	int	x_iter;
	int	y_iter;

	y_iter = y;
	while (y_iter < y + size)
	{
		x_iter = x;
		while (x_iter < x + size)
		{
			if (str[y_iter][x_iter] == 'o')
				return (-1);
			x_iter++;
		}
		y_iter++;
	}
	return (0);
}

void	pr_x(char **str, int len, int width, int x, int y, int size)
{
	int	i_y;
	int	i_x;

	i_y = 0;
	while (i_y < len)
	{
		i_x = 0;
		while (i_x < width)
		{
			if (i_y <= y + size && i_x <= x + size && i_y >= y && i_x >= x)
				printf("X");
			else
				printf("%c", str[i_y][i_x]);
			i_x++;
		}
		printf("\n");
		i_y++;
	}
	printf("\n");
}

int	find_sq(char **str, int len, int width)
{
	int	cords[2];
	int	size;
	int	cords_found[2];

	size = 0;
	cords[0] = 0;
	while (cords[0] < len - size)
	{
		cords[1] = 0;
		while (cords[1] < width - size)
		{
			if (sq_can_fit(str, cords[1], cords[0], size + 1) == 0)
			{
				cords_found[0] = cords[0];
				cords_found[1] = cords[1];
				size++;
			}
			else
				cords[1]++;
		}
		cords[0]++;
	}
	pr_x(str, len, width, cords_found[1], cords_found[0], size);
	return (0);
}

void	parse_first_line(int *iter, char *file_str, char controls[3])
{
	controls[0] = file_str[*iter];
	(*iter)++;
	controls[1] = file_str[*iter];
	(*iter)++;
	controls[2] = file_str[*iter];
	(*iter)++;
	(*iter)++;
}

int	*parse_file(char **file_str, char ***map)
{
	int		iter;
	int		len;
	int		line;
	int		*size;
	int		line_iter;
	char	controls[3];

	line_iter = 0;
	line = 0;
	iter = 0;
	len = ft_atoi(*file_str, &iter);
	*map = malloc(sizeof (char *) * len);
	size = malloc(sizeof (int) * 2);
	parse_first_line(&iter, *file_str, controls);
	printf("%.3s\n", controls);
	while (0 != (*file_str)[iter])
	{
		line_iter = 0;
		(*map)[line] = malloc(sizeof (char) * len);
		while ((*file_str)[iter] != '\n')
		{
			if ((*file_str)[iter] == controls[0])
				(*map)[line][line_iter] = '.';
			if ((*file_str)[iter] == controls[1])
				(*map)[line][line_iter] = 'o';
			iter++;
			line_iter++;
		}
		iter++;
		line++;
	}
	if (line != len)
	{
		printf("line: %i, len: %i\n", line, len);
		return (0);
	}
	size[1] = len;
	size[0] = line_iter;
	return (size);
}

int	main(int argc, char **argv)
{
	int		f_size;
	int		fd;
	char	*f_name;
	char	*file_str;
	char	**map;
	int		*size;

	if (argc != 2)
	{
		printf("Error, provide 1 arg\n");
		return (-1);
	}
	shift_args(&argc, &argv);
	f_name = *argv;
	f_size = file_len(f_name);
	fd = open(f_name, O_RDONLY);
	file_str = malloc(sizeof(char) * f_size);
	read(fd, file_str, f_size);
	printf("read the file\n");
	size = parse_file(&file_str, &map);
	if (size != 0)
	{
		printf("size: %i, %i\n", size[0], size[1]);
		find_sq(map, size[1], size[0]);
	}
	else
		printf("done goofed\n");
}
