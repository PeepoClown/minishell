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
int		ft_islowcase(int ch);
int		ft_isupcase(int ch);
int		ft_isdigit(int ch);
int		ft_isalpha(int ch);
int		ft_isalnum(int ch);
int		ft_atoi(const char *str);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);

#endif
