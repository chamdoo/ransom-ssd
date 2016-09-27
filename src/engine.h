/*
 * engine.h
 *
 *  Created on: 2016. 9. 8.
 *      Author: seryugun
 */

#ifndef ENGINE_H_
#define ENGINE_H_

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <limits.h>

#ifdef WINDOWS
#define PATH_MAX			256
#else
#endif
#define MAX_CSV_LINE		1024
#define PER_SCAN_COUNTER	0.80
#define PER_SCAN_BYTES		0.80
#define MAX_SCAN_TIME		5
#define MAX_SCAN_NUM		1000
#define MAX_WINDOW_TIME		5

typedef unsigned long long ulong64;
typedef unsigned long ulong;
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;
typedef FILE file;

typedef struct _tio
{
	ulong sec;
	uint nano_sec;
	uchar mark;
	ulong64 sector;
	ushort bytes;
	struct _tio *next;
	struct _tio *prev;
}tio;

typedef struct _tdetect
{
	ulong sec;
	uint nano_sec;
	ulong64 sector;
	uint bytes;
	uint cnt;	// wmib
	struct _tdetect *next;
}tdetect;

typedef struct _tdetect_window
{
	uint cnt_win;
	tdetect **detect;
	uint *total_io;
}tdetect_win;

typedef struct _tiocount
{
	ulong sec;
	uint cnt_r;
	uint cnt_w;
	struct _tiocount *next;
}tiocount;

/* util */
char *split_char(char *str, char c, char **buf);
uint dp_point(uint dp, uint digit);

/* io */
int init_io(tio **io);
int free_io(tio **io);
tio *find_io_time(tio *io, ulong sec);
tio *find_io_near_time(tio *io, ulong sec);

/* csv */
int load_csv_data(char *path, tio **io);
int save_csv_detect(char *path, uint time, uint total_io, tdetect **detect);
int save_csv_iocount(char *path, tiocount **iocount);

/* detect */
int init_detect(tdetect **detect);
int free_detect(tdetect **detect);
tdetect *add_detect(tdetect *detect);
tdetect *find_detect(ulong64 sector, tdetect *detect);
int get_detect(tio *io, tdetect **detect, uint *total_io);
tio *get_detect_time(tio *io, ulong last_sec, tdetect **detect, uint *total_io);
int get_detect_max_cnt(tdetect *detect);

/* detect_win */
int init_detect_win(uint cnt_win, tdetect_win **detect_win);
int free_detect_win(tdetect_win **detect_win);

/* sec */
int init_iocount(tiocount **iocount);
int free_iocount(tiocount **iocount);
int get_sec_io_count(tio *io, tiocount **iocount);

#endif /* ENGINE_H_ */
