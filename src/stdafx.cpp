// by jrzanol
// 

#include "stdafx.h"

void Log(const char* str, ...)
{
	static FILE* g_LogFp = NULL;

	if (str)
	{
		char buf[1024];
		char buf2[1024];

		va_list arglist;
		va_start(arglist, str);
		vsprintf(buf, str, arglist);
		va_end(arglist);

		time_t rawnow = time(0);
		tm* now = localtime(&rawnow);

		sprintf(buf2, "%02d/%02d/%02d %02d:%02d:%02d %s\n", now->tm_mday, now->tm_mon + 1, now->tm_year - 100, now->tm_hour, now->tm_min, now->tm_sec, buf);
		printf(buf2);

		if (g_LogFp == NULL)
		{
			char filename[64];
			sprintf(filename, ".\\LOG%02d%02d%02d_%02d%02d.txt", now->tm_year - 100, now->tm_mon + 1, now->tm_mday, now->tm_hour, now->tm_min);

			g_LogFp = fopen(filename, "at");
		}

		if (g_LogFp)
		{
			fprintf(g_LogFp, buf2);
			fflush(g_LogFp);
		}
	}
	else if (g_LogFp)
		fclose(g_LogFp);
}

