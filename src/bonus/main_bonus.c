/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:14:46 by yoonsele          #+#    #+#             */
/*   Updated: 2023/02/28 18:57:51 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	main(int ac, char **av, char **env)
{
	char	**path;
	t_data	data;

	if (ac < 5)
		ft_error_msg("Invalid number of arguments", __FILE_NAME__, __LINE__);
	data.number = ac - 3;

	data.cmd = (char **)malloc(sizeof(char *) * data.number);
	data.cmd_options = (char ***)malloc(sizeof(char **) * data.number);
	pipex_set(av, env, &data);
	pipex_execute(&data, env);
	return (EXIT_SUCCESS);
}
