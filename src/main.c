/*
 * main.c
 *
 *  Created on: 2016. 9. 8.
 *      Author: seryugun
 */
#include "engine.h"

char *g_path = "../data/";
char *g_files[] = {"ransom", "install", "surf_ransom", "surf"};
char *g_ext = ".csv";

int main()
{
	tio *io = NULL, *p_io = NULL, *p_io_next = NULL;
	tdetect *detect = NULL;
	char fpath[PATH_MAX] = {0,};
	int i = 0;
	uint total_io = 0;
	uint time = 0;

	for(i = 0; i < sizeof(g_files) / sizeof(char*); i ++)
	{
		time = 0;
		memset(fpath, 0x00, sizeof(fpath));
		sprintf(fpath, "%s%s%s", g_path, (char*)g_files[i], g_ext);
		printf("%s..\n", fpath);
		load_csv_data(fpath, &io);
		p_io = io;
		while(p_io != NULL)
		{
			p_io_next = get_detect_time(p_io, MAX_WINDOW_TIME, &detect, &total_io);
			memset(fpath, 0x00, sizeof(fpath));
			sprintf(fpath, "%soutput/%s.detect%s", g_path, (char*)g_files[i], g_ext);
			save_csv_detect(fpath, time, total_io, &detect);
			time += MAX_WINDOW_TIME;
			free_detect(&detect);
			p_io = p_io_next;
		}
		free_io(&io);
	}

	printf("end!\n");
	return 0;
}
