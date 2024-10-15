# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
/*   libft_guia_funciones.c                             :+:      :+:    :+:   */
#                                                     +:+ +:+         +:+      #
#    By: sardomin <sardomin@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/23 19:52:18 by sardomin          #+#    #+#              #
/*   Updated: 2024/10/15 14:43:34 by smejia-a         ###   ########.fr       */
#                                                                              #
# *****************************************************************************#

int	ft_isalpha(int c)
{
	Recibe: un int
	Valida: si es un valor alfabetico (mayuscula o minuscula).
	Devuelve:
		1 si el valor es alfabetico
		0 si no lo es
}

void	ft_isdigit(int c)
{
	Recibe: un int
	Valida: si el int es un digito, es decir entre '0' y '9' ambos incl
	Devuelve: 
		1 si el valor es un digito
		0 si el valor no lo es	
}

int	ft_isalnum(int c)
{
	Recibe: un int
	Valida: si es un valor alphanumerico, combina las dos func. anteriores
	Devuelve:
		1 si el valor es alfanumerico
		0 si no lo es
}

int	ft_isascii(int c)
{
	Recibe: un int
	Valida: si es una variable 7 bits, es decir, valor entre 0 y 127
	Devuelve:
		1 si el valor esta entre 0 y 127
		0 si no lo es
}

int	ft_isprint(int c)
{
	Recibe: un int
	Valida: Si la variable tiene un valor entre 32 y 126
	Devuelve:
		1 si el valor esta entre 32 y 126
		0 si no lo es
}

size_t	ft_strlen(const char *str)
{
	Recibe: un const char *str
	Valida: calcula el len del array recibido por parametros		OJO: sin contar el '\0'
	Devuelve: un int, el len.
}

void	*ft_memset(void *s, int c, size_t n)
{
	OJO!: void *s -> no puede ser desreferenciado, hay que\
		convertir *s a un tipo unsigned char *
	Recibe:
		*s -> un puntero del bloque de memoria\
			que se desea rellenar
		 c -> el valor que deseas que tenga cada byte\
		 	del bloque de memoria
		 n -> cantidad de bytes a rellenar con el\
		 	valor de c
	Valida: rellena n espacios de memoria de *s, con el\
		valor de c.
	Devuelve: un puntero al bloque *s
}

void	ft_bzero(void *s, size_t n)
{
	OJO!: void *s -> no puede ser desreferenciado, hay que\
                convertir *s a un tipo unsigned char *
	Recibe:
		*s -> un puntero del bloque de memoria
	 	 n -> cantidad de bytes a borrar 
	Valida: borra n bytes del espacio de memoria de *s\
		sustituyendo el valor por '\0'.
	Devuelve: Nada, es de tipo void
}

void	ft_memcpy(void *dest, const void *src, size_t n)
{
	OJO!: void *dest, const void *src -> no puede ser\
	      desreferenciado, hay que convertir *s a un tipo\
	      unsigned char *
	      Las areas de memoria no deben superponerse
	Recibe: 
		*dest -> pointer donde se copiaran bytes
		*src  -> pointer de donde se copiaran bytes
		 n    -> numero de bytes a copiar
	Valida: copia n bytes del pointer *src en *dest
	Devuelve: poiner *dest;
}

void	*memmove(void *dest, const void *src, size_t n)
{
	Recibe: 
		*dest ->Un puntero que indica donde se va a copiar el\
		       	contenido
		*src -> Un puntero que indica de donde se va a copiar \
			el contenido
		n -> 	Numero de bytes que se deben copiar
	Valida: Copia un bloque de memoria de una ubicacion a otra, \
		incluso si se solapan, principal ventaja con memcpy que\
		no maneja bien la superposicion

	Devuelve: un puntero al area de memoria dest, es decir, *dest
	Superposicion: 
		*dest antes que *src -> copia de delante hacia atras
		*dest despues que *src -> copia de atras hacia delante
}

void	ft_strlcpy(char *dst, const char *src, size_t size)
{
	OJO: es mas robusta que strcpy porque comprueba que\
		dest tenga espacio suficiente para que se \
		copien los elementos y no haya desbordamiento
	
	Recibe: 
       		*dst -> puntero al destino donde copiaremos la\
			cadena
		*src -> puntero que apunta a la cadena que \
			copiaremos
		size -> el numero de bytes que copiaremos
	Valida: copiamos size elementos de src en dest
		OJO: size incluye el '\0', lo tenemos que anadir para \
			terminar dest. El bucle i < size - 1 
	Devuelve: 
		len de src (sin incluir '\0')
		si size es 0, no copia y devuelve len src

		En el caso de strcpy se retorna un puntero \
		a dest
}
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	OJO: es mas robusta que strcpy porque comprueba que\
                dest tenga espacio suficiente para que se \
                copien los elementos y no haya desbordamiento

        Recibe:
                *dst -> puntero al destino donde copiaremos la\
                        cadena
                *src -> puntero que apunta a la cadena que \
                        copiaremos
                size -> el numero de bytes que copiaremos
        Valida: (size > dst_len) -> concatena size valores de src en dst\
       			despues de los caracteres que ya tiene. 
		       OJO: size incluye el '\n' y siempre incorporamos el '\0'\
		       		al final de la cadena dst despues de concatenar
		(size <= dst_len) -> no concatena
        Devuelve: dst_len + src_len

