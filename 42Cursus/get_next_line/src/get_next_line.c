

char	*get_next_line(int fd)
{
	ssize_t	readed_char;
	char	*str;
	char	buffer[BUFFER_SIZE];
	int		loop;
	size_t		count;


	loop = 1;
	str = NULL;
	count = COUNT_SIZE;
	while (loop)
	{
		readed_char = read(fd, buffer, count);
		if (readed_char == -1)
		{
			free(str);
			return (NULL);
		}
		if (readed_char == 0)
		{
			break;
		}
		



	}
	if(ft_strcontains((const char) buffer, '\n'))
	{
		//tengo que buscar la primera aparicion de \n y guardar todo hasta ese caracter en str y devolverlo.
		//No se debe perder el resto de la informacion del buffer porque esa info pertenecera a la
		//siguiente linea
	}
}
