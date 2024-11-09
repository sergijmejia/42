/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 11:52:19 by rtorrent          #+#    #+#             */
/*   Updated: 2024/09/30 02:53:52 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "ft_printf.h"
#include "tests.h"

/*
	create the tester by
		1. compiling the project with the 'make' command
		2. copying the contents of the 'tester' folder into its parent folder
		3. compiling with 'cc tester.c libftprintf.a libft/libft.a -w -o test'

	run the tester in "silent mode" with './test', or display all test results
		on-screen with './test -p' or './test -P'
*/

#define NAME0 "/tmp/test_stdc"
#define NAME1 "/tmp/test_ft_printf"
#define BUFFERSIZE 512

#define TEST(X) if (!fail) {													\
					if (!silent)												\
						dprintf(fd[0], "* Test " #X " libc\'s printf:\n");		\
					nc = dprintf(fd[0], TEST ## X);								\
					dprintf(fd[0], "\n#char(s): %d\n", nc);						\
																				\
					if (!silent)												\
						dprintf(fd[1], "\n* Test " #X " 42\'s ft_printf:\n");	\
					nc = ft_printf(TEST ## X);									\
					dprintf(fd[1], "\n#char(s): %d\n", nc);						\
																				\
					if (silent)													\
					{															\
						if (readtmp(fd, off)) {									\
							dprintf(fd[2], "Test " #X "...  failed!\n");		\
							fail = 1;											\
						}														\
						else													\
							dprintf(fd[2], "Test " #X "...  success!\n");		\
					}															\
					else														\
						ft_putchar_fd('\n', fd[2]);								\
				}

int readtmp(int *fd, off_t *off)
{
	ssize_t size_0, size_1;
	char buffer_0[BUFFERSIZE], buffer_1[BUFFERSIZE];
	size_t idx_0 = 0, idx_1 = 0;
	int fail;

	off[0] = lseek(fd[0], off[0], SEEK_SET);
	off[1] = lseek(fd[1], off[1], SEEK_SET);
	size_0 = read(fd[0], buffer_0, BUFFERSIZE);
	size_1 = read(fd[1], buffer_1, BUFFERSIZE);
	fail = (off[0] == -1 || off[1] == -1 || size_0 == -1 || size_1 == -1);

	while (!fail && (idx_0 < size_0 || idx_1 < size_1))
	{
		while (!ft_isprint(buffer_0[idx_0]) && idx_0 < size_0)
			idx_0++;
		while (!ft_isprint(buffer_1[idx_1]) && idx_1 < size_1)
			idx_1++;
		if (idx_0 == size_0 || idx_1 == size_1) {
			fail = !(idx_0 == size_0 && idx_1 == size_1);
			break ;
		}
		fail = (buffer_0[idx_0++] != buffer_1[idx_1++]);
	}

/*
	ft_putstr_fd("buffer_0 >>", fd[2]);
	write(fd[2], buffer_0, size_0);
	ft_putstr_fd("<<\n", fd[2]);
	ft_putstr_fd("buffer_1 >>", fd[2]);
	write(fd[2], buffer_1, size_1);
	ft_putstr_fd("<<\n", fd[2]);
*/

	off[0] = lseek(fd[0], 0, SEEK_END);
	off[1] = lseek(fd[1], 0, SEEK_END);
	if (off[0] == -1 || off[1] == -1)
		fail = 1;

	return fail;
}

int main(int argc, char *argv[])
{
	int	silent, fail = 0;
	int nc;
	int fd[3];
	off_t off[2] = {0};

	silent = (argc != 2 || (strcmp(argv[1], "-p") && strcmp(argv[1], "-P")));
	if (argc > 2 || (argc == 2 && silent))
		return 1;

	if (silent)
	{
		fd[0] = open(NAME0, O_CREAT | O_RDWR, 0600);
		if (fd[0] != -1)
			fail = unlink(NAME0);
		fd[1] = open(NAME1, O_CREAT | O_RDWR, 0600);
		if (fd[1] != -1)
			fail = unlink(NAME1) || fail;
		fd[2] = dup(STDOUT_FILENO);
		if (fd[0] == -1 || fd[1] == -1 || fd[2] == -1 || dup2(fd[1], STDOUT_FILENO) == -1)
		{
			if (fd[0] != -1)
				close(fd[0]);
			if (fd[1] != -1)
				close(fd[1]);
			if (fd[2] != -1)
				close(fd[2]);
			return 1;
		}
	}
	else
		fd[0] = fd[1] = fd[2] = STDOUT_FILENO;

// mandatory tests
	TEST(00) TEST(01) TEST(02) TEST(03) TEST(04) TEST(05) TEST(06) TEST(07) TEST(08)
	TEST(09) TEST(10) TEST(11) TEST(12) TEST(13) TEST(14) TEST(15) TEST(16) TEST(17)
	TEST(18) TEST(19) TEST(20) TEST(21) TEST(22) TEST(23) TEST(24) TEST(25)

	dprintf(fd[2], "\n*** Mandatory tests %s ***\n\n", fail ? "failed" : "successful");

// bonus tests
	TEST(26) TEST(27) TEST(28) TEST(29) TEST(30) TEST(31) TEST(32) TEST(33) TEST(34)
	TEST(35) TEST(36) TEST(37) TEST(38) TEST(39) TEST(40) TEST(41) TEST(42) TEST(43)
	TEST(44) TEST(45) TEST(46) TEST(47) TEST(48) TEST(49) TEST(50) TEST(51) TEST(52)
	TEST(53) TEST(54) TEST(55) TEST(56) TEST(57) TEST(58) TEST(59) TEST(60) TEST(61)
	TEST(62) TEST(63) TEST(64) TEST(65) TEST(66) TEST(67) TEST(68) TEST(69) TEST(70)
	TEST(71) TEST(72) TEST(73) TEST(74) TEST(75) TEST(76) TEST(77) TEST(78) TEST(79)
	TEST(80) TEST(81) TEST(82) TEST(83) TEST(84) TEST(85) TEST(86) TEST(87) TEST(88)
	TEST(89) TEST(90) TEST(91) TEST(92) TEST(93) TEST(94) TEST(95) TEST(96) TEST(97)
	TEST(98) TEST(99) TEST(100) TEST(101)

	dprintf(fd[2], "\n*** Bonus tests %s ***\n", fail ? "failed" : "successful");

	if (silent)
	{
		fail = close(fd[0]) || fail;
		fail = close(fd[1]) || fail;
		fail = close(fd[2]) || fail;
	}

	return fail;
}
