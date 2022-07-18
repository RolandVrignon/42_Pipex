/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 19:25:54 by rvrignon          #+#    #+#             */
/*   Updated: 2022/07/18 14:24:28 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

void	error(void)
{
	ft_putstr_fd("Error\n", 2);
	exit(EXIT_FAILURE);
}

void	usage(void)
{
	ft_putstr_fd("Too few or too many arguments", 2);
	exit(EXIT_SUCCESS);
}

int	open_file(char *av, int i)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(av, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == 1)
		file = open(av, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == 2)
		file = open(av, O_RDONLY, 0777);
	if (file < 0)
		perror(av);
	if (file < 0 && i != 2)
		exit(EXIT_FAILURE);
	return (file);
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
		path = find_path(cmd[0], envp);
	if (!path)
	{
		err = ft_strjoin(cmd[0], ": Command not found\n");
		ft_putstr_fd(err, STDERR_FILENO);
		free(err);
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		return ;
	}
	if (execve(path, cmd, envp) == -1)
		return ;
}

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
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
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
}
