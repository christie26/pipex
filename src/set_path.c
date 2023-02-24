/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:14:36 by yoonsele          #+#    #+#             */
/*   Updated: 2023/02/24 14:55:19 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <stdlib.h>
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

int	get_cmd(t_data *data, char **av)
{
	int		i;

	data->cmd_options1 = ft_split(av[2], ' ');
	if (!data->cmd_options1)
		return (EXIT_FAILURE);
	data->cmd_options2 = ft_split(av[3], ' ');
	if (!data->cmd_options2)
		return (EXIT_FAILURE);
	data->cmd1 = data->cmd_options1[0];
	data->cmd2 = data->cmd_options2[0];
	return (EXIT_SUCCESS);
}

char	*check_access(char *cmd, char **path)
{
	int		i;
	char	*path_cmd;

	i = 0;
	while (path[i])
	{
		path_cmd = ft_strjoin(path[i], cmd);	// what if fail malloc here?
		if (access(path_cmd, X_OK) == 0)
			return (path_cmd);
	i++;
	}
	return (0);
}

int	get_path_cmd(t_data *data, char **path)
{
	char	*path_cmd;

	path_cmd = check_access(data->cmd1, path);
	if (!path_cmd)
		return (EXIT_FAILURE);
	data->path_cmd1 = path_cmd;
	path_cmd = check_access(data->cmd2, path);
	if (!path_cmd)
		return (EXIT_FAILURE);
	data->path_cmd2 = path_cmd;
	return (EXIT_SUCCESS);
}

int	pipex_set(char **av, char **env, t_data *data)
{
	char	**path;
	int		infile_fd;

	// get path from env
	path = get_path(env);


	// open input file
	infile_fd = open(av[1], O_RDONLY);
	if (infile_fd == -1)
		ft_handle_syscall(__FILE_NAME__, __LINE__);


	// get cmd from arguments
	if (get_cmd(data, av))
		ft_handle_syscall(__FILE_NAME__, __LINE__);


	// check accessibility of cmd
	if (get_path_cmd(data, path))
		ft_error_msg("Invalid command", __FILE_NAME__, __LINE__);

	printf("%s\n%s\n", data->path_cmd1, data->path_cmd2);
	return (0);
}

