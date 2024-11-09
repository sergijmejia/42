/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtorrent <rtorrent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 03:47:31 by rtorrent          #+#    #+#             */
/*   Updated: 2024/09/30 03:12:12 by rtorrent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

// collection of tests for the ft_printf tester

// tests 0 through 25 verify compliance with the mandatory portion of the project

// test0: simple string literal
#define TEST00 "This is a test.\nA very good test!"

// test1: %c conversion specifier, print a single character
#define TEST01 "%c", 'r'
// test2: %s conversion specifier, print a string
#define TEST02 "%s", "hello, tester"
// test3: %s conversion specifier, print a string, NULL argument
#define TEST03 "%s", NULL
// test4: %p conversion specifier, print a (void *) pointer argument in hexadecimal
#define TEST04 "%p", &silent
// test5: %p conversion specifier, print a (void *) pointer, NULL argument
#define TEST05 "%p", NULL
// test6: %d conversion specifier, print a signed decimal integer, positive value
#define TEST06 "%d", 47321
// test7: %d conversion specifier, print a signed decimal integer, negative value
#define TEST07 "%d", -47321
// test8: %d conversion specifier, print a signed decimal integer, zero argument
#define TEST08 "%d", 0
// test9: %i conversion specifier, print a signed decimal integer, positive value
#define TEST09 "%i", 47321
// test10: %i conversion specifier, print a signed decimal integer, negative value
#define TEST10 "%i", -47321
// test11: %i conversion specifier, print a signed decimal integer, zero argument
#define TEST11 "%i", 0
// test12: %d & %i conversion specifiers, print numerical limits to signed decimal integers
#define TEST12 "%d %d %i %i", INT_MIN, INT_MAX, INT_MIN, INT_MAX
// test13: %u conversion specifier, print an unsigned decimal integer, positive value
#define TEST13 "%u", 47321
// test14: %u conversion specifier, print an unsigned decimal integer, negative value
#define TEST14 "%u", -47321
// test15: %u conversion specifier, print an unsigned decimal integer, zero argument
#define TEST15 "%u", 0
// test16: %x conversion specifier, print a lowercase hexadecimal integer, positive value
#define TEST16 "%x", 47321
// test17: %x conversion specifier, print a lowercase hexadecimal integer, negative value
#define TEST17 "%x", -47321
// test18: %x conversion specifier, print a lowercase hexadecimal integer, zero argument
#define TEST18 "%x", 0
// test19: %X conversion specifier, print an uppercase hexadecimal integer, positive value
#define TEST19 "%X", 47321
// test20: %X conversion specifier, print an uppercase hexadecimal integer, negative value
#define TEST20 "%X", -47321
// test21: %X conversion specifier, print an uppercase hexadecimal integer, zero argument
#define TEST21 "%X", 0
// test22: %u, %x & %X conversion specifiers, print numerical limits to unsigned decimal integers
#define TEST22 "%u %x %X", UINT_MAX, UINT_MAX, UINT_MAX
// test23: %% conversion specifier, print a percent sign
#define TEST23 "%%"

// test24: combination of string literal and various specifiers
#define TEST24 "%%%i is n\v w\nt %s rec%so%p to%c%x", -34567, "Alba", NULL, NULL, 42, 32463
// test25: combination of string literal and various specifiers
#define TEST25 "\ary%Xto-amohe %p\nYup, %d, go with %utoday", 4362111, &silent + 6, 0, 7560

// tests 26 through 101 verify compliance with the bonus portion of the project

// test26: field width, single character
#define TEST26 ">>%6c<< >>%1c<<", 'a', 'r'
// test27: field width, string
#define TEST27 ">>%8s<< >>%8s<< >>%2s<<", "one", "", "sixteen"
// test28: field width, string, NULL argument
#define TEST28 ">>%10s<< >>%2s<<", NULL, NULL
// test29: field width, print a (void *) pointer in hexadecimal
#define TEST29 ">>%12p<< >>%4p<<", &silent, &silent
// test30: field width, print a (void *) pointer, NULL argument
#define TEST30 ">>%10p<< >>%2p<<", NULL, NULL
// test31: field width, signed decimal integer
#define TEST31 ">>%6d<< >>%6d<< >>%6d<< >>%2d<<", 54, -54, 0, 12446
// test32: field width, signed decimal integer
#define TEST32 ">>%6i<< >>%6i<< >>%6i<< >>%2i<<", 46, -46, 0, 89024
// test33: field width, unsigned decimal integer
#define TEST33 ">>%6u<< >>%6u<< >>%6u<< >>%2u<<", 31, -31, 0, 43647
// test34: field width, lowercase hexadecimal integer
#define TEST34 ">>%6x<< >>%6x<< >>%6x<< >>%2x<<", 892, -892, 0, 20912
// test35: field width, uppercase hexadecimal integer
#define TEST35 ">>%6X<< >>%6X<< >>%6X<< >>%2X<<", 903, -903, 0, 46008
// test36: field width, print a percent sign
#define TEST36 ">>%4%<<"

// test37: precision, single character
#define TEST37 ">>%.0c<< >>%.1c<< >>%.2c<<", 'a', '+', 'r'
// test38: precision, string
#define TEST38 ">>%.2s<< >>%.4s<< >>%.6s<< >>%.8s<< >>%.s<<", "abcd", "efgh", "ijkl", "", ""
// test39: precision, string, NULL argument
#define TEST39 ">>%.3s<< >>%.6s<< >>%.10s<<", NULL, NULL, NULL
// test40: precision, print a (void *) pointer in hexadecimal
#define TEST40 ">>%.12p<< >>%.4p<<", &silent, &silent
// test41: precision, print a (void *) pointer, NULL argument
#define TEST41 ">>%.3p<< >>%.5p<< >>%.10p<< >>%.0p<<", NULL, NULL, NULL, NULL
// test42: precision, signed decimal integer
#define TEST42 ">>%.2d<< >>%.2d<< >>%.2d<< >>%.3d<< >>%.5d<< >>%.5d<< >>%.3d<<", 1783, 17, -17, -17, 17, -17, 0
// test43: zero precision, signed decimal integer
#define TEST43 ">>%.0d<< >>%.0d<< >>%.0d<< >>%.d<< >>%.d<<", 1783, 0, -4, 9006, 0
// test44: precision, signed decimal integer
#define TEST44 ">>%.2i<< >>%.2i<< >>%.2i<< >>%.3i<< >>%.5i<< >>%.5i<< >>%.3i<<", 1783, 17, -17, -17, 17, -17, 0
// test45: zero precision, signed decimal integer
#define TEST45 ">>%.0i<< >>%.0i<< >>%.0i<< >>%.i<< >>%.i<<", 1783, 0, -4, 9006, 0
// test46: precision, unsigned decimal integer
#define TEST46 ">>%.2u<< >>%.2u<< >>%.2u<< >>%.5u<< >>%.3u<<", 1783, 17, -17, 17, 0
// test47: zero precision, unsigned decimal integer
#define TEST47 ">>%.0u<< >>%.0u<< >>%.0u<< >>%.u<< >>%.u<<", 1783, 0, -4, 9006, 0
// test48: precision, lowercase hexadecimal integer
#define TEST48 ">>%.2x<< >>%.2x<< >>%.2x<< >>%.5x<< >>%.3x<<", 0xAc34,  0xa, -17, 0xC, 0
// test49: zero precision, lowercase hexadecimal integer
#define TEST49 ">>%.0x<< >>%.0x<< >>%.x<< >>%.x<<", 0xf3E1, 0, -1, 0
// test50: precision, uppercase hexadecimal integer
#define TEST50 ">>%.2X<< >>%.2X<< >>%.2X<< >>%.5X<< >>%.3X<<", 0xAc34,  0xa, -17, 0xC, 0
// test51: zero precision, uppercase hexadecimal integer
#define TEST51 ">>%.0X<< >>%.0X<< >>%.X<< >>%.X<<", 0xf3E1, 0, -1, 0
// test52: precision, print a percent sign
#define TEST52 ">>%.4%<< >>%.0%<< >>%.%<<"

// test53: field width and precision combinations, single character
#define TEST53 ">>%3.0c<< >>%4.1c<< >>%3.c<<", 'a', '+', 'r'
// test54: field width and precision combinations, string
#define TEST54 ">>%6.2s<< >>%6.4s<< >>%2.4s<< >>%2.6s<< >>%6.3s<< >>%2.s<<", "abcd", "efgh", "ijkl", "mnop", "", ""
// test55: field width and precision combinations, string, NULL argument
#define TEST55 ">>%10.7s<< >>%10.4s<< >>%4.8s<< >>%4.2s<<", NULL, NULL, NULL, NULL
// test56: field width and precision, print a (void *) pointer in hexadecimal
#define TEST56 ">>%12.20p<< >>%10.3p<< >>%2.4p<<", &silent, &silent, &silent
// test57: field width and precision, print a (void *) pointer, NULL argument
#define TEST57 ">>%8.6p<< >>%10.2p<< >>%3.10p<< >>%3.4p<<", NULL, NULL, NULL, NULL
// test58: field width and precision combinations, signed decimal integer
#define TEST58 ">>%6.2d<< >>%6.4d<< >>%5.2d<< >>%5.3d<< >>%2.5d<< >>%6.3d<< >>%4.3d<<", 1783, 17, -17, -17, 17, -17, 0
// test59: field width and precision combinations, zero precision, signed decimal integer
#define TEST59 ">>%5.0d<< >>%3.0d<< >>%1.0d<<", 1783, 0, 9006
// test60: field width and precision combinations, signed decimal integer
#define TEST60 ">>%6.2i<< >>%6.4i<< >>%5.2i<< >>%5.3i<< >>%2.5i<< >>%6.3i<< >>%4.3i<<", 1783, 17, -17, -17, 17, -17, 0
// test61: field width and precision combinations, zero precision, signed decimal integer
#define TEST61 ">>%5.0i<< >>%3.0i<< >>%1.i<<", 1783, 0, 9006
// test62: field width and precision combinations, unsigned decimal integer
#define TEST62 ">>%6.2u<< >>%6.4u<< >>%5.2u<< >>%2.5u<< >>%4.3u<<", 1783, 17, -17, 17, 0
// test63: field width and precision combinations, zero precision, unsigned decimal integer
#define TEST63 ">>%5.0u<< >>%3.0u<< >>%1.u<<", 1783, 0, 9006
// test64: field width and precision combinations, lowercase hexadecimal integer
#define TEST64 ">>%6.2x<< >>%6.4x<< >>%5.2x<< >>%2.5x<< >>%4.3x<<", 0x1eF3, 0X17, -17, 0x17, 0
// test65: field width and precision combinations, zero precision, lowercase hexadecimal integer
#define TEST65 ">>%5.0x<< >>%3.0x<< >>%1.x<<", 0XC7b3, 0, 0x9aB6
// test66: field width and precision combinations, uppercase hexadecimal integer
#define TEST66 ">>%6.2X<< >>%6.4X<< >>%5.2X<< >>%2.5X<< >>%4.3X<<", 0x1eF3, 0X17, -17, 0x17, 0
// test67: field width and precision combinations, zero precision, uppercase hexadecimal integer
#define TEST67 ">>%5.0X<< >>%3.0X<< >>%1.X<<", 0XC7b3, 0, 0x9aB6
// test68: field width and precision combinations, print a percent sign
#define TEST68 ">>%4.2%<< >>%2.4%<< >>%3.0%<<"

// test69: '#' flag, lowercase hexadecimal integer
#define TEST69 ">>%#6.4x<< >>%#3x<< >>%#x<< >>%#.x<< >>%#x", 0xaE, 0XF5, 0, 0, -53365
// test70: '#' flag, uppercase hexadecimal integer
#define TEST70 ">>%#6.4X<< >>%#3X<< >>%#X<< >>%#.X<< >>%#X", 0xaE, 0XF5, 0, 0, -53365

// test71: '0' flag, signed decimal integer
#define TEST71 ">>%04d<< >>%08.4d<< >>%04.8d<< >>%04d<< >>%03d<< >>%0.d", 28, 42, 42, -16, 0, 0
// test72: '0' flag, signed decimal integer
#define TEST72 ">>%04i<< >>%08.4i<< >>%04.8i<< >>%04i<< >>%03i<< >>%0.i", 28, 42, 42, -16, 0, 0
// test73: '0' flag, unsigned decimal integer
#define TEST73 ">>%04u<< >>%08.4u<< >>%04.8u<< >>%03u<< >>%0.u<<", 87, 23, 39, 0, 0
// test74: '0' flag, lowercase hexadecimal integer
#define TEST74 ">>%06.4x<< >>%06x<< >>%04.6x<< >>%03x<< >>%0.x<<", 0x9c, 0x9c, 0X1B, 0, 0
// test75: '0' flag, uppercase hexadecimal integer
#define TEST75 ">>%06.4X<< >>%06X<< >>%04.6X<< >>%03X<< >>%0.X<<", 0x9c, 0x9c, 0X1B, 0, 0

// test76: '-' flag, single character
#define TEST76 ">>%-4c<<", '$'
// test77: '-' flag, string
#define TEST77 ">>%-s<< >>%-6.3s<< >>%-6.s<< >>%-4.1s<<", "ABCD", "RSTU", "MNOP", ""
// test78: '-' flag, string, NULL argument
#define TEST78 ">>%-10.7s<< >>%-10.4s<< >>%-4.8s<< >>%-4.2s<<", NULL, NULL, NULL, NULL
// test79: '-' flag, print a (void *) pointer in hexadecimal
#define TEST79 ">>%-12.2p<< >>%-10.8p<< >>%-2.p<<", &silent, &silent, &silent 
// test80: '-' flag, print a (void *) pointer, NULL argument
#define TEST80 ">>%-8.6p<< >>%-10.2p<< >>%-3.10p<< >>%-3.4p<<", NULL, NULL, NULL, NULL
// test81: '-' flag, signed decimal integer
#define TEST81 ">>%-5d<< >>%-5.3d<< >>%-4d<< >>%-5.3d<< >>%-4.2d<<", 51, 50, -16, -16, 0
// test82: '-' & '0' flags, signed decimal integer
#define TEST82 ">>%0-4d<< >>%-0-d >>%-06d<< >>%--0.d<<", -16, 0, 261, 0
// test83: '-' flag, signed decimal integer
#define TEST83 ">>%-5i<< >>%-5.3i<< >>%-4i<< >>%-5.3i<< >>%-4.2i<<", 51, 50, -16, -16, 0
// test84: '-' & '0' flags, signed decimal integer
#define TEST84 ">>%0-4i<< >>%-0-i >>%-06i<< >>%--0.i<<", -16, 0, 261, 0
// test85: '-' flag, unsigned decimal integer
#define TEST85 ">>%-5u<< >>%-5.3u<< >>%-4u<< >>%-4.2u<<", 52, 52, -19, 0
// test86: '-' & '0' flags, unsigned decimal integer
#define TEST86 ">>%0-4u<< >>%-0-u >>%-06u<< >>%--0.u<<", 68, 0, 502, 0
// test87: '-' flag, lowercase hexadecimal integer
#define TEST87 ">>%-5x<< >>%-5.3x<< >>%-4x<< >>%-4.2x<<", 0xa3, 0XA3, -60, 0
// test88: '-' & '0' flags, lowercase hexadecimal integer
#define TEST88 ">>%0-4x<< >>%-0-x<< >>%-06x<< >>%--0.x<<", 0x68, 0, 0X5De, 0
// test89: '-' flag, uppercase hexadecimal integer
#define TEST89 ">>%-5X<< >>%-5.3X<< >>%-4X<< >>%-4.2X<<", 0xa3, 0XA3, -60, 0
// test90: '-' & '0' flags, uppercase hexadecimal integer
#define TEST90 ">>%0-4X<< >>%-0-X<< >>%-06X<< >>%--0.X<<", 0x68, 0, 0X5De, 0
// test91: '-' flag, print a percent sign
#define TEST91 ">>%-%<< >>%-4%<<"

// test92: ' ' flag, signed decimal integer
#define TEST92 ">>% d<< >>% 5.3d<< >>% 4d<< >>% d<< >>% 3.0d<< >>% .d<<", 47, 82, -36, 0, 0, 0
// test93: ' ' flag in combination with '0' & '-', signed decimal integer
#define TEST93 ">>% - 5.4d<< >>% -4d<< >>% -08d<< >>% -06d<< >>% 0-.d", 47, 82, -36, 0, 0
// test94: ' ' flag, signed decimal integer
#define TEST94 ">>% i<< >>% 5.3i<< >>% 4i<< >>% i<< >>% 3.0i<< >>% .i<<", 47, 82, -36, 0, 0, 0
// test95: ' ' flag in combination with '0' & '-', signed decimal integer
#define TEST95 ">>% - 5.4i<< >>% -4i<< >>% -08i<< >>% -06i<< >>% 0-.i", 47, 82, -36, 0, 0

// test96: '+' flag, signed decimal integer
#define TEST96 ">>%+d<< >>%+5.3d<< >>%+4d<< >>%+d<< >>%+3.0d<< >>%+.d<<", 58, 51, -16, 0, 0, 0
// test97: '+' flag in combination with '0' & '-', signed decimal integer
#define TEST97 ">>%+-+5.4d<< >>%+-4d<< >>%+-08d<< >>%+-06d<< >>%+0-.d", 58, 51, -16, 0, 0
// test98: '+' & ' ' flags, signed decimal integer
#define TEST98 ">>%+ d<< >>% +5.3d<< >>%+ 4d<< >>% +d<< >>%+ +3.0d<< >>% +.d<<", 58, 51, -16, 0, 0, 0
// test99: '+' flag, signed decimal integer
#define TEST99 ">>%+i<< >>%+5.3i<< >>%+4i<< >>%+i<< >>%+3.0i<< >>%+.i<<", 58, 51, -16, 0, 0, 0
// test100: '+' flag in combination with '0' & '-', signed decimal integer
#define TEST100 ">>%+-+5.4i<< >>%+-4i<< >>%+-08i<< >>%+-06i<< >>%+0-.i", 58, 51, -16, 0, 0
// test101: '+' & ' ' flags, signed decimal integer
#define TEST101 ">>%+ i<< >>% +5.3i<< >>%+ 4i<< >>% +i<< >>%+ +3.0i<< >>% +.i<<", 58, 51, -16, 0, 0, 0
