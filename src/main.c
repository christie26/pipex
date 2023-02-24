/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 16:14:46 by yoonsele          #+#    #+#             */
/*   Updated: 2023/02/24 18:01:03 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <stdlib.h>

int	main(int ac, char **av, char **env)
{
	char	**path;
	t_data	data;

	if (ac != 5)
		ft_error_msg("Invalid number of arguments", __FILE_NAME__, __LINE__);
	pipex_set(av, env, &data);
	execute_command(&data, env);
	return (EXIT_SUCCESS);
}
