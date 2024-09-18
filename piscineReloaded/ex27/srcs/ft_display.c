/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smejia-a <smejia-a@student.42barcelona.com>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:04:39 by smejia-a          #+#    #+#             */
/*   Updated: 2024/09/18 15:11:06 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#define BUFFER_SIZE 1024

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

static void	print_error(const char *message)
{
	write (2, message, ft_strlen(message));
}

static void	display_file_content(int fd)
{
	char	buffer[BUFFER_SIZE];	
	ssize_t	bytes_read;

	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		write (1, buffer, bytes_read);
	}
}

int	main(int argc, char **argv)
{
	int	fd;

	if (argc == 1)
	{
		print_error("File name missing.\n");
		return (1);
	}
	if (argc > 2)
	{
		print_error("Too many arguments.\n");
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		print_error("Cannot read file.\n");
		return (1);
	}
	display_file_content(fd);
	close(fd);
	return (0);
}
