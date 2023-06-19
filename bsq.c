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

long long	ft_atoll(char *str, int *iter)
{
	int			sign;
	long long	result;

	iter = 0;
	sign = 1;
	result = 0;
	skip_whitespace(str, iter);
	while (str[*iter] == '+' || str[*iter] == '-')
	{
		if (str[*iter] == '-')
			sign *= -1;
		iter++;
	}
	while (str[*iter] >= '0' && str[*iter] <= '9')
	{
		result = result * 10 + str[*iter] - '0';
		iter++;
	}
	return (result * sign);
}

int shift_args(int *argc, char ***argv)
{
	if(*argc <= 1)
		return (-1);
	(*argv)++;
	(*argc)--;
	return (0);
}

int main(int argc, char **argv)
{
	while (argc >= 1)
	{
		shift_args(&argc, &argv);
		printf("argc: %i argv %s\n", argc, *argv);
	}
}
