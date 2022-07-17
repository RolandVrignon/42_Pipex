/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvrignon <rvrignon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 18:12:32 by rvrignon          #+#    #+#             */
/*   Updated: 2022/07/17 23:02:11 by rvrignon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <string.h>
# include <limits.h>
# include <stdarg.h>
# include <fcntl.h>

# define HEXALOWER		"0123456789abcdef"
# define HEXAUPPER		"0123456789ABCDEF"
# define BUFFER_SIZE	10

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

long int	ft_atoi(const char *nptr);

void		ft_bzero(void *s, size_t n);

void		*ft_calloc(size_t nmemb, size_t size);

int			ft_isalpha(int c);

int			ft_isascii(int c);

int			ft_isdigit(int c);

int			ft_isalnum(int c);

int			ft_isprint(int c);

void		*ft_memchr(const void *s, int c, size_t n);

void		*ft_memcpy(void *dest, const void *src, size_t n);

int			ft_memcmp(const void *s1, const void *s2, size_t n);

void		*ft_memmove(void *dest, const void *src, size_t n);

void		*ft_memset(void *s, int c, size_t n);

char		*ft_strchr(const char *s, int c);

char		*ft_strdup(const char *s);

size_t		ft_strlcat(char *dst, const char *src, size_t size);

size_t		ft_strlcpy(char *dst, const char *src, size_t size);

size_t		ft_strlen(const char *s);

int			ft_strncmp(const char *s1, const char *s2, size_t n);

char		*ft_strnstr(const char *str, const char *to_find, size_t len);

char		*ft_strrchr(const char *s, int c);

int			ft_tolower(int c);

int			ft_toupper(int c);

char		*ft_substr(char const *s, unsigned int start, size_t len);

char		*ft_strjoin(char const *s1, char const *s2);

char		*ft_strtrim(char const *s1, char const *set);

char		**ft_split(char const *s, char c);

char		*ft_itoa(int n);

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));

void		ft_striteri(char *s, void (*f)(unsigned int, char *));

void		ft_putchar_fd(char c, int fd);

void		ft_putstr_fd(char *s, int fd);

void		ft_putendl_fd(char *s, int fd);

void		ft_putnbr_fd(int n, int fd);

// Listes

t_list		*ft_lstnew(void *content);

void		ft_lstadd_front(t_list **lst, t_list *new);

int			ft_lstsize(t_list *lst);

t_list		*ft_lstlast(t_list *lst);

void		ft_lstadd_back(t_list **lst, t_list *new);

void		ft_lstdelone(t_list *lst, void (*del)(void *));

void		ft_lstclear(t_list **lst, void (*del)(void *));

void		ft_lstiter(t_list *lst, void (*f)(void *));

t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

// --------------------------------------------------------------------------
// --------------------------------------------------------------------------

// Printf

int			ft_printf(const char *format, ...);

// Printf // Flags

size_t		ft_flag_c(int c);

size_t		ft_flag_s(char *str);

size_t		ft_flag_p(void *p);

size_t		ft_flag_d(int nb);

size_t		ft_flag_u(unsigned int nb);

size_t		ft_flag_x(unsigned int nb);

size_t		ft_flag_uppercase_x(unsigned int nb);

size_t		ft_flag_pourcent(void);

// Printf // Utils

char		*ft_putnbr_base(unsigned int nbr, char *base, int j, char *r);

size_t		ft_print_pointeur(unsigned long long nbr, char *base);

int			check_base(char *base);

void		ft_strrev(char *str);

char		*process_unsigned(int j, int len, char *str, unsigned int n);

char		*itoa_unsigned(unsigned int n);

// Gnl

char		*return_value(char *buffer, char *line, char *limiter, char *stash);

char		*get_next_line(int fd, char *limiter);

#endif