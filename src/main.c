
#include "../include/pipex.h"

int	main(int ac, char **av, char **env)
{
	if (ac != 5)
		ft_error("invalid number of arguments\n");	
	set_path(av, env);
//	execute_command();
	(void)(av);
	(void)(env);
}
