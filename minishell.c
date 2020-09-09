#include <stdio.h>
#include <unistd.h>


int readline(char **argv)
{
	printf("%s", argv[1]);
	return (0);
}


int main (int argc, char **argv)
{
	if (argc > 1)
	{
		readline(argv);
	}
	return 0;
}