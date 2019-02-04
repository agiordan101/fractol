#include "fractol.h"

int	main(int ac, char **av)
{
	int	i;
	char	*exec;
	char	*input;

	i = 0;
	if (ac > 1)
		while (++i < ac)
		{
			exec = ft_strdup("./fractol ");
			input = ft_strdup(av[i]);
			//printf("%s\n%s\n", exec, input);
			system(ft_strcat(exec, input));
			ft_strdel(&exec);
			ft_strdel(&input);
		}
	return (0);
}
