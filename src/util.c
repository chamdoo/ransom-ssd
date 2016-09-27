/*
 * util.c
 *
 *  Created on: 2016. 9. 8.
 *      Author: seryugun
 */

#include "engine.h"

char *split_char(char *str, char c, char **buf)
{
	char *p = NULL;
	uint n = 0;

	if(buf == NULL) return NULL;

	if(str == NULL)
	{
		*buf = NULL;
		return NULL;
	}

	p = str;
	while(*p != 0x00)
	{
		if(*p == c)
			break;
		p ++;
	}

	n = p - str;
	if(n == 0)
	{
		*buf = NULL;
		return p + 1;
	}
	else
	{
		if(*buf == NULL)
			*buf = (char*)malloc(n + 1);
		memset(*buf, 0x00, n + 1);
		memcpy(*buf, str, n);
	}
	return *p == 0x00 ? NULL : p + 1;
}

uint dp_point(uint dp, uint digit)
{	// 000005164
	uint digit_p = 1;
	uint i = 0;

	for(i = 0; i < digit -1; i ++) digit_p *= 10;

	for(i = 0; i < digit -1; i ++)
	{
		if((uint)(dp / digit_p) == 0) dp *= 10;
		else break;
	}
	return dp;
}
