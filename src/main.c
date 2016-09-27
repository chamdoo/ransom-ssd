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
	tio *io = NULL, *p_io = NULL, *p_io_next = NULL, *p_io_start = NULL;
	tdetect *detect = NULL;
	char fpath[PATH_MAX] = {0,};
	int i_file = 0, i_win = 0;
	uint total_io = 0;
	uint time = 0;

	for(i_file = 0; i_file < sizeof(g_files) / sizeof(char*); i_file ++)
	{
		time = 0;
		memset(fpath, 0x00, sizeof(fpath));
		sprintf(fpath, "%s%s%s", g_path, (char*)g_files[i_file], g_ext);
		printf("%s..", fpath);
		load_csv_data(fpath, &io);
		p_io = io;

		for(i_win = 0; i_win < MAX_WINDOW_TIME; i_win ++)
		{
			p_io = io;
			time = 0;
			while(p_io != NULL)
			{
				//p_io_start = find_io_time(p_io, time + i_win);
				p_io_start = find_io_near_time(p_io, time + i_win);
				if(p_io_start == NULL) break;
				p_io_next = get_detect_time(p_io_start, time + MAX_WINDOW_TIME, &detect, &total_io);
				memset(fpath, 0x00, sizeof(fpath));
				sprintf(fpath, "%soutput/%s.detect%s", g_path, (char*)g_files[i_file], g_ext);

				if(total_io > 0)
					save_csv_detect(fpath, time + i_win, total_io, &detect);
				time += MAX_WINDOW_TIME;
				free_detect(&detect);
				p_io = p_io_next;
			}
		}
		printf("done\n");
		free_io(&io);
	}

	printf("job is done\n");
	return 0;
}
