#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

int	main(void)
{
	char	arr[] = "Good morning Vietnam";
	char	arr2[] = "Good morning Saigon";
	char	numarr[] = "0246897531";

	puts("\n*********************************\n");
	printf("ft_atoi\n");
	printf("ORIGINAL: %d\n", atoi(numarr));
	printf("YOUR'S  : %d\n", ft_atoi(numarr));
	printf("ORIGINAL: %d\n", atoi(arr));
	printf("YOUR'S  : %d\n", ft_atoi(arr));
	printf("ORIGINAL: %d\n", atoi("2147483647"));
	printf("YOUR'S  : %d\n", ft_atoi("2147483647"));
	printf("ORIGINAL: %d\n", atoi("-2147483648"));
	printf("YOUR'S  : %d\n", ft_atoi("-2147483648"));
	printf("ORIGINAL: %d\n", atoi("2147483648"));
	printf("YOUR'S  : %d\n", ft_atoi("2147483648"));
	printf("ORIGINAL: %d\n", atoi("-2147483649"));
	printf("YOUR'S  : %d\n", ft_atoi("-2147483649"));
	printf("ORIGINAL: %d\n", atoi("99999999999999999999999999"));
	printf("YOUR'S  : %d\n", ft_atoi("99999999999999999999999999"));
	printf("ORIGINAL: %d\n", atoi("-99999999999999999999999999"));
	printf("YOUR'S  : %d\n", ft_atoi("-99999999999999999999999999"));

	puts("\n*********************************\n");
	printf("ft_bzero\n");
	bzero(arr, 4);
	printf("ORIGINAL: %c\n", arr[5]);
	ft_bzero(arr, 4);
	printf("YOUR'S  : %c\n", arr[5]);

	puts("\n*********************************\n");
	printf("ft_calloc\n");
	printf("ORIGINAL: %d, %d\n", *(int *)(calloc(4, sizeof(int))), *(int *)((calloc(3, sizeof(int))) + 2));
	printf("YOUR'S  : %d, %d\n", *(int *)(ft_calloc(4, sizeof(int))), *(int *)((ft_calloc(3, sizeof(int))) + 2));

	int *ip = calloc(3, sizeof(int));
	int *ip2 = calloc(3, sizeof(int));
	printf("ORIGINAL: ");
	for (int i = 0; i < 3; i++)
	{
	printf("%d ", ip[i]);
	}
	printf("\nYOUR'S  : ");
	for (int i = 0; i < 3; i++)
	{
	printf("%d ", ip[i]);
	}

	puts("\n*********************************\n");
	printf("ft_isalnum\n");
	printf("ORIGINAL: %d\n", isalnum('A'));
	printf("YOUR'S  : %d\n", ft_isalnum('A'));
	printf("ORIGINAL: %d\n", isalnum('$'));
	printf("YOUR'S  : %d\n", ft_isalnum('$'));
	printf("ORIGINAL: %d\n", isalnum('0'));
	printf("YOUR'S  : %d\n", ft_isalnum('0'));

	puts("\n*********************************\n");
	printf("ft_isalpha\n");
	printf("ORIGINAL: %d\n", isalpha('A'));
	printf("YOUR'S  : %d\n", ft_isalpha('A'));
	printf("ORIGINAL: %d\n", isalpha('a'));
	printf("YOUR'S  : %d\n", ft_isalpha('a'));
	printf("ORIGINAL: %d\n", isalpha('$'));
	printf("YOUR'S  : %d\n", ft_isalpha('$'));

	puts("\n*********************************\n");
	printf("ft_isascii\n");
	printf("ORIGINAL: %d\n", isascii('.'));
	printf("YOUR'S  : %d\n", ft_isascii('.'));
	printf("ORIGINAL: %d\n", isascii('0x89'));
	printf("YOUR'S  : %d\n", ft_isascii('0x89'));

	puts("\n*********************************\n");
	printf("ft_isdigit\n");
	printf("ORIGINAL: %d\n", isdigit(0));
	printf("YOUR'S  : %d\n", ft_isdigit(0));
	printf("ORIGINAL: %d\n", isdigit('5'));
	printf("YOUR'S  : %d\n", ft_isdigit('5'));
	printf("ORIGINAL: %d\n", isdigit('K'));
	printf("YOUR'S  : %d\n", ft_isdigit('K'));
	printf("ORIGINAL: %d\n", isdigit('0'));
	printf("YOUR'S  : %d\n", ft_isdigit('0'));

	puts("\n*********************************\n");
	printf("ft_isprint\n");
	printf("ORIGINAL: %d\n", isprint(' '));
	printf("YOUR'S  : %d\n", ft_isprint(' '));
	printf("ORIGINAL: %d\n", isprint(31));
	printf("YOUR'S  : %d\n", ft_isprint(31));
	printf("ORIGINAL: %d\n", isprint(126));
	printf("YOUR'S  : %d\n", ft_isprint(126));
	printf("ORIGINAL: %d\n", isprint(128));
	printf("YOUR'S  : %d\n", ft_isprint(128));

	puts("\n*********************************\n");
	printf("ft_itoa\n");
	printf("integer %d, string %s\n", 0, ft_itoa(0));
	printf("integer %d, string %s\n", -7, ft_itoa(-7));
	printf("integer %d, string %s\n", 395, ft_itoa(395));
	printf("integer %d, string %s\n", -391, ft_itoa(-391));
	printf("integer %d, string %s\n", 2147483647, ft_itoa(2147483647));
	printf("integer %d, string %s\n", -2147483648, ft_itoa(-2147483648));

	puts("\n*********************************\n");
	char mcarr[6] = "Hello";
	char mcarr2[6] = "Hello";
	printf("ft_memccpy\n");
	printf("ORIGINAL: %s\n", memccpy(mcarr, "Dalma", 'L', 5));
	printf("YOUR'S  : %s\n", ft_memccpy(mcarr2, "Dalma", 'L', 5));
	printf("ORIGINAL: %s\n", memccpy(mcarr, "Dalma", 'l', 5));
	printf("YOUR'S  : %s\n", ft_memccpy(mcarr2, "Dalma", 'l', 5));

	puts("\n*********************************\n");
	printf("ft_memchr\n");
	printf("ORIGINAL: %p\n", memchr(arr, '$', 20));
	printf("YOUR'S  : %p\n", ft_memchr(arr, '$', 20));
	printf("ORIGINAL: %p\n", memchr(arr, 'V', 20));
	printf("YOUR'S  : %p\n", ft_memchr(arr, 'V', 20));

	puts("\n*********************************\n");
	printf("ft_memcmp\n");
	printf("ORIGINAL: %d\n", memcmp("", "", 4));
	printf("YOUR'S  : %d\n", ft_memcmp("", "", 4));
	printf("ORIGINAL: %d\n", memcmp(arr, arr2, 15));
	printf("YOUR'S  : %d\n", ft_memcmp(arr, arr2, 15));
	printf("ORIGINAL: %d\n", memcmp("Xa", "Aa", 2));
	printf("YOUR'S  : %d\n", ft_memcmp("a", "Aa", 2));
	printf("ORIGINAL: %d\n", memcmp("Good morning Vietnam", "Good morning Saigon", 10));
	printf("YOUR'S  : %d\n", ft_memcmp("Good morning Vietnam", "Good morning Saigon", 10));

	puts("\n*********************************\n");
	char marr[6] = "Hello";
	char marr2[6] = "Hello";
	printf("ft_memcpy\n");
	printf("ORIGINAL: %s\n", memcpy(marr, "Jazz concert", 3));
	printf("YOUR'S  : %s\n", ft_memcpy(marr2, "Jazz concert", 3));
	ft_bzero(marr, 6);
	ft_bzero(marr2, 6);
	printf("ORIGINAL: %s\n", memcpy(marr, "Jazz concert", 6));
	printf("YOUR'S  : %s\n", ft_memcpy(marr2, "Jazz concert", 6));

	puts("\n*********************************\n");
	ft_bzero(marr, 6);
	ft_bzero(marr2, 6);
	printf("ft_memmove\n");
	printf("ORIGINAL: %s\n", memmove(marr, "Barra", 3));
	printf("YOUR'S  : %s\n", ft_memmove(marr2, "Barra", 3));
	printf("ORIGINAL: %s\n", memmove(marr, "Japonese", 5));
	printf("YOUR'S  : %s\n", ft_memmove(marr2, "Japonese", 5));

	puts("\n*********************************\n");
	printf("ft_memset\n");
	printf("ORIGINAL: %s\n", memset(arr, '$', 4));
	printf("YOUR'S  : %s\n", ft_memset(arr, '$', 4));

	puts("\n*********************************\n");
	printf("ft_strchr\n");
	printf("ORIGINAL: %s\n", strchr("Yocogama", 'g'));
	printf("YOUR'S  : %s\n", ft_strchr("Yocogama", 'g'));
	printf("ORIGINAL: %s\n", strchr("Yocogama", '\0'));
	printf("YOUR'S  : %s\n", ft_strchr("Yocogama", '\0'));

	puts("\n*********************************\n");
	printf("ft_strdup\n");
	printf("ORIGINAL: %s\n", strdup("PariS"));
	printf("YOUR'S  : %s\n", ft_strdup("PariS"));

	puts("\n*********************************\n");
	printf("ft_strjoin\n");
	printf("YOUR'S  : %s\n", ft_strjoin("Apple", "Juice"));
	printf("YOUR'S  : %s\n", ft_strjoin("$string1$", "_string2_"));

	puts("\n*********************************\n");
	char sarr[7] = "Good";
	char sarr2[7] = "Good";
	char *sp = "Bad";
	char *sp2 = "Sad";
	printf("ft_strlcat\n");
	printf("ORIGINAL: %zu\n", strlcat(sarr, "Day", 7));
	printf("YOUR'S  : %zu\n", ft_strlcat(sarr2, "Day", 7));
	printf("ORIGINAL: %s\n", sarr);
	printf("YOUR'S  : %s\n", sarr2);
	printf("ORIGINAL: %zu\n", strlcat(sp, "Dad", 3));
	printf("YOUR'S  : %zu\n", ft_strlcat(sp2, "Dad", 3));
	ft_bzero(sarr, 7);
	ft_bzero(sarr2, 7);
	ft_memset(sarr, 'A', 3);
	ft_memset(sarr2, 'A', 3);
	printf("ORIGINAL: %zu\n", strlcat(sarr, "Bcb", 7));
	printf("YOUR'S  : %zu\n", ft_strlcat(sarr2, "Bcb", 7));
	printf("ORIGINAL: %s\n", sarr);
	printf("YOUR'S  : %s\n", sarr2);

	puts("\n*********************************\n");
	printf("ft_strlcpy\n");
	printf("ORIGINAL: %zu\n", strlcpy(marr, "Sixty", 6));
	printf("YOUR'S  : %zu\n", ft_strlcpy(marr2, "Sixty", 6));
	printf("ORIGINAL: %zu\n", strlcpy(marr, "Sixteen", 6));
	printf("YOUR'S  : %zu\n", ft_strlcpy(marr2, "Sixteen", 6));
	printf("ORIGINAL: %s\n", marr);
	printf("YOUR'S  : %s\n", marr2);

	puts("\n*********************************\n");
	printf("ft_strlen\n");
	printf("ORIGINAL: %zu\n", strlen("Sixty"));
	printf("YOUR'S  : %zu\n", ft_strlen("Sixty"));
	printf("ORIGINAL: %zu\n", strlen(marr));
	printf("YOUR'S  : %zu\n", ft_strlen(marr));

	puts("\n*********************************\n");
	printf("ft_strncmp\n");
	printf("ORIGINAL: %d\n", strncmp("Adam", "Adan", 4));
	printf("YOUR'S  : %d\n", ft_strncmp("Adam", "Adan", 4));
	printf("ORIGINAL: %d\n", strncmp("Adam", "Adan", 3));
	printf("YOUR'S  : %d\n", ft_strncmp("Adam", "Adan", 3));
	printf("ORIGINAL: %d\n", strncmp("Adam", "Baba", 0));
	printf("YOUR'S  : %d\n", ft_strncmp("Adam", "Baba", 0));
	printf("ORIGINAL: %d\n", strncmp("", "", 4));
	printf("YOUR'S  : %d\n", ft_strncmp("", "", 4));

	
	

	puts("\n*********************************\n");
	printf("ft_strrchr\n");
	printf("ORIGINAL: %s\n", strrchr("Syru$", '$'));
	printf("YOUR'S  : %s\n", ft_strrchr("Syru$", '$'));
	printf("ORIGINAL: %s\n", strrchr("Syru$", 'S'));
	printf("YOUR'S  : %s\n", ft_strrchr("Syru$", 'S'));
	printf("ORIGINAL: %s\n", strchr("Syru$", '\0'));
	printf("YOUR'S  : %s\n", ft_strchr("Syru$", '\0'));

	puts("\n*********************************\n");
	printf("ft_strtrim\n");
	printf("YOUR'S  : %s\n", ft_strtrim("two words", "w"));
	printf("YOUR'S  : %s\n", ft_strtrim("$Out of the two words, 'your' is the most common. It appears about 44 times more frequently than 'yours$$$' $\t \0\n$ $\0", "$ ,\t\n'4"));
	printf("YOUR'S  : %s\n", ft_strtrim("$4' ,Out $4 of the two $4 words' $4' ,", "$ ,'4"));

	puts("\n*********************************\n");
	printf("ft_substr\n");
	printf("YOUR'S  : %s\n", ft_substr("Revolutionary", 1, 9));
	printf("YOUR'S  : %s\n", ft_substr("Dorama", 2, 10));

	puts("\n*********************************\n");
	printf("ft_tolower\n");
	printf("ORIGINAL: %c\n", tolower('Z'));
	printf("YOUR'S  : %c\n", ft_tolower('Z'));
	printf("ORIGINAL: %c\n", tolower('y'));
	printf("YOUR'S  : %c\n", ft_tolower('y'));
	printf("ORIGINAL: %c\n", tolower('$'));
	printf("YOUR'S  : %c\n", ft_tolower('$'));

	puts("\n*********************************\n");
	printf("ft_toupper\n");
	printf("ORIGINAL: %c\n", toupper('a'));
	printf("YOUR'S  : %c\n", ft_toupper('a'));
	printf("ORIGINAL: %c\n", toupper('B'));
	printf("YOUR'S  : %c\n", ft_toupper('B'));
	printf("ORIGINAL: %c\n", toupper('.'));
	printf("YOUR'S  : %c\n", ft_toupper('.'));

	puts("\n*********************************\n");
	printf("ft_split\n");
	printf("YOUR'S  : \n\n");
	char **arr2d;
	arr2d = ft_split("$Yocco$gama$", '$');
	int i = 0;
	while (arr2d[i] != NULL)
	{
	printf("%s\n", arr2d[i]);
	i++;
	}
	printf("\n");
	arr2d = ft_split("$Bed$was$hard$", '$');
	i = 0;
	while (arr2d[i] != NULL)
	{
	printf("%s\n", arr2d[i]);
	i++;
	}
	printf("\n");
	arr2d = ft_split("$Harvey&Barns$$ was famous$ bookstore on the 5th Avenue $ in New-York.$", '$');
	i = 0;
	while (arr2d[i] != NULL)
	{
	printf("%s\n", arr2d[i]);
	i++;
	}
	printf("\n");
	arr2d = ft_split("      split       this for   me  !       ", ' ');
	i = 0;
	while (arr2d[i] != NULL)
	{
	printf("\n%s, len = %zu", arr2d[i], ft_strlen(arr2d[i]));
	i++;
	}
	printf("\n");

	puts("\n*********************************\n");
	printf("ft_strmapi\n");
	printf("MISSING CHECK HERE!!!");

	puts("\n*********************************\n");
	printf("ft_putchar_fd\n");
	printf("MISSING CHECK HERE!!!");

	puts("\n*********************************\n");
	printf("ft_putstr_fd\n");
	printf("MISSING CHECK HERE!!!");

	puts("\n*********************************\n");
	printf("ft_putendl_fd\n");
	printf("MISSING CHECK HERE!!!");

	puts("\n*********************************\n");
	printf("ft_putnbr_fd\n");
	printf("MISSING CHECK HERE!!!");

	puts("\n*********************************\n");
	printf("ft_calloc test\n");

	
	
	puts("\n*********************************\n");
	printf("ft_strnstr\n");
	printf("ORIGINAL: %s\n", strnstr("Globus", "bus", 6));
	printf("YOUR'S  : %s\n", ft_strnstr("Globus", "bus", 6));
	printf("ORIGINAL: %s\n", strnstr("Globus", "bus", 4));
	printf("YOUR'S  : %s\n", ft_strnstr("Globus", "bus", 4));
	printf("ORIGINAL: %s\n", strnstr("Drama", "Cine", 5));
	printf("YOUR'S  : %s\n", ft_strnstr("Drama", "Cine", 5));
	printf("ORIGINAL: %s\n", strnstr("Drama", "Dra", 5));
	printf("YOUR'S  : %s\n", ft_strnstr("Drama", "Dra", 5));
	char *s1 = "";
	char *s2 = "oh no not the empty string !";
	size_t max = strlen(s2);
	printf("ORIGINAL: %s\n", strnstr(s1, s2, max));
	printf("YOUR'S  : %s\n", ft_strnstr(s1, s2, max));
	return (0);
}
