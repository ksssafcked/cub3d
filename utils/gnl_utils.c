/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:42:49 by lsaiti            #+#    #+#             */
/*   Updated: 2025/01/07 18:18:48 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/gnl.h"

void	*ft_freestr(char **str)
{
	if (*str)
		free(*str);
	*str = NULL;
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char const *s2, long n)
{
	size_t	total_len;
	char	*str;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (ft_freestr(&s1));
	total_len = ft_strlen(s1) + n;
	str = malloc((total_len + 1) * sizeof(char));
	if (!str)
		return (ft_freestr(&s1), NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] && j < n)
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (free(s1), str);
}
