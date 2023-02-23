/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:14:36 by yoonsele          #+#    #+#             */
/*   Updated: 2023/02/23 17:10:30 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <sys/unistd.h>

char **get_path(char **env)
{
	int		i;
	char	*all_path;
	char	**path;
	char	*tmp;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH", 4))
			break;
		i++;
	}
	all_path = env[i] + 5;
	path = ft_split(all_path, ':');
	i = 0;
	while (path[i])
	{
		tmp = path[i];
		path[i] = ft_strjoin(path[i], "/");
		free(tmp);
		i++;
	}
	return (path);
}

void	get_cmd(t_data *data, char **av)
{
	int		i;

	data->cmd_options1 = ft_split(av[2], ' ');
	data->cmd_options2 = ft_split(av[3], ' ');
	data->cmd1 = data->cmd_options1[0];
	data->cmd2 = data->cmd_options2[0];

//	printf("cmd1 = %s\ncmd2 = %s\n", data->cmd1, data->cmd2);
}

char	*check_access(char *cmd, char **path)
{
	int		i;
	char	*path_with_cmd;

	i = 0;
	while (path[i])
	{
		path_with_cmd = ft_strjoin(path[i], cmd);
		printf("path_with_cmd = %s\n", path_with_cmd);
		if (access(path_with_cmd, X_OK) == 1)
			return (path_with_cmd);
	i++;
	}
	return (0);
}

int	pipex_set(char **av, char **env, t_data *data)
{
	char	**path;
	char	*path_with_cmd1;
	char	*path_with_cmd2;
	int		infile_fd;

	// get path from env
	path = get_path(env);


	// open input file
	infile_fd = open(av[1], O_RDONLY);
	if (infile_fd == -1)
		ft_handle_syscall(__FILE_NAME__, __LINE__);
//	printf("success to open\n");


	// get cmd from arguments
	get_cmd(data, av);


	// check accessibility of cmd
	path_with_cmd1 = check_access(data->cmd1, path);
	path_with_cmd2 = check_access(data->cmd2, path);

	printf("%s\n%s\n", path_with_cmd1, path_with_cmd2);
	return (0);
}

