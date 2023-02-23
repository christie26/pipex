#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/src/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_data {
	char	*cmd1;
	char	*cmd2;
	char	**cmd_options1;
	char	**cmd_options2;
}	t_data;

// handle error 
void	ft_error_msg(char *error_message, char *filename, int line);
void	ft_handle_syscall(char *filename, int line);

int		pipex_set(char **av, char **env, t_data *data);

#endif
