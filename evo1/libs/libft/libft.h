/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atursun <atursun@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:34:46 by atursun           #+#    #+#             */
/*   Updated: 2026/01/28 12:29:38 by atursun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

int		ft_isalpha(int a);
int		ft_isdigit(int a);
int		ft_isalnum(int a);
int		ft_isascii(int a);
int		ft_isprint(int a);
int		ft_toupper(int a);
int		ft_tolower(int a);

char	*ft_itoa(int number);
int		ft_atoi(const char *str);
size_t	ft_strlen(const char *str);
char	**ft_split(char const *str, char c);
char	*ft_strchr(const char *str, int chr);
char	*ft_strrchr(const char *str, int chr);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *str1, const char *str2, size_t size);
char	*ft_strnstr(const char *str, const char *substr, size_t len);

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *str, int fd);
void	ft_putendl_fd(char *str, int fd);
void	ft_putnbr_fd(int number, int fd);
char	*ft_strdup(const char *src);
void	ft_bzero(void *str, size_t len);
void	*ft_memset(void *str, int chr, size_t len);
void	*ft_memchr(const void *str, int chr, size_t n);
void	*ft_calloc(size_t num_blocks, size_t block_size);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *source, size_t n);
int		ft_memcmp(const void *str1, const void *str2, size_t n);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstdelone(t_list *lst, void (*del)(void*));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);

void	ft_free(char **str);
int		ft_len_of_str(char *str);
char	*ft_search_new_line(char *str);
char	*ft_merge_str(char *leftover, char *buffer);
int		ft_len_of_word(char const *str, char c);
int		ft_atoi_base(char *str, char *base);
float	max(float a, float b);
float	min(float a, float b);
float	absolute(float nbr);

#endif