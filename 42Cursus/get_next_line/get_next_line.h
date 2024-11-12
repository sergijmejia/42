#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);
int		ft_check_end_line(const char *str);
char	*ft_strdup(const char *s);
size_t	ft_strlen(char *str);
void	*ft_memcpy(void *dest, const void *src, size_t n);

#endif
