/*
 * sec.c
 *
 *  Created on: 2016. 9. 20.
 *      Author: seryugun
 */

#include "engine.h"

int init_iocount(tiocount **iocount)
{
	if(iocount == NULL) return -1;

	*iocount = (tiocount*)malloc(sizeof(tiocount));
	memset(*iocount, 0x00, sizeof(tiocount));
	return 0;
}

int free_iocount(tiocount **iocount)
{
	tiocount *p = NULL, *next = NULL;

	if(iocount == NULL || *iocount == NULL) return -1;

	p = *iocount;
	while(p != NULL)
	{
		next = p->next;
		free(p);
		p = NULL;
		p = next;
	}
	*iocount = NULL;
	return 0;
}

int get_sec_io_count(tio *io, tiocount **iocount)
{
	tio *p = NULL;
	tiocount *p_ic = NULL;
	ulong64 last_sec = 0;

	p = io;

	if(*iocount == NULL)
		init_iocount(iocount);
	p_ic = *iocount;
	while(p != NULL)
	{
		if(p->sec != last_sec && p->sec != 0)
		{
			last_sec = p->sec;
			init_iocount(&p_ic->next);
			p_ic = p_ic->next;
		}
		p_ic->sec = p->sec;
		if(p->mark == 'R')
			p_ic->cnt_r ++;
		else if(p->mark == 'W')
			p_ic->cnt_w ++;

		p = p->next;
	}
	return 0;
}
