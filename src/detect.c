/*
 * detect.c
 *
 *  Created on: 2016. 9. 19.
 *      Author: seryugun
 */
#include "engine.h"

int init_detect(tdetect **detect)
{
	if(detect == NULL) return -1;

	*detect = (tdetect*)malloc(sizeof(tdetect));
	memset(*detect, 0x00, sizeof(tdetect));
	return 0;
}

tdetect *add_detect(tdetect *detect)
{
	tdetect *p = NULL;

	p = detect;
	while(p->next != NULL)
		p = p->next;
	init_detect(&p->next);
	return p->next;
}

int free_detect(tdetect **detect)
{
	tdetect *p = NULL, *p_next = NULL;

	p = p_next = *detect;
	while(p_next != NULL)
	{
		p_next = p->next;
		free(p);
		p = p_next;
	}
	*detect = NULL;
	return 0;
}

tdetect *find_detect(ulong64 sector, tdetect *detect)
{
	tdetect *p = NULL;

	p = detect;
	while(p != NULL)
	{
		if(p->sector == sector)
			return p;
		p = p->next;
	}
	return NULL;
}

int get_detect_max_cnt(tdetect *detect)
{
	tdetect *p = NULL;
	uint max = 0;

	p = detect;
	while(p != NULL)
	{
		if(p->cnt > max)
			max = p->cnt;
		p = p->next;
	}
	return max;
}

int get_detect(tio *io, tdetect **detect, uint *total_io)
{
	tio *p_io = NULL;
	tdetect *p_detect = NULL;
	uint total = 0;

	if(detect == NULL) return -1;
	if(total_io == NULL) return -1;

	*total_io = 0;
	p_io = io;
	while(p_io != NULL)
	{
		if(p_io->mark == 'R')	// Read IO?
		{
			// 기존에 있던 섹터인지 체크 후, 새로운 섹터만 리스트에 쌓아둔다
			if(find_detect(p_io->sector, *detect) == NULL)
			{
				if(*detect == NULL)
				{
					init_detect(detect);
					p_detect = *detect;
				}
				else
				{
					p_detect = add_detect(*detect);
				}
				p_detect->sec = p_io->sec;
				p_detect->nano_sec = p_io->nano_sec;
				p_detect->sector = p_io->sector;
			}
		}
		else if(p_io->mark == 'W')
		{
			if((p_detect = find_detect(p_io->sector, *detect)) != NULL)
			{
				p_detect->cnt ++;
				p_detect->bytes += p_io->bytes;
			}
		}
		total ++;
		p_io = p_io->next;
	}
	*total_io = total;
	return 0;
}

tio *get_detect_time(tio *io, ulong last_sec, tdetect **detect, uint *total_io)
{
	tio *p_io = NULL;
	tdetect *p_detect = NULL;
	uint total = 0;

	if(detect == NULL) return NULL;
	if(total_io == NULL) return NULL;

	*total_io = 0;
	p_io = io;
	while(p_io != NULL)
	{
		if(p_io->sec >= last_sec) break;
		if(p_io->mark == 'R')	// Read IO?
		{
			// 기존에 있던 섹터인지 체크 후, 새로운 섹터만 리스트에 쌓아둔다
			if(find_detect(p_io->sector, *detect) == NULL)
			{
				if(*detect == NULL)
				{
					init_detect(detect);
					p_detect = *detect;
				}
				else
				{
					p_detect = add_detect(*detect);
				}
				p_detect->sec = p_io->sec;
				p_detect->nano_sec = p_io->nano_sec;
				p_detect->sector = p_io->sector;
			}
		}
		else if(p_io->mark == 'W')
		{
			if((p_detect = find_detect(p_io->sector, *detect)) != NULL)
			{
				p_detect->cnt ++;
				p_detect->bytes += p_io->bytes;
			}
		}
		total ++;
		p_io = p_io->next;
	}
	*total_io = total;
	return p_io;
}
