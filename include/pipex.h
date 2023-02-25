#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/src/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# define READ 0
# define WRITE 1

typedef struct s_data {
	char	*cmd1;
	char	*cmd2;
	char	**cmd_options1;
	char	**cmd_options2;
	char	*path_cmd1;
	char	*path_cmd2;
	int		infile_fd;
	int		outfile_fd;
}	t_data;

// handle error 
void	ft_error_msg(char *error_message, char *filename, int line);
void	ft_error_syscall(char *filename, int line);

// set path and check accessibility
int		pipex_set(char **av, char **env, t_data *data);

// fork and execute 
int		pipex_execute(t_data *data, char **env);

#endif
