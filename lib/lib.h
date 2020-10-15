#ifndef __LIB_H__
# define __LIB_H__

# include <stdlib.h>
# include <unistd.h>

size_t	ft_strlen(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *str);
char	*ft_substr(const char *s, int start, size_t len);
int		ft_find_first_of(const char *str, char sym);
void	ft_putstr_fd(const char *s, int fd);
void	ft_putendl_fd(int fd);

#endif
