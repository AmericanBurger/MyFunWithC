#include <stdio.h>

int strlen(const char* s)
{
	int i = 0;
	while(s[i] != '\0' && ++i);
	return i;
}

char *strcat(char *dest, const char *src)
{
	char *wsk = dest + strlen(dest);
	while(*src != '\0' && (*wsk++ = *src++));	*wsk = '\0';
	return dest;
}
char *strcpy(char *dest, const char *src)
{
	while(*src != '\0' && (*dest++ = *src++));	*dest = '\0';
	return dest;
}
int strcmp(const char* s1, const char* s2)
{
	while(*s1 != '\0')
	{
		if(*s1 != *s2)
			return *s1 - *s2;
		*s1++;	*s2++;
	}
	return 0;
}

char *strchr(const char *s, int c)
{
	while(*s != (char)c)
		if(!*s++)
			return 0;
	return (char*)s;
}
char *strrchr(const char *s, int c)
{
	while(*s++)
		if(*s == (char)c)
			return (char*)s;
	return 0;
}

int main()
{
	char t[] = "halabarda", tab[] = "wrence";
	strcat(tab, t);	puts(tab);
	return 0;
}
