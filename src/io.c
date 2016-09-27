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

