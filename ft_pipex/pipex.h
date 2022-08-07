#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../libft/libft.h"


void	close_pipes(int *fd);

void	child_process(char **av, char **envp, int *fd);

void	parent_process(char **av, char **envp, int *fd);

void	process(char **av, char **envp);

void	free_double(char **tab);

char	**find_path(char **envp);

char	*find_cmdpath(char *cmd, char **envp);

void	execute(char *av, char **envp, int *fd);

#endif
