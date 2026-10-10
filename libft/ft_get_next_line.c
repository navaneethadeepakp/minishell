/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbecker <kbecker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:47:07 by kbecker           #+#    #+#             */
/*   Updated: 2025/10/19 17:53:50 by kbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strpos(char const *str, char c)
{
	int	pos;

	pos = 0;
	while (str[pos] && str[pos] != c)
		pos++;
	if (str[pos] == c)
		return (pos);
	return (-1);
}

static int	ft_set_bytes_to_read(int const bytes_read, int const n_pos)
{
	if (n_pos < 0)
		return (bytes_read);
	if (n_pos < bytes_read)
		return (n_pos + 1);
	return (bytes_read);
}

static int	ft_continue(
				char *buffer, int const buf_len, int const bytes_to_read)
{
	if (buf_len > bytes_to_read)
	{
		ft_memmove(buffer, buffer + bytes_to_read, buf_len - bytes_to_read);
		buffer[buf_len - bytes_to_read] = '\0';
		return (0);
	}
	if (bytes_to_read == buf_len && buffer[bytes_to_read - 1] == '\n')
	{
		buffer[0] = '\0';
		return (0);
	}
	buffer[0] = '\0';
	return (1);
}

static int	ft_read_next_bytes(
				int fd, char *buffer, int *total_bytes, int *bytes_to_read)
{
	*bytes_to_read = 0;
	if (*buffer)
		*total_bytes = ft_strlen(buffer);
	else
	{
		*total_bytes = read(fd, buffer, BUFFER_SIZE);
		if (*total_bytes >= 0)
			buffer[*total_bytes] = '\0';
	}
	if (*total_bytes < 0)
		return (*bytes_to_read = *total_bytes, *total_bytes);
	*bytes_to_read = ft_set_bytes_to_read(
			*total_bytes, ft_strpos(buffer, '\n'));
	return (*bytes_to_read);
}

char	*ft_get_next_line(int fd)
{
	static char	buffer[1024][BUFFER_SIZE + 1];
	char		*line;
	char		*tmp_line;
	int			bytes_read;
	int			bytes_to_read;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_strndup("", 0);
	if (line == NULL)
		return (NULL);
	while (ft_read_next_bytes(fd, buffer[fd], &bytes_read, &bytes_to_read) > 0)
	{
		if (bytes_to_read < 0)
			return (free(line), line = NULL, NULL);
		tmp_line = line;
		line = ft_strnjoin(line, buffer[fd], bytes_to_read, tmp_line);
		if (line == NULL)
			return (NULL);
		if (!ft_continue(buffer[fd], bytes_read, bytes_to_read))
			return (line);
	}
	if (!*line || bytes_to_read < 0)
		return (buffer[fd][0] = '\0', free(line), line = NULL, NULL);
	return (line);
}
