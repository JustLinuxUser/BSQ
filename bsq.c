#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


int	file_len(char * fname)
{
	int		size;
	int		fd;
	char	c;
	fd = open(fname, O_RDONLY);
	size = 0;
	while(read(fd, &c, 1))
		size++;
	close(fd);
	return (size);
}

void	skip_whitespace(char *str, int *i)
{
	while(str[*i] == '\n' || str[*i] == '\t'
		|| str[*i] == '\f' || str[*i] == ' '
		|| str[*i] == '\v' || str[*i] == '\r')
		(*i)++;
}

int	is_whitespace(char c)
{
	if(c == '\n' || c == '\t'
		|| c == '\f' || c == ' '
		|| c == '\v' || c == '\r')
		return(1);
	return(0);
}

int	ft_atoi(char *str, int *iter)
{
	int	result;

	result = 0;
	while (str[*iter] >= '0' && str[*iter] <= '9')
	{
		result = result * 10 + str[*iter] - '0';
		(*iter)++;
	}
	return (result);
}

int shift_args(int *argc, char ***argv)
{
	if(*argc <= 1)
		return (-1);
	(*argv)++;
	(*argc)--;
	return (0);
}

int	go_to_next_line(char **str)
{
	int	i;

	i = 0;
	while ((*str)[i] != '\n' )
	{
		if ((*str)[i] == 0)
			return (-1);
		i++;
	}
	*str += i;
	return (0);
}

int	sq_can_fit(char **str, int x, int y, int size)
{
	int x_iter;
	int y_iter;

	y_iter = y;
	while (y_iter <= y + size)
	{
		x_iter = x;
		while (x_iter <= x + size)
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
	for(int i_y = 0; i_y < len; i_y++)
	{
		for(int i_x = 0; i_x < width; i_x++)
		{
			if (i_y <= y + size && i_x <= x + size && i_y >= y && i_x >= x)
				printf("X");
			else
				printf("%c", str[i_y][i_x]);
		}
		printf("\n");
	}
	printf("\n");
}

int	find_sq(char **str, int len, int width)
{
	int cords[2];
	int size;
	int cords_found[2];

	size = 0;
	cords[0] = 0;
	while (cords[0] < len - size)
	{
		cords[1] = 0;
		while (cords[1] < width - size)
		{
			if (sq_can_fit(str, cords[1], cords[0], size+1) == 0)
			{
				cords_found[0] = cords[0];
				cords_found[1] = cords[1];
				size++;
			}
			else
				cords[1]++;
			//printf("c[1]: %i, width: %i, size: %i\n", cords[1], width, size);
		}
		cords[0]++;
	}
	//printf("x:%i y:%i size:%i\n", cords_found[1], cords_found[0], size);
	pr_x(str, len, width, cords_found[1], cords_found[0], size);
	return 0;
}

int *parse_file(char **file_str, char ***map)
{
	int iter;
	int len;
	int line;
	int	*size;
	int line_iter;
	char	controls[3];

	*map = malloc(sizeof (char *)*100);
	line_iter = 0;
	line = 0;
	iter = 0;
	size = malloc(sizeof (int) * 2);
	len = ft_atoi(*file_str, &iter);
	controls[0] = (*file_str)[iter];
	iter++;
	controls[1] = (*file_str)[iter];
	iter++;
	controls[2] = (*file_str)[iter];
	iter++;
	iter++;
//	printf("%.3s\n", controls);
//	printf("length is %i\n", len);
	while (0 != (*file_str)[iter])
	{
//		printf("%s\n", *file_str);
		line_iter = 0;
		(*map)[line] = malloc(sizeof (char) * len);
		while ((*file_str)[iter] != '\n')
		{
			if ((*file_str)[iter] == controls[0])
				(*map)[line][line_iter] = '.';
			if ((*file_str)[iter] == controls[1])
				(*map)[line][line_iter] = 'o';
//			printf("%i :%.25s\n", iter, (*map)[line]);
			iter++;
			line_iter++;
		}
		iter++;
		if (line_iter != len)
		{
//			printf("line_iter %i len %i\n", line_iter, len);
			return (0);
		}
		line++;
	}
	size[0] = len;
	size[1] = line;
	return (size);
	//go_to_next_line(file_str);
}
int main(int argc, char **argv)
{
	int f_size;
	int	fd;
	int	line;
	char *f_name;
	char *file_str;
	char **map;

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
//	printf("%s", file_str);
	int *size = parse_file(&file_str, &map);
	if (size != 0)
	{
//		printf("size: %i %i\n", size[0], size[1]);
		find_sq(map, size[0], size[1]);
	}
	else
		printf("done goofed\n");
}
