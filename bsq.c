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
	skip_whitespace(str, iter);
	if (str[*iter] == '+' || str[*iter] == '-')
		return (-1);
	while (str[*iter] >= '0' && str[*iter] <= '9')
	{
		result = result * 10 + str[*iter] - '0';
		iter++;
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
	while (*str[i] != '\n' )
	{
		if (*str[i] == 0)
			return (-1);
		i++;
	}
	*str += i;
	return (0);
}

int main(int argc, char **argv)
{
	int f_size;
	int	fd;
	int	line;
	char *f_name;
	char *file_str;

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
	printf("%s", file_str);
}
