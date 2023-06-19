#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


long long	*resize_long_long_arr(long long *arr, int length)
{
	int			iter;
	long long	*arr_new;

	iter = 0;
	arr_new = malloc(sizeof(long long) * length * 2);
	while (iter < length)
	{
		arr_new[iter] = arr[iter];
		iter++;
	}
	while (iter < length * 2)
	{
		arr_new[iter] = -1;
		iter++;
	}
	free(arr);
	return (arr_new);
}

char	**resize_char_char_arr(char **arr, int length)
{
	int			iter;
	char		**arr_new;

	iter = 0;
	arr_new = malloc(sizeof(char *) * length * 2);
	while (iter < length)
	{
		arr_new[iter] = arr[iter];
		iter++;
	}
	while (iter < length * 2)
	{
		arr_new[iter] = 0;
		iter++;
	}
	free(arr);
	return (arr_new);
}

char	*resize_char_arr(char *arr, int length)
{
	int			iter;
	char		*arr_new;

	iter = 0;
	arr_new = malloc(sizeof(char ) * length * 2);
	while (iter < length)
	{
		arr_new[iter] = arr[iter];
		iter++;
	}
	while (iter < length * 2)
	{
		arr_new[iter] = 0;
		iter++;
	}
	free(arr);
	return (arr_new);
}

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

int	parce_words(char *str, char *out)
{
	int	i;
	int	word_start;
	int	i_out;
	int	out_size;

	out_size = 10;
	out = malloc(sizeof(char) * out_size);
	word_start = 0;
	i = 0;
	i_out = 0;
	while (str[i] != '\n' && str[i] != 0)
	{
		if (i_out >= out_size - 1)
		{
			resize_char_arr(out, out_size);
		}
		if (is_whitespace(str[i]) == 1)
			word_start = 1;
		else
		{
			if(word_start)
			{
				word_start = 0;
				if (i != 0)
				{
					str[i] = ' ';
					i_out++;
				}
			}
			else
			{
				out[i] = str[i];
				i_out++;
			}
		}
		i++;
	}
	return (0);
}

int	parce_ln(char	*line, long long **dict_key, char **dict_val, int length)
{
	int	i;
	long long	*key;

	key = malloc(sizeof (long long));
	i = 0;
	skip_whitespace(line, &i);
	*key = ft_atoll(&line[i], &i);
	skip_whitespace(line, &i);
	if (line[i] != ':')
		return (-1);
	skip_whitespace(line, &i);
	while (line[i] != 0 && line[i] != '\n')
	{

	}
	return (0);
}

int	main()
{
	int 	fd = open("test", O_RDONLY);
	int		size;
	char	*dict;
	char	*fname;
	char	*line;
	int		iter;
	int		line_len;
	int		line_size;

	fname = "test";
	size = file_len(fname);
	dict = malloc(sizeof (char) * size);
	fd = open(fname, O_RDONLY);
	read(fd, dict, size);
	line_size = 10;
	line = malloc(sizeof(char)* line_size);
	while (dict[iter] != 0)
	{
		line_len = 0;
		while (dict[iter] != '\n')
		{
			if(line_size <= line_len + 2){
				line = resize_char_arr(line, line_size);
				line_size *= 2;
			}
				
			line[line_len] = dict[iter];
			line_len++;
			iter++;
		}
		line[line_len] = 0;
		iter++;
		printf("%s\n", line);
	}
}
