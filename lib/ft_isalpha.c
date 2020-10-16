#include <lib.h>

int		ft_isalpha(int ch)
{
	return (ft_islowcase(ch) || ft_isupcase(ch));
}