int	ft_toupper(int c)
{
	Recibe: c -> un caracter
	Valida: si c  es una minuscula.
	Devuelve:
		si c es una minuscula -> el mismo caracter en mayusculas
		si c es una mayuscula -> el mismo caracter
}

int	ft_tolower(int c)
{
        Recibe: c -> un caracter
        Valida: si c  es una minuscula.
        Devuelve:
                si c es una mayuscula -> el mismo caracter en mimuscula
                si c es una minuscula -> el mismo caracter
}

char    *ft_strchr(const char *s, int c)
{
	OJO: const char... hay que convertir los valores para que sean iterables
	Recibe: un pointer de tipo const char s* y un caracter a buscar en\
                        la cadena c
        Valida: primera ocurrencia de c en la cadena s*
        Devuelve:
                si encuentra c -> pointer apuntando a c
                si no encuentra c -> NULL
                OJO: se tiene en cuenta el caracter '\0' de la cadena\
                        si c = '\0' -> pointer a '\0'
}


char	*ft_strrchr(const char *s, int c)
{
	Recibe: un pointer de tipo const char s* y un caracter a buscar en\
			la cadena c
	Valida: ultima ocurrencia de c en la cadena s*
	Devuelve:
		si encuentra c -> pointer apuntando a c
		si no encuentra c -> NULL
		OJO: se tiene en cuenta el caracter '\0' de la cadena\
	       		si c = '\0' -> pointer a '\0'
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	Recibe: un pointer *s1, un pointer *s2 y un valor no negativo n
	Valida: es igual que strcmp pero solo comprara los n primeros caracteres
	Devuelve: la diferencia entre los elementos s1[i] y s2[i] de los\
		n elementos comparados
}

void	*ft_memchr(const void *s, int c, size_t n)
{
	Recibe: puntero *s, n bytes iniciales a escanear del area de *s, \
		      para encontrar la primera instancia de c
	Valida: Busca un valor especifico en un bloque de memoria, incluido \
			el nulo
	Devuelve: un pointer al primer byte coincidente con c o NULL si no lo \
			encuentra
	Importante: diferencias con strschr:
		1. Proposito:
			- strchr: busca la primera aparicion de c en cadena \
					de caracteres terminada en '\0'.
			- memchr: busca cualquier dato en un bloque de memoria\
					incluido valores nulos
		2. Tipo de datos:
			-strchr: solo funciona con cadenas de caracteres que \
					acaban en '\0''
			-memchr: trabaja con cualquier dato binario. No se \
					detiene en '\0'.

		3. Finalizacion de la busqueda:
			- strchr: se detiene cuando encuentra c o '\0'
			- memchr: recorre hasta encontrar c o haber revisado \
					n bytes. No se detiene en un '\0'.

		4. Retorno:
			- strchr: pointer al primer caracter igual que c o NULL
			- memchr: pointer al prmer byte con valor igual c o NULL	
		5. Uso de cadenas vs binarios:
			-strchr: trabaja conn cadenas. Depende de c o '\0'
			-memchr: con memoria en general, incluye binarios.\
					no depende de '\0'
}

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
        Recibe: un pointer *s1, un pointer *s2 y un valor no negativo n
        Valida: es igual que strcmp pero solo comprara los n primeros caracteres
        Devuelve: la diferencia entre los elementos s1[i] y s2[i] de los\
                n elementos comparados

	Diferencias iguales con strncmp (caracteres frente a bytes, uno se\
			detiene en '\0' y el otro no...)
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
/* Valida si *little es nulo primero, despues recorres *big teniendo en cuenta el parametro de len y buscas coindidencia para iterar sobre little si la encuentra. Sabemos que ha encontrado little cuando despues de la coincidencia encuetra el final, el nulo. Entonces retornamos pointer de la 1º posicion de la coincidencia de big. Si no encuentra, devolvemos NULL*/

	Recibe: pointer *big, pointer *little y una longitud positiva len
	Valida: busca la cadena *little dentro de *big, con el limite de \
			len caracteres de busqueda en *big
	Devuelve:
		Si no encuentra a *little en *big dentro de len \
				caraceteres -> NULL
		Si lo encuentra dentro de len caracteres -> pointer al \
				inicio de esa subcadena
}

