/*
 * io.c
 *
 *  Created on: 2016. 9. 8.
 *      Author: seryugun
 */

#include "engine.h"

int init_io(tio **io)
{
	if(io == NULL) return -1;
	*io = (tio*)malloc(sizeof(tio));
	memset(*io, 0x00, sizeof(tio));
	return 0;
}

int free_io(tio **io)
{
	tio *p = NULL, *next = NULL;

	if(io == NULL || *io == NULL) return -1;

	p = *io;
	while(p != NULL)
	{
		next = p->next;
		free(p);
		p = NULL;
		p = next;
	}
	*io = NULL;
	return 0;
}

ulong get_io_last_time(tio *io)
{
	tio *p = NULL;
	p = io;
	while(p->next != NULL)
	{
		p = p->next;
	}
	return p->sec;
}

tio *find_io_time(tio *io, ulong sec)
{
	tio *p = NULL;
	p = io;
	while(p != NULL)
	{
		if(p->sec == sec) return p;
		p = p->next;
	}
	return NULL;
}

tio *find_io_near_time(tio *io, ulong sec)
{
	tio *p = NULL, *p_io = NULL;
	ulong next_sec = 0, last_sec = 0;

	last_sec = get_io_last_time(io);
	next_sec = sec;
	while(next_sec <= last_sec)
	{
		if((p = find_io_time(io, next_sec)) != NULL)
			return p;
		else
			next_sec ++;
	}
	return NULL;
}
