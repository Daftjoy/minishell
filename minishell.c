#include <stdio.h>
#include <unistd.h>

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while(str[i])
		i++;
	return i;
}

int main ()
{
	char buffer[5];
	int	ret;

	write(1, "... ", 4);
	ret = read(0, buffer, 4);
	buffer[4] = '\0';
	write(1, buffer, ret);
	return 0;
}