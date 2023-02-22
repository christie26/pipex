#include "../include/pipex.h"

char **get_path(char **env)
{
	int		i;
	char	*all_path;
	char	**path;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH", 4))
			break;
		i++;
	}
	all_path = env[i] + 5;
//	printf("all_path\n->%s\n", all_path);
	path = ft_split (all_path, ':');	
	return (path);
}


void	set_path(char **av, char **env)
{
	char **path;

	path = get_path(env);
	if (!path)
		ft_error("invalid path\n");
	(void)(av);
}
