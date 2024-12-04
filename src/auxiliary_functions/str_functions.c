/*
 *	Functions used when using strings.
 */

#include "yyfunctions.h"
#include "str_functions.h"

char	*strjoin(const char *str1, const char *str2)
{
	char *dst;
	
	dst = yymalloc(strlen(str1) + strlen(str2) + 1);
	strcpy(dst, str1);
	strcat(dst, str2);
	return dst;
}

static int	strlcpy(char *dst, const char *src, int dstsize)
{
	int	i;
	int	size;

	size = strlen(src);
	if (dstsize == 0)
		return (size);
	i = 0;
	while (*(src + i) != '\0' && i < dstsize - 1)
	{
		*(dst + i) = *(src + i);
		i++;
	}
	*(dst + i) = '\0';
	return (size);
}

char	*substr(char const *s, int start, int len)
{
	char	*str;
	int	s_len;
	int	size;

	if (s == NULL)
		size = 1;
	else
	{
		s_len = strlen(s);
		if (start > s_len)
			size = 1;
		else if (len > s_len - start)
			size = s_len - start + 1;
		else
			size = len + 1;
	}
	str = yymalloc(sizeof(char) * size);
	if (str == NULL)
		return (NULL);
	if (start > s_len)
		*str = '\0';
	else
		strlcpy(str, s + start, len);
	return (str);
}
