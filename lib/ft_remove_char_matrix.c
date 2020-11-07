#include <lib.h>

void	ft_remove_char_matrix(char **matrix)
{
	int		i;

	i = 0;
	if (!matrix)
		return ;
	while (matrix[i] != NULL)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}
