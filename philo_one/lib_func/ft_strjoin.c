
#include "../philo_one.h"

static void	null(char *dst, const char *src, size_t size, size_t i)
{
	size_t j;

	j = 0;
	while (i < size - 1 && src[j] != '\0')
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
}

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t t;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (dst[i] != '\0' && i < size)
		i++;
	if (dst[i] != '\0')
	{
		t = size;
		return (t + ft_strlen(src));
	}
	else
	{
		t = ft_strlen(dst);
		null(dst, src, size, i);
	}
	return (t + ft_strlen(src));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char*ptr;
	int len1;
	int len2;
	int i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	ptr = (char *)malloc(sizeof(*ptr) * (len1 + len2 + 1));
	if (ptr == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	ft_strlcat(ptr, s2, (len1 + len2 + 1));
	return (ptr);
}

