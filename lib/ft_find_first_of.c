#include <lib.h>

int		ft_find_first_of(const char *str, char sym)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == sym)
			return (i);
		i++;
	}
	return (-1);
}
