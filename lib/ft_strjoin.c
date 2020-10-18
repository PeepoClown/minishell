#include <lib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	char	*tmp1;
	char	*tmp2;

	tmp1 = !s1 ? ft_strdup("") : ft_strdup(s1);
	tmp2 = !s2 ? ft_strdup("") : ft_strdup(s2);
	str = (char*)malloc(sizeof(char) * (ft_strlen(tmp1) +
				ft_strlen(tmp2) + 1));
	if (!str)
		return (NULL);
	ft_strcpy(str, tmp1);
	ft_strcpy(str + ft_strlen(tmp1), tmp2);
	*(str + ft_strlen(tmp1) + ft_strlen(tmp2)) = '\0';
	free(tmp1);
	free(tmp2);
	return (str);
}
