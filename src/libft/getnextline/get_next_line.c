/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibault <thibault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:31:15 by tsanglar          #+#    #+#             */
/*   Updated: 2023/08/07 08:48:59 by thibault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*get_next_line(int fd)
{
	static char	*temp;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	temp = add_buf_to_temp(fd, temp);
	if (!temp)
		return (NULL);
	line = get_new_line(temp);
	temp = temp_update(temp);
	return (line);
}

char	*add_buf_to_temp(int fd, char *temp)
{
	int			nbytes;
	char		*buf;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	nbytes = 1;
	while (nbytes && check_add_buf_to_temp(temp))
	{	
		nbytes = read(fd, buf, BUFFER_SIZE);
		if (nbytes == -1)
		{
			free(buf);
			if (temp)
			{
				free(temp);
				temp = NULL;
			}
			return (NULL);
		}
		buf[nbytes] = '\0';
		temp = ft_strjoin(temp, buf);
	}
	free (buf);
	return (temp);
}

int	check_add_buf_to_temp(char *temp)
{
	int	i;

	if (temp == NULL)
		return (1);
	i = 0;
	while (*(temp + i) != '\n' && *(temp + i) != '\0')
		i++;
	if (*(temp + i) == '\n')
		return (0);
	return (1);
}

char	*get_new_line(char *temp)
{
	char		*line;
	int			i_end;
	int			i;

	if (temp[0] == '\0')
		return (NULL);
	i_end = 0;
	while (temp[i_end] != '\n' && temp[i_end] != '\0')
		i_end++;
	line = (char *)malloc(sizeof(char) * (i_end + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (temp[i] != '\0' && temp[i] != '\n')
	{
		line[i] = temp[i];
		i++;
	}
	if (temp[i] == '\n')
	{
			line[i] = temp[i];
			i++;
	}
	line[i] = '\0';
	return (line);
}

char	*temp_update(char *temp)
{
	char		*newtemp;
	int			i_end;
	int			i;

	i_end = 0;
	while (*(temp + i_end) != '\n' && *(temp + i_end) != '\0')
		i_end++;
	if (!temp[i_end])
	{
		free(temp);
		return (NULL);
	}
	i_end++;
	newtemp = (char *)malloc(sizeof(char) * (ft_strlen(temp) - i_end + 1));
	if (!newtemp)
		return (NULL);
	i = 0;
	while (temp[i_end])
		newtemp[i++] = temp[i_end++];
	*(newtemp + i) = 0;
	free(temp);
	return (newtemp);
}
