/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 19:25:17 by rvrignon          #+#    #+#             */
/*   Updated: 2022/08/18 02:10:44 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex_bonus.h"

void	free_double(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	check_path(char **envp)
{
	char	**paths;
	int		value;

	paths = find_path(envp);
	if (!paths)
	{	
		ft_printf("Env error\n");
		value = 0;
	}
	else
	{
		free_double(paths);
		value = 1;
	}
	return (value);
}


char	**find_path(char **envp)
{
	int		i;
	char	**paths;

	if (!envp[0])
		return (NULL);
	i = 0;
	while (envp[i + 1] && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	if (ft_strnstr(envp[i], "PATH", 4) == 0)
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	return (paths);
}

char	*find_cmdpath(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	paths = find_path(envp);
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	free_double(paths);
	return (0);
}

void	execute(char *av, char **envp)
{
	char	**cmd;
	int		i;
	char	*path;
	char	*err;

	i = -1;
	cmd = ft_split(av, ' ');
	if (access(cmd[0], F_OK) == 0)
		path = cmd[0];
	else
		path = find_cmdpath(cmd[0], envp);
	if (!path)
	{
		err = ft_strjoin(cmd[0], ": Command not found\n");
		ft_putstr_fd(err, 2);
		free(err);
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		exit(EXIT_FAILURE);
	}
	if (execve(path, cmd, envp) == -1)
	{
		fprintf(stderr, "Failed to execute 'wc'\n");
		exit(EXIT_FAILURE);
	}
}

t_pipex	*set_pipex(int ac, char **av, char **envp)
{
	t_pipex *pipex;

	pipex = (t_pipex *)malloc(sizeof(t_pipex));
	if (!pipex)
		return (0);
	pipex->ac = ac;
	pipex->av = av;
	pipex->envp = envp;
	pipex->i = 2;
	pipex->oldfd = -1;
	
	return (pipex);
}

void	close_pipes(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

void	error(void)
{
	ft_putstr_fd("Error\n", 2);
	exit(EXIT_FAILURE);
}

void	print(char *s)
{
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\n", 2);
}