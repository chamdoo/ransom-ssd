/*
 * csv.c
 *
 *  Created on: 2016. 9. 8.
 *      Author: seryugun
 */

#include "engine.h"

char *get_csv_parse_line(char *line, char **time, char **io, char **sector, char **bytes)
{
	char *p = NULL;
	char sep = ',';

	p = line;
	p = split_char(p, sep, time);
	p = split_char(p, sep, io);
	p = split_char(p, sep, sector);
	p = split_char(p, sep, bytes);
	return p;
}

int get_csv_io(char *line, tio **p_io)
{
	char *time = NULL, *mark = NULL, *sector = NULL, *bytes = NULL;
	char *sec = NULL, *p_sec = NULL;
	char *p = NULL;
	char b_next = -1;

	if(p_io == NULL) return -1;
	if(*p_io == NULL)
		init_io(p_io);

	p = line;
	p = get_csv_parse_line(p, &time, &mark, &sector, &bytes);

	if(time != NULL)
	{
		p_sec = split_char(time, '.', &sec);
		if(p_sec == NULL)
		{
			(*p_io)->sec = (ulong64)atoll(sec);
			(*p_io)->nano_sec = 0;
			free(sec);
		}
		else
		{
			(*p_io)->sec = (ulong64)atoll(sec);
			(*p_io)->nano_sec = dp_point((ulong64)atoll(p_sec), 9);
			free(sec);
		}
		free(time);
		b_next = 0;
	}
	if(mark != NULL)
	{
		(*p_io)->mark = *mark;
		free(mark);
		b_next = 0;
	}
	if(sector != NULL)
	{
		(*p_io)->sector = (ulong64)atoll(sector);
		free(sector);
		b_next = 0;
	}
	if(bytes != NULL)
	{
		(*p_io)->bytes = (ulong64)atoi(bytes);
		free(bytes);
		b_next = 0;
	}

	if(b_next == 0)
		return 0;

	return -1;
}

int load_csv_data(char *path, tio **io)
{
	file *fp = NULL;
	char line[MAX_CSV_LINE] = {0,};
	tio *p = NULL, *buf = NULL;

	if(io == NULL) return -1;

	p = *io;

	if((fp = fopen(path, "r")) == NULL)
		return -1;

	while(!feof(fp))
	{
		fgets(line, MAX_CSV_LINE, fp);
		if(*line == 0) break;

		if(get_csv_io(line, &buf) == 0)
		{
			if(*io == NULL)
				p = *io = buf;
			else
			{
				p->next = buf;
				p->next->prev = p;
				p = p->next;
			}
			buf = NULL;
		}
	}
	fclose(fp);
	return 0;
}

int save_csv_detect(char *path, uint time, uint total_io, tdetect **detect)
{
	file *fp = NULL;
	char line[MAX_CSV_LINE] = {0,};
	tdetect *p = NULL;
	uint cnt = 0;

	if(detect == NULL) return -1;

	if((fp = fopen(path, "a+")) == NULL)
		return -1;

	//max = get_detect_max_cnt(*detect);

	p = *detect;
	while(p != NULL)	// count node
	{
		if(p->cnt > 0)
			cnt ++;
		p = p->next;
	}

	sprintf(line,
			"%d, %d, %d, %f\n",
			time,
			cnt,
			total_io,
			((double)cnt / (double)total_io) * 100);
	fputs(line, fp);
	memset(line, 0x00, sizeof(line));
	fclose(fp);
	return 0;
}

int save_csv_iocount(char *path, tiocount **iocount)
{
	file *fp = NULL;
	char line[MAX_CSV_LINE] = {0,};
	tiocount *p = NULL;

	if(iocount == NULL) return -1;

	p = *iocount;

	if((fp = fopen(path, "w")) == NULL)
		return -1;

	while(p != NULL)
	{
		sprintf(line, "%Lu,%d,%d\n", p->sec, p->cnt_r, p->cnt_w);
		fputs(line, fp);
		memset(line, 0x00, sizeof(line));

		p = p->next;
	}
	fclose(fp);
	return 0;
}
