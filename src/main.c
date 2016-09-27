/*
 * main.c
 *
 *  Created on: 2016. 9. 8.
 *      Author: seryugun
 */
#include "engine.h"

/*char *g_path = "/mnt/data/Research/9#4/";*/
/*char *g_files[] = {"zerber.nqz", "blktrace_sdc2(surf_ransom)2_list", "blktrace_sdc2(install_sw)_list", "blktrace_sdc2(web_surfing)_list"};*/
//char *g_files[] = {"blktrace_sdc2(web_surfing)_list"};

char *g_path = "../data/";
char *g_files[] = {"install", "ransom", "surf_ransom", "surf"};
char *g_ext = ".csv";

int main()
{
	tio *io = NULL;
	tdetect *detect = NULL;
	tiocount *iocount = NULL;
	char fpath[PATH_MAX] = {0,};
	int i = 0;

	for(i = 0; i < sizeof(g_files); i ++)
	{
		memset(fpath, 0x00, sizeof(fpath));
		sprintf(fpath, "%s%s%s", g_path, (char*)g_files[i], g_ext);
		load_csv_data(fpath, &io);
		get_detect(io, &detect);
		get_sec_io_count(io, &iocount);
		memset(fpath, 0x00, sizeof(fpath));
		sprintf(fpath, "%s%s.detect%s", g_path, (char*)g_files[i], g_ext);
		save_csv_detect(fpath, &detect);
		sprintf(fpath, "%s%s.iocount%s", g_path, (char*)g_files[i], g_ext);
		save_csv_iocount(fpath, &iocount);
		free_io(&io);
		free_detect(&detect);
		free_iocount(&iocount);
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
