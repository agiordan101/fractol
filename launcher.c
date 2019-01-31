#include "fractol.h"

int	main(int ac, char **av)
{
	int	i;
	char	*command;
	
	i = 0;
	if (ac > 1)
		while (++i < ac)
		{
			command = ft_strdup("./fractol ");
			command = ft_strcat(command, av[i]);
			system(command);
		}
	return (0);
}
