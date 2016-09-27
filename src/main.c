/*
 * main.c
 *
 *  Created on: 2016. 9. 8.
 *      Author: seryugun
 */
#include "engine.h"

char *g_path = "/mnt/data/GoogleDrive/2015_03_SimpleHAN/Research/9#4/";
char *g_files[] = {"zerber.nqz", "blktrace_sdc2(surf_ransom)2_list", "blktrace_sdc2(install_sw)_list", "blktrace_sdc2(web_surfing)_list"};
//char *g_files[] = {"blktrace_sdc2(surf_ransom)2_list"};
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
		//get_detect(io, &detect, &total_io);
		p_io = io;
		while(p_io != NULL)
		{
			p_io_next = get_detect_time(p_io, 10, &detect, &total_io);
			/*
			//printf("%d - %d\tvalue\t%d\n", p_io->sec, p_io->sec + 2, )
			p_detect = detect;
			while(p_detect != NULL)
			{
				if(p_detect->cnt > 0)
					printf("%d.%d\t%d\t%d\t%f\n", p_detect->sec, p_detect->nano_sec, p_detect->cnt, total_io, ((double)p_detect->cnt / (double)total_io) * 100);
				p_detect = p_detect->next;
			}
			*/
			memset(fpath, 0x00, sizeof(fpath));
			sprintf(fpath, "%s%s.detect%s", g_path, (char*)g_files[i], g_ext);
			save_csv_detect(fpath, total_io, &detect);
			free_detect(&detect);
			p_io = p_io_next;
		}
		printf("end!\n");
		free_io(&io);
	}

	/*
	// 리스트를 순차적으로 카운트 갯수를 출력한다
	p_detect = detect;
	while(p_detect != NULL)
	{
		if(p_detect->cnt > 0)
			printf("%d, %d\n", p_detect->sector, p_detect->cnt);
		p_detect = p_detect->next;
	}
	*/
	return 0;
}
