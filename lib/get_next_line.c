#include "lib.h"

static char	*ft_strjoin_gnl(char *s1, const char *s2)
{
	int		i;
	int		j;
	char	*sj;

	i = -1;
	j = -1;
	if (!s1)
		return (NULL);
	sj = (char*)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (sj == NULL)
		return (NULL);
	while (s1[++i] != '\0')
		sj[i] = s1[i];
	while (s2[++j] != '\0')
		sj[i++] = s2[j];
	sj[i] = '\0';
	free(s1);
	return (sj);
}

int			get_next_line(int fd, char **line)
{
	char buffer[2];

	if (!(*line = (char *)malloc(sizeof(char))))
		return (-1);
	**line = '\0';
	while (read(fd, buffer, 1) > 0)
	{
		buffer[1] = '\0';
		if (*buffer == '\n')
			return (1);
		if (!(*line = ft_strjoin_gnl(*line, buffer)))
			return (-1);
	}
	return (0);
}
