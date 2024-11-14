/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alasoare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:09:19 by alasoare          #+#    #+#             */
/*   Updated: 2024/11/14 16:45:36 by smejia-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	open_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		printf("Erro al abrir el arquivo: %s\n", filename);
	}
	return (fd);
}

void	read_single_file(void)

{
	int		fd;
	char	*line;

	fd = open_file("test.txt");
	if (fd == -1)
		return ;
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("linha: %s", line);
		free(line);
		line = get_next_line(fd);
	}
	if (close(fd) == -1)
		perror("Erro ao fechar o arquivo");
}

void	test_invalid_fd(void)
{
	char *line;

	printf("\nTeste FD inválido:\n");
	line = get_next_line(42);
	if (!line)
		printf("PASSOU: get_next_line retornou NULL para FD inválido\n");
	else
	{
		printf("FALHOU: get_next_line não retornou NULL para FD inválido\n");
		free(line);
	}
}

void	test_closed_fd(void)
{
	int		fd;
	char	*line;

	printf("\nTeste FD fechado:\n");
	fd = open_file("test.txt");
	if (fd == -1)
		return ;
	close(fd);

	line = get_next_line(fd);
	if (!line)
		printf("PASSOU: get_next_line retornou NULL para FD fechado\n");
	else
	{
		printf("FALHOU: get_next_line não retornou NULL para FD fechado\n");
		free(line);
	}
}

void	test_large_buffer(void)
{
	printf("\nTeste com BUFFER_SIZE grande (> 1024):\n");
	int fd = open_file("large_test.txt");
	if (fd == -1) return;
	char *line;
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
}

void	test_small_buffer(void)
{
	printf("\nTeste com BUFFER_SIZE pequeno (< 8):\n");
	int fd = open_file("small_test.txt");
	if (fd == -1) return;
	char *line;
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
}

void	test_exact_buffer(void)
{
	printf("\nTeste com BUFFER_SIZE igual ao tamanho da linha:\n");
	int fd = open_file("exact_test.txt");
	if (fd == -1) return;
	char *line;
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
}

void	test_read_stdin(void)
{
	printf("\nTeste com leitura de stdin:\nDigite algumas linhas e pressione Ctrl+D para finalizar:\n");
	char *line;
	while ((line = get_next_line(0)))
	{
		printf("%s", line);
		free(line);
	}
}

void	test_long_line(void)
{
	printf("\nTeste com linha longa (>2k caracteres):\n");
	int fd = open_file("long_line.txt");
	if (fd == -1) return;
	char *line;
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
}

void	test_short_line(void)
{
	printf("\nTeste com linha curta (< 4 caracteres):\n");
	int fd = open_file("short_line.txt");
	if (fd == -1) return;
	char *line;
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
}

void	test_empty_lines(void)
{
	printf("\nTeste com linhas vazias:\n");
	int fd = open_file("empty_lines.txt");
	if (fd == -1) return;
	char *line;
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
}

void	test_multiple_fds(void)
{
	int fd1 = open("file1.txt", O_RDONLY);
	int fd2 = open("file2.txt", O_RDONLY);
	int fd3 = open("file3.txt", O_RDONLY);
	char *line1, *line2, *line3;

	if (fd1 == -1 || fd2 == -1 || fd3 == -1)
	{
		printf("Erro ao abrir um ou mais arquivos de teste.\n");
		return;
	}

	printf("\nLeitura de file1.txt, file2.txt, file3.txt com múltiplos FDs:\n");
	line1 = get_next_line(fd1);
	line2 = get_next_line(fd2);
	line3 = get_next_line(fd3);
	while (line1 || line2 || line3)
	{
		if (line1)
		{
			printf("FD1: %s", line1);
			free(line1);
			line1 = get_next_line(fd1);
		}
		if (line2)
		{
			printf("FD2: %s", line2);
			free(line2);
			line2 = get_next_line(fd2);
		}
		if (line3)
		{
			printf("FD3: %s", line3);
			free(line3);
			line3 = get_next_line(fd3);
		}
	}

	close(fd1);
	close(fd2);
	close(fd3);
}

int	main(void)

{
	read_single_file();
	test_invalid_fd();
	test_closed_fd();
	test_large_buffer();
	test_small_buffer();
	test_exact_buffer();
	test_read_stdin();
	test_long_line();
	test_short_line();
	test_empty_lines();
	test_multiple_fds();
	return (0);
}

