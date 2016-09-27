/*
 * main.c
 *
 *  Created on: 2016. 9. 8.
 *      Author: seryugun
 */
#include "engine.h"

char *g_path = "../data/";
char *g_files[] = {"install", "ransom", "surf_ransom", "surf"};
char *g_ext = ".csv";

int main()
{
	tio *io = NULL, *p_io = NULL, *p_io_next = NULL;
	tdetect *detect = NULL, *p_detect = NULL;
	tiocount *iocount = NULL;
	char fpath[PATH_MAX] = {0,};
	int i = 0;
	uint total_io = 0, t = 0;

	for(i = 0; i < sizeof(g_files); i ++)
	{
		memset(fpath, 0x00, sizeof(fpath));
		sprintf(fpath, "%s%s%s", g_path, (char*)g_files[i], g_ext);
		load_csv_data(fpath, &io);
		p_io = io;
		while(p_io != NULL)
		{
			p_io_next = get_detect_time(p_io, 10, &detect, &total_io);
			memset(fpath, 0x00, sizeof(fpath));
			sprintf(fpath, "%s%s.detect%s", g_path, (char*)g_files[i], g_ext);
			save_csv_detect(fpath, total_io, &detect);
			free_detect(&detect);
			p_io = p_io_next;
		}
		printf("end!\n");
		free_io(&io);
	}

	return 0;
}
