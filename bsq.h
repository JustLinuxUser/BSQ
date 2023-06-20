/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adokhnia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 17:38:45 by adokhnia          #+#    #+#             */
/*   Updated: 2023/06/20 17:38:52 by adokhnia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_H
# include <fcntl.h>
# include <unistd.h>
# define BSQ_H

int	shift_args(int *argc, char ***argv)
{
	if (*argc <= 1)
		return (-1);
	(*argv)++;
	(*argc)--;
	return (0);
}

int	file_len(char *fname)
{
	int		size;
	int		fd;
	char	c;

	size = 0;
	fd = open(fname, O_RDONLY);
	while (read(fd, &c, 1))
		size++;
	close(fd);
	return (size);
}

int	new_line_count(const char *str)
{
	int	iter;
	int	res;

	iter = 0;
	res = 0;
	while (str[iter] != 0)
	{
		if (str[iter] == '\n')
			res++;
	}
	return (res);
}

void	skip_whitespace(const char *str, int *i)
{
	while (str[*i] == '\n' || str[*i] == '\t'
		|| str[*i] == '\f' || str[*i] == ' '
		|| str[*i] == '\v' || str[*i] == '\r')
		(*i)++;
}

int	is_whitespace(char c)
{
	if (c == '\n' || c == '\t'
		|| c == '\f' || c == ' '
		|| c == '\v' || c == '\r')
		return (1);
	return (0);
}

int	ft_atoi(const char *str, int *iter)
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
#endif
