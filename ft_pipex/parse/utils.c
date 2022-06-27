/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:21:48 by rvrignon          #+#    #+#             */
/*   Updated: 2022/06/23 16:34:10 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

// t_command	*ft_lstnew(void *content)
// {
// 	t_command	*new;

// 	new = (t_command *)malloc(sizeof(t_command));
// 	if (!new)
// 		return (NULL);
// 	new->cmd = ;
// 	new->cmd_path = ;
// 	new->options = ;
// 	new->next = NULL;
// 	return (new);
// }

t_command	*create_list(char **av, char **envp)
{
	int i;

	(void)envp;
	i = 0;
	while (av[i++] != NULL)
	{
		ft_printf("%s\n", av[i]);	
	}
	return (NULL);
}

