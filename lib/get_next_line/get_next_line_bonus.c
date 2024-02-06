/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlakchai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 09:56:34 by codespace         #+#    #+#             */
/*   Updated: 2023/11/27 22:38:32 by tlakchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	get_content(t_gnl *gnl, t_list *tmp, int rd_size, size_t idx)
{
	while (tmp)
	{
		if (!tmp->buffer[tmp->idx])
		{
			rd_size = read(gnl->fd, tmp->buffer, BUFFER_SIZE);
			if (rd_size < 1)
				return (rd_size == 0);
			tmp->buffer[rd_size] = '\0';
			tmp->idx = 0;
		}
		idx = tmp->idx;
		while (tmp->buffer[idx] && tmp->buffer[idx] != '\n')
			idx++;
		gnl->is_nl = tmp->buffer[idx] == '\n';
		gnl->line_len += idx - tmp->idx + gnl->is_nl;
		if (gnl->is_nl)
			return (1);
		if (!gnl_lstnew(&(tmp->next)))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

char	*get_lines(t_gnl *gnl, size_t len, char **line)
{
	t_list	*tmp;
	char	current_char;

	while (gnl->lst)
	{
		current_char = gnl->lst->buffer[gnl->lst->idx];
		if (current_char == '\n' || !current_char)
			break ;
		(*line)[len++] = gnl->lst->buffer[gnl->lst->idx++];
		if (!(gnl->lst->buffer[gnl->lst->idx]))
		{
			tmp = gnl->lst;
			gnl->lst = gnl->lst->next;
			free(tmp);
		}
	}
	if (gnl->lst && gnl->is_nl)
		gnl->lst->idx++;
	return (*line);
}

char	*get_next_line(int fd)
{
	static t_gnl	gnl[FD_MAX] = {{0, 0, 0, NULL}};
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= FD_MAX)
		return (NULL);
	gnl[fd].fd = fd;
	gnl[fd].is_nl = 0;
	gnl[fd].line_len = 0;
	if (gnl_lstnew(&(gnl[fd].lst)) == NULL)
		return (gnl_free(&(gnl[fd])));
	if (!get_content(&(gnl[fd]), gnl[fd].lst, 0, 0))
		return (gnl_free(&(gnl[fd])));
	if (!gnl[fd].line_len)
		return (gnl_free(&(gnl[fd])));
	line = malloc(sizeof(char) * (gnl[fd].line_len + 1));
	if (line == NULL)
		return (gnl_free(&(gnl[fd])));
	if (gnl[fd].is_nl)
		line[gnl[fd].line_len - 1] = '\n';
	line[gnl[fd].line_len] = '\0';
	if (get_lines(&gnl[fd], 0, &line) == NULL)
		return (gnl_free(&gnl[fd]));
	return (line);
}
