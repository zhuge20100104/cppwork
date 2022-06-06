
 
#define __STDC_CONSTANT_MACROS
#pragma warning(disable:4996)
#include <stdio.h>

extern "C" {
	#include <libavutil/log.h>
}
int main(int argc, char* argv[]) {
	av_log_set_level(AV_LOG_DEBUG);
	av_log(NULL, AV_LOG_INFO, "Hello world\n");
	return 0;
}
