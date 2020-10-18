#include "minishell.h"

char	*add_to_str(char *str, char c)
{
	int		i = 0;
	char	*res;

	res = (char*)malloc((ft_strlen(str) + 2) * sizeof(char));
	while (i < ft_strlen(str))
	{
		res[i] = str[i];
		i++;
	}
	res[i++] = c;
	res[i] = '\0';
	if (str)
		free(str);
	return (res);
}

char	*user_input(void)
{
	char	*input;
	char	buff[1];
	int		read_res;

	input = ft_strdup("");
	while ((read_res = read(0, buff, 1)) != 0)
	{
		if (buff[0] == '\n')
			break ;
		input = add_to_str(input, buff[0]);
	}
	input = add_to_str(input, '\0');
	if (read_res < 0)
	{
		free(input);
		input = NULL;
	}
	return (input);
}
