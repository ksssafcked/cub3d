/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 13:41:59 by lsaiti            #+#    #+#             */
/*   Updated: 2025/01/07 15:28:59 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/gnl.h"

char	*get_next_line_onebuff(int fd, t_string *s, t_buffer *b)
{
	s->str = malloc(1 * sizeof(char));
	if (!s->str)
		return (NULL);
	s->str[0] = '\0';
	b->bytesread = read(fd, b->buffer, BUFFER_SIZE);
	if (b->bytesread < 1)
		return (ft_freestr(&s->str));
	while (b->bytesread != 0)
	{
		s->str = ft_strjoin(s->str, b->buffer, 1);
		if (!s->str)
			return (NULL);
		if (b->buffer[0] == '\n')
			break ;
		b->bytesread = read(fd, b->buffer, BUFFER_SIZE);
		if (b->bytesread == -1)
			return (ft_freestr(&s->str));
	}
	return (s->str);
}

void	get_next_line_read(int fd, t_buffer *b)
{
	b->bytesread = read(fd, b->buffer, BUFFER_SIZE);
	b->buff_pos = 0;
	b->buff_read = 0;
}

char	*get_next_line_buff_set(int fd, t_string *s, t_buffer *b)
{
	while (b->bytesread > 0)
	{
		b->buff_pos++;
		if (b->buffer[b->buff_pos - 1] == '\n')
		{
			s->str = ft_strjoin(s->str, b->buffer + b->buff_read,
					b->buff_pos - b->buff_read);
			b->buff_read = b->buff_pos;
			if (!s->str)
				return (NULL);
			break ;
		}
		if (b->buff_pos == b->bytesread)
		{
			s->str = ft_strjoin(s->str, b->buffer + b->buff_read,
					b->buff_pos - b->buff_read);
			if (!s->str)
				return (NULL);
			get_next_line_read(fd, b);
			if (b->bytesread == -1)
				return (ft_freestr(&s->str));
		}
	}
	return (s->str);
}

char	*get_next_line_buff(int fd, t_buffer *b, t_string *s)
{
	s->str = malloc(1 * sizeof(char));
	if (!s->str)
		return (NULL);
	s->str[0] = '\0';
	if (b->buff_pos == 0 && b->bytesread <= 0)
		b->bytesread = read(fd, b->buffer, BUFFER_SIZE);
	if (b->bytesread < 1)
		return (ft_freestr(&s->str));
	s->str = get_next_line_buff_set(fd, s, b);
	if (!s->str)
		return (NULL);
	return (s->str);
}

char	*get_next_line(int fd)
{
	static t_buffer	b = {0};
	t_string		s;

	if (BUFFER_SIZE == 1)
	{
		s.str = get_next_line_onebuff(fd, &s, &b);
		if (!s.str || b.buff_pos == b.bytesread)
		{
			b.bytesread = 0;
			b.buff_pos = 0;
		}
	}
	else if (BUFFER_SIZE > 1)
	{
		s.str = get_next_line_buff(fd, &b, &s);
		if (!s.str || b.buff_pos == b.bytesread)
		{
			b.bytesread = 0;
			b.buff_pos = 0;
			b.buff_read = 0;
		}
	}
	else
		return (NULL);
	return (s.str);
}
