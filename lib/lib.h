/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wupdegra <wupdegra@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 18:33:17 by qcraghas          #+#    #+#             */
/*   Updated: 2020/11/08 17:16:00 by wupdegra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

# include <stdlib.h>
# include <unistd.h>

size_t				ft_strlen(const char *str);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strdup(const char *str);
char				*ft_substr(const char *s, int start, size_t len);
int					ft_find_first_of(const char *str, char sym);
void				ft_putstr_fd(const char *s, int fd);
void				ft_putendl_fd(int fd);
void				ft_putnbr_fd(int n, int fd);
int					ft_islowcase(int ch);
int					ft_isupcase(int ch);
char				*ft_itoa(int n);
int					ft_isdigit(int ch);
int					ft_isalpha(int ch);
int					ft_isalnum(int ch);
int					ft_atoi(const char *str);
char				*ft_strcpy(char *dest, char *src);
char				*ft_strjoin(char const *s1, char const *s2);
char				**ft_split(char const *s, char c);
char				*ft_strtrim(char *s1, char const *set);
char				*ft_strchr(const char *s, int c);
void				ft_remove_char_matrix(char **matrix);
char				**ft_copy_char_matrix(char **matrix, int row);
unsigned long long	ft_atoll(const char *str);
char				*str_to_lower(char *s);

#endif