int		ft_atoi(const char *nptr)
{
/* Primero valida si el char comienza por un espacio para ignorarlo
   Después validaremos si el valor es nulo o alfanumerico -> NULL
   Comprobar el signo: se ignora el +
   Conversion: (se va haciendo por decenas, centenas, millares...)
	1. Elemento numerico
	2. Elemento numerico -> (1ºelemento * 10) + 2º elemento
*/
	Recibe: una cadena de caracteres
	Valida: convierte una cadena de carateres a numero entero. Es decir de \
			*char a int
	Devuelve:
		Retorna el int del *char convertido
		Retorna 0 si la cadena comienza por alfanumericos o esta vacia
	OJO: 	Ignora cadenas no numericas, ejem "123abc" solo convertira "123"
		Si la cadena es "123fr89" solo convertira "123"
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	OJO: hay que inicializar la memoria con valor de 0, por eso se utiliza\
		     ft_bzero(result, (nmemb * size)
	Recibe: Numero de elementos (nmemb)\
		Bytes de cada elementos (size)
	Valida: Reserva bytes de memoria: malloc(nmemb * size);
	Devuelve: 
		Pointer al espacio asignado
		Si nmemb o  size = 0 o error de proceso-> devuelve NULL
}

char	*ft_strdup(const char *s)
{
	Recibe:	una cadena a copiar
	Valida: asigna memoria a una nueva cadena para copiar en ella la \
		cadena *s. 
	       	La asignacion de memoria la hace con malloc
	Devuelve:
		Un puntero a la cadena creada
		NULL si da error la asignacion de memoria	
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	Recibe:
		*s -> (string desde la que crear la substring)
		start -> indice del caracter s desde donde empezer la substr
		len -> longitud máxima substr
	Valida: Reserva (con malloc(3)) y devuelve una substring de la string\
			 ’s’. La substring empieza desde el índice ’start’ y\
				tiene una longitud máxima ’len’
	Devuelve:
		Substr resultante o NULL si falla la reserva de memoria

}

char	*ft_strjoin(char const *s1, char const *s2)
{
	Recibe: una cadena s1 y otra cadena s2
	valida: concatenar s2 despues de la cadena existente s1
	Devuelve:
		Si malloc da error -> NULL
		Nueva string formada por la concatenacion de s1 y s2
}
char	*ft_strtrim(char const *s1, char const *set)
{
	Recibe: una cadena de caracteres *s1 y una cadena de caracteres *set
	Valida: 
		Desde el inicio de la cadena *s1, si el 1er elemento esta dentro\
			de la cadena *set no hay que imprimirlo, comprobamos el \
			siguiente
		Desde el final lo mismo
	Devuelve:
		La cadena resultante
}

char	**ft_split(char const *s, char c)
{
	Recibe: una cadena *s y un caracter c
	Valida: el caracter c es el que determina donde se separa la cadena en \
		subcadenas.
		La cadena de cada subarray debe tener el caracter '\0'
	Devuelve: 
		aray de nuevos strings resultantes de la separacion
		NULL si falla la reserva de memoria
}		

char	*ft_itoa(int n)
{
	Recibe: un entero que puede ser negativo tambien
	Valida: convertir el entero en una cadena char. El simbolo negativo se \
		debe incluir y el nulo al final de la nueva cadena
	Devuelve:
		La cadena que representa el entero
		NULL si falla la reserva de memoria
	Pasos a realizar: 
		1. Identificar cuantos digitos tiene el entero, incluyendo el \
		simbolo -. Caso especial n = 0, que debe devolver '0'.
		
		Caso A: numero negativo. Se debe anadir el simbolo a la cadena y\
	       	convertir el numero en positivo multiplicando (-1)
		
		Caso aparte: INT_MIN (valor minimo de un entero, que no puede \
				representarse en positivo multiplicando (-1)
		
		2. Reserva de memoria. Hay que anadir tambien el nulo del final\
	       	de la cadena.
		3. Convertir el digito en char, sumandole '0''
		4. Anadir el caracter nulo a la cadena.
		5. Manejar los casos especiales.
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	Recibe: cadena a iterar *s, la funcion a aplicar sobre cada caracter
	Valida: Aplica la funcion a cada caracter de la cadena, pasando su \
		indice como primer argumento y le propio caracter como segundo.
		Creamos nueva cadena con malloc para las sucesivas aplicaicones\
		de la funcion
	Devuelve: La cadena creada tras el uso correcto de f
		  NULL si la reserva de memoria falla
}

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	OJO: la funcion void (*f) recibe la direccion de cada elemento de *s! 
	Recibe: la cadena a iterar *s, la funcion a aplicar
	Valida:	A cada caracter de la string le aplica una funcion, dando como\
		parametro la funcion y la direccion del propio caracter, que \
		podra modificarse si es necesario
	Devuelve: Nada
}	
