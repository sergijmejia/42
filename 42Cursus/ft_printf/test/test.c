#include "libftprintf.h"

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
	printed_printf = printf("Diferentes casos de d = -3704998 con    printf: %%d: %d , %%15d: %15d , %%015d: %015d , %%0+15d: %0+15d , %%0 15d: %0 15d , %%15.10d: %15.10d , %%-d: %-d , %%-15d: %-15d , %%-15.10d: %-15.10d , %%-+15.10d: %-+15.10d , %%- 15.10d: %- 15.10d  , %%- 15.d: %- 15.d.", d_n, d_n, d_n, d_n, d_n, d_n, d_n, d_n, d_n, d_n, d_n, d_n);
        printf(" La cantidad de caracteres impreso es %d\n", printed_printf);
        printed_ft_printf = ft_printf("Diferentes casos de d = -3704998 con ft_printf: %%d: %d , %%15d: %15d , %%015d: %015d , %%0+15d: %0+15d , %%0 15d: %0 15d , %%15.10d: %15.10d , %%-d: %-d , %%-15d: %-15d , %%-15.10d: %-15.10d , %%-+15.10d: %-+15.10d , %%- 15.10d: %- 15.10d  , %%- 15.d: %- 15.d.", d_n, d_n, d_n, d_n, d_n, d_n, d_n, d_n, d_n, d_n, d_n, d_n);
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
	return (0);
}
