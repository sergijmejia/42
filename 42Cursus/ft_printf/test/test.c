#include "ft_printf.h"

int	main()
{
	char			c = 'c';
	char			*s = "HolaMundo";
	void			*p = s;
	int				d = 20025;
	int				d_0 = 0;
	int				d_n = -3704998;
	unsigned int	u = 123456;
	unsigned int	u_0 = 0;
	unsigned int	x = 654321;
	unsigned int	x_0 = 0;
	int				printed_printf;
	int				printed_ft_printf;
	int				result_ft_print;
	int				result_orig_print;

	printed_printf = printf("Diferentes casos de c con    printf: %%c: %c , %%-c: %-c , %%-10c: %-10c.", c, c, c);
	printf(" La cantidad de caracteres impreso es %d\n", printed_printf);
	printed_ft_printf = ft_printf("Diferentes casos de c con ft_printf: %%c: %c , %%-c: %-c , %%-10c: %-10c.", c, c, c);
	ft_printf(" La cantidad de caracteres impreso es %d\n", printed_ft_printf);
	printf("\n");
	printed_printf = printf("Diferentes casos de s con    printf: %%s: %s , %%-s: %-s , %%-15s: %-15s ,  %%-15.5s: %-15.5s.", s, s, s, s);
	printf(" La cantidad de caracteres impreso es %d\n", printed_printf);
	printed_ft_printf = ft_printf("Diferentes casos de s con ft_printf: %%s: %s , %%-s: %-s , %%-15s: %-15s ,  %%-15.5s: %-15.5s.", s, s, s, s);
	ft_printf(" La cantidad de caracteres impreso es %d\n", printed_ft_printf);
	printf("\n");
	printed_printf = printf("Diferentes casos de p con    printf: %%p: %p , %%-p: %-p , %%-10p: %-10p , %%-20p: %-20p.", p, p, p, p);
	printf(" La cantidad de caracteres impreso es %d\n", printed_printf);
	printed_ft_printf = ft_printf("Diferentes casos de p con ft_printf: %%p: %p , %%-p: %-p , %%-10p: %-10p , %%-20p: %-20p.", p, p, p, p);
	ft_printf(" La cantidad de caracteres impreso es %d\n", printed_ft_printf);
	printf("\n");
	
	
	
	
	printed_printf = printf("Diferentes casos de d = 20025 con    printf: %%d: %d , %%15d: %15d , %%015d: %015d , %%0+15d: %0+15d , %%0 15d: %0 15d , %%15.10d: %15.10d , %%-d: %-d , %%-15d: %-15d , %%-15.10d: %-15.10d , %%-+15.10d: %-+15.10d , %%- 15.10d: %- 15.10d  , %%- 15.d: %- 15.d.", d, d, d, d, d, d, d, d, d, d, d, d);
	printf(" La cantidad de caracteres impreso es %d\n", printed_printf);
	printed_ft_printf = ft_printf("Diferentes casos de d = 20025 con ft_printf: %%d: %d , %%15d: %15d , %%015d: %015d , %%0+15d: %0+15d , %%0 15d: %0 15d , %%15.10d: %15.10d , %%-d: %-d , %%-15d: %-15d , %%-15.10d: %-15.10d , %%-+15.10d: %-+15.10d , %%- 15.10d: %- 15.10d  , %%- 15.d: %- 15.d.", d, d, d, d, d, d, d, d, d, d, d, d);
	ft_printf(" La cantidad de caracteres impreso es %d\n", printed_ft_printf);
	printf("\n");
	printed_printf = printf("Diferentes casos de d = 0 con    printf: %%d: %d , %%15d: %15d , %%015d: %015d , %%0+15d: %0+15d , %%0 15d: %0 15d , %%15.10d: %15.10d , %%-d: %-d , %%-15d: %-15d , %%-15.10d: %-15.10d , %%-+15.10d: %-+15.10d , %%- 15.10d: %- 15.10d  , %%- 15.d: %- 15.d.", d_0, d_0, d_0, d_0, d_0, d_0, d_0, d_0, d_0, d_0, d_0, d_0);
        printf(" La cantidad de caracteres impreso es %d\n", printed_printf);
        printed_ft_printf = ft_printf("Diferentes casos de d = 0 con ft_printf: %%d: %d , %%15d: %15d , %%015d: %015d , %%0+15d: %0+15d , %%0 15d: %0 15d , %%15.10d: %15.10d , %%-d: %-d , %%-15d: %-15d , %%-15.10d: %-15.10d , %%-+15.10d: %-+15.10d , %%- 15.10d: %- 15.10d  , %%- 15.d: %- 15.d.", d_0, d_0, d_0, d_0, d_0, d_0, d_0, d_0, d_0, d_0, d_0, d_0);
        ft_printf(" La cantidad de caracteres impreso es %d\n", printed_ft_printf);
        printf("\n");
	printed_printf = printf("Diferentes casos de d = -3704998 con    printf: %%d: %d , %%15d: %15d , %%015d: %015d , %%0+15d: %0+15d , %%0 15d: %0 15d , %%15.10d: %15.10d , %%-d: %-d , %%-15d: %-15d , %%-15.10d: %-15.10d , %%-+15.10d: %-+15.10d , %%- 15.10d: %- 15.10d  , %%- 15.d: %- 15.d  , %%.8d: %.8d.", d_n, d_n, d_n, d_n, d_n, d_n, d_n, d_n, d_n, d_n, d_n, d_n, d_n);
        printf(" La cantidad de caracteres impreso es %d\n", printed_printf);
        printed_ft_printf = ft_printf("Diferentes casos de d = -3704998 con ft_printf: %%d: %d , %%15d: %15d , %%015d: %015d , %%0+15d: %0+15d , %%0 15d: %0 15d , %%15.10d: %15.10d , %%-d: %-d , %%-15d: %-15d , %%-15.10d: %-15.10d , %%-+15.10d: %-+15.10d , %%- 15.10d: %- 15.10d  , %%- 15.d: %- 15.d  , %%.8d: %.8d.", d_n, d_n, d_n, d_n, d_n, d_n, d_n, d_n, d_n, d_n, d_n, d_n, d_n);
        ft_printf(" La cantidad de caracteres impreso es %d\n", printed_ft_printf);
        printf("\n");


	printed_printf = printf("Diferentes casos de i = 20025 con    printf: %%i: %i , %%15i: %15i , %%015i: %015i , %%0+15i: %0+15i , %%0 15i: %0 15i , %%15.10i: %15.10i , %%-i: %-i , %%-15i: %-15i , %%-15.10i: %-15.10i , %%-+15.10i: %-+15.10i , %%- 15.10i: %- 15.10i.", d, d, d, d, d, d, d, d, d, d, d);
        printf(" La cantidad de caracteres impreso es %d\n", printed_printf);
        printed_ft_printf = ft_printf("Diferentes casos de i = 20025 con ft_printf: %%i: %i , %%15i: %15i , %%015i: %015i , %%0+15i: %0+15i , %%0 15i: %0 15i , %%15.10i: %15.10i , %%-i: %-i , %%-15i: %-15i , %%-15.10i: %-15.10i , %%-+15.10i: %-+15.10i , %%- 15.10i: %- 15.10i.", d, d, d, d, d, d, d, d, d, d, d);
        ft_printf(" La cantidad de caracteres impreso es %d\n", printed_ft_printf);
        printf("\n");
        printed_printf = printf("Diferentes casos de i = 0 con    printf: %%i: %i , %%15i: %15i , %%015i: %015i , %%0+15i: %0+15i , %%0 15i: %0 15i , %%15.10i: %15.10i , %%-i: %-i , %%-15i: %-15i , %%-15.10i: %-15.10i , %%-+15.10i: %-+15.10i , %%- 15.10i: %- 15.10i.", d_0, d_0, d_0, d_0, d_0, d_0, d_0, d_0, d_0, d_0, d_0);
        printf(" La cantidad de caracteres impreso es %d\n", printed_printf);
        printed_ft_printf = ft_printf("Diferentes casos de i = 0 con ft_printf: %%i: %i , %%15i: %15i , %%015i: %015i , %%0+15i: %0+15i , %%0 15i: %0 15i , %%15.10i: %15.10i , %%-d: %-i , %%-15i: %-15i , %%-15.10i: %-15.10i , %%-+15.10i: %-+15.10i , %%- 15.10i: %- 15.10i.", d_0, d_0, d_0, d_0, d_0, d_0, d_0, d_0, d_0, d_0, d_0);
        ft_printf(" La cantidad de caracteres impreso es %d\n", printed_ft_printf);
        printf("\n");
        printed_printf = printf("Diferentes casos de i = -3704998 con    printf: %%i: %i , %%15i: %15i , %%015i: %015i , %%0+15i: %0+15i , %%0 15i: %0 15i , %%15.10i: %15.10i , %%-i: %-i , %%-15i: %-15i , %%-15.10i: %-15.10i , %%-+15.10i: %-+15.10i , %%- 15.10i: %- 15.10i.", d_n, d_n, d_n, d_n, d_n, d_n, d_n, d_n, d_n, d_n, d_n);
        printf(" La cantidad de caracteres impreso es %d\n", printed_printf);
        printed_ft_printf = ft_printf("Diferentes casos de i = -3704998 con ft_printf: %%i: %i , %%15i: %15i , %%015i: %015i , %%0+15i: %0+15i , %%0 15i: %0 15i , %%15.10i: %15.10i , %%-i: %-i , %%-15i: %-15i , %%-15.10i: %-15.10i , %%-+15.10i: %-+15.10i , %%- 15.10i: %- 15.10i.", d_n, d_n, d_n, d_n, d_n, d_n, d_n, d_n, d_n, d_n, d_n);
	ft_printf(" La cantidad de caracteres impreso es %d\n", printed_ft_printf);
        printf("\n");


	printed_printf = printf("Diferentes casos de u = 123456 con    printf: %%u: %u , %%15u: %15u , %%015u: %015u , %%15.10u: %15.10u , %%-u: %-u , %%-15u: %-15u , %%-15.10u: %-15.10u.", u, u, u, u, u, u, u);
        printf(" La cantidad de caracteres impreso es %d\n", printed_printf);
        printed_ft_printf = ft_printf("Diferentes casos de u = 123456 con ft_printf: %%u: %u , %%15u: %15u , %%015u: %015u , %%15.10u: %15.10u , %%-u: %-u , %%-15u: %-15u , %%-15.10u: %-15.10u.", u, u, u, u, u, u, u);
        ft_printf(" La cantidad de caracteres impreso es %d\n", printed_ft_printf);
        printf("\n");
        printed_printf = printf("Diferentes casos de u = 0 con    printf: %%u: %u , %%15u: %15u , %%015u: %015u , %%15.10u: %15.10u , %%-u: %-u , %%-15u: %-15u , %%-15.10u: %-15.10u.", u_0, u_0, u_0, u_0, u_0, u_0, u_0);
	printf(" La cantidad de caracteres impreso es %d\n", printed_printf);
        printed_ft_printf = ft_printf("Diferentes casos de u = 0 con ft_printf: %%u: %u , %%15u: %15u , %%015u: %015u , %%15.10u: %15.10u , %%-u: %-u , %%-15u: %-15u , %%-15.10u: %-15.10u.", u_0, u_0, u_0, u_0, u_0, u_0, u_0);
        ft_printf(" La cantidad de caracteres impreso es %d\n", printed_ft_printf);
        printf("\n");


	printed_printf = printf("Diferentes casos de x = 654321 con    printf: %%x: %x , %%15x: %15x , %%015x: %015x , %%15.10x: %15.10x , %%-x: %-x , %%-15x: %-15x , %%-15.10x: %-15.10x , %%-#15.10x: %-#15.10x.", x, x, x, x, x, x, x, x);
        printf(" La cantidad de caracteres impreso es %d\n", printed_printf);
        printed_ft_printf = ft_printf("Diferentes casos de x = 654321 con ft_printf: %%x: %x , %%15x: %15x , %%015x: %015x , %%15.10x: %15.10x , %%-x: %-x , %%-15x: %-15x , %%-15.10x: %-15.10x , %%-#15.10x: %-#15.10x.", x, x, x, x, x, x, x, x);
        ft_printf(" La cantidad de caracteres impreso es %d\n", printed_ft_printf);
        printf("\n");
        printed_printf = printf("Diferentes casos de x = 0 con    printf: %%x: %x , %%15x: %15x , %%015x: %015x , %%15.10x: %15.10x , %%-x: %-x , %%-15x: %-15x , %%-15.10x: %-15.10x , %%-#15.10x: %-#15.10x.", x_0, x_0, x_0, x_0, x_0, x_0, x_0, x_0);
        printf(" La cantidad de caracteres impreso es %d\n", printed_printf);
        printed_ft_printf = ft_printf("Diferentes casos de x = 0 con ft_printf: %%x: %x , %%15x: %15x , %%015x: %015x , %%15.10x: %15.10x , %%-x: %-x , %%-15x: %-15x , %%-15.10x: %-15.10x , %%-#15.10x: %-#15.10x.", x_0, x_0, x_0, x_0, x_0, x_0, x_0, x_0);
        ft_printf(" La cantidad de caracteres impreso es %d\n", printed_ft_printf);
        printf("\n");


	printed_printf = printf("Diferentes casos de X = 654321 con    printf: %%X: %X , %%15X: %15X , %%015X: %015X , %%15.10X: %15.10X , %%-X: %-X , %%-15X: %-15X , %%-15.10X: %-15.10X , %%-#15.10X: %-#15.10X.", x, x, x, x, x, x, x, x);
        printf(" La cantidad de caracteres impreso es %d\n", printed_printf);
	printed_ft_printf = ft_printf("Diferentes casos de X = 654321 con ft_printf: %%X: %X , %%15X: %15X , %%015X: %015X , %%15.10X: %15.10X , %%-X: %-X , %%-15X: %-15X , %%-15.10X: %-15.10X , %%-#15.10X: %-#15.10X.", x, x, x, x, x, x, x, x);
	ft_printf(" La cantidad de caracteres impreso es %d\n", printed_ft_printf);
        printf("\n");
        printed_printf = printf("Diferentes casos de X = 0 con    printf: %%X: %X , %%15X: %15X , %%015X: %015X , %%15.10X: %15.10X , %%-X: %-X , %%-15X: %-15X , %%-15.10X: %-15.10X , %%-#15.10X: %-#15.10X.", x_0, x_0, x_0, x_0, x_0, x_0, x_0, x_0);
	printf(" La cantidad de caracteres impreso es %d\n", printed_printf);
        printed_ft_printf = ft_printf("Diferentes casos de X = 0 con ft_printf: %%X: %X , %%15X: %15X , %%015X: %015X , %%15.10X: %15.10X , %%-X: %-X , %%-15X: %-15X , %%-15.10X: %-15.10X , %%-#15.10X: %-#15.10X.", x_0, x_0, x_0, x_0, x_0, x_0, x_0, x_0);
	ft_printf(" La cantidad de caracteres impreso es %d\n", printed_ft_printf);
	printf("\n");

	printf("\n\n\n\n");
	printf("Test especiales de c. Primero en printf y luego en ft_printf:\n");
	printed_printf = printf(" %c %c %c ", '0', 0, '1');
	printf("\n");
	printed_ft_printf = ft_printf(" %c %c %c ", '0', 0, '1');
	printf("\n");
	printf("Los caracteres impresos con printf son %d y los impresos con ft_printf con %d", printed_printf, printed_ft_printf);

	printf("\n");
	printed_printf = printf(" %c %c %c ", '2', '1', 0);
        printf("\n");
        printed_ft_printf = ft_printf(" %c %c %c ", '2', '1', 0);
        printf("\n");
	printf("Los caracteres impresos con printf son %d y los impresos con ft_printf con %d", printed_printf, printed_ft_printf);


	printf("\n");
        printed_printf = printf(" %c %c %c ", 0, '1', '2');
        printf("\n");
        printed_ft_printf = ft_printf(" %c %c %c ", 0, '1', '2');
        printf("\n");
	printf("Los caracteres impresos con printf son %d y los impresos con ft_printf con %d", printed_printf, printed_ft_printf);


        printf("\n\n\n\n");
        printf("Test especial de mix. Primero en printf y luego en ft_printf:\n");
        printed_printf = printf("%%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %c%%", 'A', "42", 42, 42 ,42 , 42, 42, 'B', "-42", -42, -42 ,-42 ,-42, 42, 'C', "0", 0, 0 ,0 ,0, 42, 0);
        printf("\n");
        printed_ft_printf = ft_printf("%%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %c%%", 'A', "42", 42, 42 ,42 , 42, 42, 'B', "-42", -42, -42 ,-42 ,-42, 42, 'C', "0", 0, 0 ,0 ,0, 42, 0);
        printf("\n");
        printf("Los caracteres impresos con printf son %d y los impresos con ft_printf con %d", printed_printf, printed_ft_printf);



	printf("\n\n\n\n");
        printf("Test especial de '.'. Primero en printf y luego en ft_printf:\n");
        printed_printf = printf(" %.2d ", -1);
        printf("\n");
        printed_ft_printf = ft_printf(" %.2d ", -1);
        printf("\n");
        printf("Los caracteres impresos con printf son %d y los impresos con ft_printf con %d", printed_printf, printed_ft_printf);

	printf("\n");
        printed_printf = printf(" %.3d ", -99);
        printf("\n");
        printed_ft_printf = ft_printf(" %.3d ", -99);
        printf("\n");
        printf("Los caracteres impresos con printf son %d y los impresos con ft_printf con %d", printed_printf, printed_ft_printf);

	printf("\n");
        printed_printf = printf(" %.4d ", -101);
        printf("\n");
        printed_ft_printf = ft_printf(" %.4d ", -101);
        printf("\n");
        printf("Los caracteres impresos con printf son %d y los impresos con ft_printf con %d", printed_printf, printed_ft_printf);


	printf("\n\n\n\n");
        printf("Test especial de '%%' unico. Primero en printf y luego en ft_printf:\n");
        printed_printf = printf("%");
        printf("\n");
        printed_ft_printf = ft_printf("%");
        printf("\n");
        printf("Los caracteres impresos con printf son %d y los impresos con ft_printf con %d", printed_printf, printed_ft_printf);

/*	printf("\n");
	printed_printf = printf("Prueba de fallo % -0 %d   q. Imprime?", d);
        printf("\n");
        printed_ft_printf = ft_printf("Prueba de fallo % -0 %d   q. Imprime?", d);
        printf("\n");
        printf("Los caracteres impresos con printf son %d y los impresos con ft_printf con %d", printed_printf, printed_ft_printf);

	printf("\n");
        printed_printf = printf("Prueba de fallo % -0 que aparecera en el print%d   q. Imprime?", d);
        printf("\n");
        printed_ft_printf = ft_printf("Prueba de fallo % -0 que aparecera en el print%d   q. Imprime?", d);
        printf("\n");
        printf("Los caracteres impresos con printf son %d y los impresos con ft_printf con %d", printed_printf, printed_ft_printf);*/

	printf("\n");
        printed_printf = printf("Prueba de fallo %");
        printf("\n");
        printed_ft_printf = ft_printf("Prueba de fallo %");
        printf("\n");
        printf("Los caracteres impresos con printf son %d y los impresos con ft_printf con %d", printed_printf, printed_ft_printf);



	printf("\n\n\n\n");
	printf("Test de Alao:\n");
	result_ft_print = ft_printf("Character test: %c\n", 'A');
	result_orig_print = printf("Character test: %c\n", 'A');
	printf("ft_printf size: %d, printf size: %d\n", result_ft_print, result_orig_print);

	result_ft_print = ft_printf("String test: %s\n", "Hello World");
	result_orig_print = printf("String test: %s\n", "Hello World");
	printf("ft_printf size: %d, printf size: %d\n", result_ft_print, result_orig_print);

	result_ft_print = ft_printf("Pointer test: %p\n", (void *)0);
	result_orig_print = printf("Pointer test: %p\n", (void *)0);
	printf("ft_printf size: %d, printf size: %d\n", result_ft_print, result_orig_print);

	result_ft_print = ft_printf("Decimal test %%d: %d\n", 42);
	result_orig_print = printf("Decimal test %%d: %d\n", 42);
	printf("ft_printf size: %d, printf size: %d\n", result_ft_print, result_orig_print);

	result_ft_print = ft_printf("Integer test %%i: %i\n", -42);
	result_orig_print = printf("Integer test %%i: %i\n", -42);
	printf("ft_printf size: %d, printf size: %d\n", result_ft_print, result_orig_print);

	result_ft_print = ft_printf("Unsigned test: %u\n", 3000000000u);
	result_orig_print = printf("Unsigned test: %u\n", 3000000000u);
	printf("ft_printf size: %d, printf size: %d\n", result_ft_print, result_orig_print);

	result_ft_print = ft_printf("Hexadecimal test %%x: %x\n", 255);
	result_orig_print = printf("Hexadecimal test %%x: %x\n", 255);
	printf("ft_printf size: %d, printf size: %d\n", result_ft_print, result_orig_print);

	result_ft_print = ft_printf("Hexadecimal test %%X: %X\n", 255);
	result_orig_print = printf("Hexadecimal test %%X: %X\n", 255);
	printf("ft_printf size: %d, printf size: %d\n", result_ft_print, result_orig_print);

	result_ft_print = ft_printf("Percentage test: %%\n");
	result_orig_print = printf("Percentage test: %%\n");
	printf("ft_printf size: %d, printf size: %d\n", result_ft_print, result_orig_print);

	result_ft_print = ft_printf("Zero test: %d\n", 0);
	result_orig_print = printf("Zero test: %d\n", 0);
	printf("ft_printf size: %d, printf size: %d\n", result_ft_print, result_orig_print);

	result_ft_print = ft_printf("Smallest int test: %d\n", -2147483648);
	result_orig_print = printf("Smallest int test: %d\n", (int)-2147483648);
	printf("ft_printf size: %d, printf size: %d\n", result_ft_print, result_orig_print);

	result_ft_print = ft_printf("Empty string test: %s\n", "");
	result_orig_print = printf("Empty string test: %s\n", "");
	printf("ft_printf size: %d, printf size: %d\n", result_ft_print, result_orig_print);

	result_ft_print = ft_printf("NULL pointer test: %p\n", NULL);
	result_orig_print = printf("NULL pointer test: %p\n", NULL);
	printf("ft_printf size: %d, printf size: %d\n", result_ft_print, result_orig_print);

	result_ft_print = ft_printf("Multiple: %d, %s, %c, %x\n", 42, "Hello", 'B', 255);
	result_orig_print = printf("Multiple: %d, %s, %c, %x\n", 42, "Hello", 'B', 255);
	printf("ft_printf size: %d, printf size: %d\n", result_ft_print, result_orig_print);

	result_ft_print = ft_printf("Largest unsigned int: %u\n", 4294967295u);
	result_orig_print = printf("Largest unsigned int: %u\n", 4294967295u);
	printf("ft_printf size: %d, printf size: %d\n", result_ft_print, result_orig_print);

	result_ft_print = ft_printf("Largest int: %d\n", 2147483647);
	result_orig_print = printf("Largest int: %d\n", 2147483647);
	printf("ft_printf size: %d, printf size: %d\n", result_ft_print, result_orig_print);

	printf("\n=== Combinações Complexas ===\n");

	result_ft_print = ft_printf("Mixed: %d, %s, %c, %x, %u, %p, %%\n", 123, "test", 'Z', 456, 789u, (void *)0x42);
	result_orig_print = printf("Mixed: %d, %s, %c, %x, %u, %p, %%\n", 123, "test", 'Z', 456, 789u, (void *)0x42);
	printf("ft_printf size: %d, printf size: %d\n\n", result_ft_print, result_orig_print);

	printf("\n=== Sequência de Conversões Idênticas ===\n");

	result_ft_print = ft_printf("Repeated int: %d %d %d %d\n", 1, -1, 2147483647, -2147483648);
	result_orig_print = printf("Repeated int: %d %d %d %d\n", 1, -1, 2147483647, (int)-2147483648);
	printf("ft_printf size: %d, printf size: %d\n\n", result_ft_print, result_orig_print);

	result_ft_print = ft_printf("Repeated char: %c %c %c %c\n", 'A', 'B', 'C', 'D');
	result_orig_print = printf("Repeated char: %c %c %c %c\n", 'A', 'B', 'C', 'D');
	printf("ft_printf size: %d, printf size: %d\n\n", result_ft_print, result_orig_print);

	result_ft_print = ft_printf("Repeated pointer: %p %p %p %p\n", (void *)0, (void *)0x1, (void *)0xFFFF, (void *)0xFFFFFFFF);
	result_orig_print = printf("Repeated pointer: %p %p %p %p\n", (void *)0, (void *)0x1, (void *)0xFFFF, (void *)0xFFFFFFFF);
	printf("ft_printf size: %d, printf size: %d\n\n", result_ft_print, result_orig_print);

	printf("\n=== Casos Extremos ===\n");

	result_ft_print = ft_printf("Extreme unsigned int: %u %u %u\n", 0u, 1u, 4294967295u);
	result_orig_print = printf("Extreme unsigned int: %u %u %u\n", 0u, 1u, 4294967295u);
	printf("ft_printf size: %d, printf size: %d\n\n", result_ft_print, result_orig_print);

	result_ft_print = ft_printf("Extreme int: %d %d %d\n", -2147483648, 0, 2147483647);
	result_orig_print = printf("Extreme int: %d %d %d\n",(int) -2147483648, 0, 2147483647);
	printf("ft_printf size: %d, printf size: %d\n\n", result_ft_print, result_orig_print);

	printf("=== Testes completos para o ft_printf ===\n");




	return (0);
}
