#include <lib.h>

char	*ft_strdup(const char *str)
{
	size_t	i;
	char	*copy;

	copy = (char*)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (copy == NULL)
		return (NULL);
	i = 0;
	while (i < ft_strlen(str))
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
