#include <lib.h>

char	**ft_copy_char_matrix(char **matrix, int row)
{
	int		i;
	char	**res;

	if (!(res = (char**)malloc(sizeof(char*) * (row + 1))))
		return (NULL);
	i = 0;
	while (i < row)
	{
		res[i] = ft_strdup(matrix[i]);
		if (!res[i])
			return (NULL);
		i++;
	}
	res[i] = NULL;
	return (res);
}
