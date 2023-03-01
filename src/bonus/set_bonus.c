/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:14:36 by yoonsele          #+#    #+#             */
/*   Updated: 2023/03/01 18:18:42 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex_bonus.h"
#include <stdlib.h>

void	get_path(char **env, char ***path)
{
	int		i;
	char	*tmp;

	while (*env++)
	{
		if (!ft_strncmp(*env, "PATH", 4))
			break ;
	}
	*path = ft_split((*env + 5), ':');
	ft_err_msg(!(*path), "Fail to malloc();", __FILE__, __LINE__);
	i = 0;
	while ((*path)[i])
	{
		tmp = (*path)[i];
		(*path)[i] = ft_strjoin((*path)[i], "/");
		ft_err_msg(!(*path)[i], "Fail to malloc();", __FILE__, __LINE__);
		free(tmp);
		i++;
	}
}

void	get_cmd(t_data *data, char **av)
{
	int	i;

	i = 0;
	while (i < data->number)
	{
		data->cmd_options[i] = ft_split(av[i + 2], ' ');
		ft_err_msg(!data->cmd_options[i], "Fail to malloc();", \
				__FILE__, __LINE__);
		data->cmd[i] = data->cmd_options[i][0];
		i++;
	}
}

char	*check_access(char *cmd, char **path)
{
	int		i;
	char	*path_cmd;

	i = 0;
	if (access(cmd, X_OK) == 0)
		return (cmd);
	while (path[i])
	{
		path_cmd = ft_strjoin(path[i], cmd);
		ft_err_msg(!path_cmd, "Fail to malloc();", __FILE__, __LINE__);
		if (access(path_cmd, X_OK) == 0)
			return (path_cmd);
	i++;
	}
	return (0);
}

void	get_path_cmd(t_data *data, char **path)
{
	char	*tmp;
	int		i;

	i = 0;
	while (i < data->number)
	{
		tmp = data->cmd[i];
		data->cmd[i] = check_access(data->cmd[i], path);
		ft_err_msg(!(data->cmd[i]), "Invalid command !", __FILE__, __LINE__);
		free(tmp);
		i++;
	}
}

int	pipex_set(char **av, char **env, t_data *data)
{
	char	**path;

	get_path(env, &path);
	data->infile = av[1];
	data->outfile = av[data->number + 2];
	get_cmd(data, av);
	get_path_cmd(data, path);
	return (0);
}
