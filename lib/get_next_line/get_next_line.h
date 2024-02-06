/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlakchai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 09:53:55 by codespace         #+#    #+#             */
/*   Updated: 2023/11/27 22:34:23 by tlakchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 7
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_list	t_list;
struct s_list {
	char	buffer[BUFFER_SIZE + 1];
	size_t	idx;
	t_list	*next;
};

typedef struct s_gnl	t_gnl;
struct s_gnl{
	char	is_nl;
	int		fd;
	ssize_t	line_len;
	t_list	*lst;
};

char	*get_next_line(int fd);
char	*get_lines(t_gnl *gnl, size_t len, char **line);
char	get_content(t_gnl *gnl, t_list *tmp, int rd_size, size_t i);
t_list	*gnl_lstnew(t_list **lst);
void	*gnl_free(t_gnl *gnl);

#endif
