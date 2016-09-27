/*
 * detect_window.c
 *
 *  Created on: 2016. 9. 27.
 *      Author: seryugun
 */
#include "engine.h"

int init_detect_win(uint cnt_win, tdetect_win **detect_win)
{
	uint i = 0;
	tdetect **p = NULL;

	if(detect_win == NULL) return -1;
	*detect_win = (tdetect_win*)malloc(sizeof(tdetect_win));
	memset(*detect_win, 0x00, sizeof(tdetect_win));

	(*detect_win)->cnt_win = cnt_win;
	(*detect_win)->detect = (tdetect**)malloc(sizeof(tdetect*) * cnt_win);
	memset((*detect_win)->detect, 0x01, sizeof(tdetect*) * cnt_win);

	for(i = 0; i < cnt_win; i ++)
	{
		p = ((*detect_win)->detect + i);
		*p = (tdetect*)malloc(sizeof(tdetect));
		memset(*p, 0x00, sizeof(tdetect));
		(*p)->cnt = i;
	}
	(*detect_win)->total_io = (uint*)malloc(sizeof(uint) * cnt_win);
	memset((*detect_win)->total_io, 0x00, sizeof(uint) * cnt_win);
	return 0;
}

int free_detect_win(tdetect_win **detect_win)
{
	uint i = 0;
	tdetect **p = NULL;

	for(i = 0; i < (*detect_win)->cnt_win; i ++)
	{
		p = ((*detect_win)->detect + i);
		free_detect(p);
	}
	return 0;
}
