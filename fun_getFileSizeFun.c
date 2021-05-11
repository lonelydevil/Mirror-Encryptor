#include"fun_getFileSizeFun.h"

size_t getFileSizeFun(FILE *fp){
	fseek(fp,0,SEEK_END);
	size_t ret_val=ftell(fp);
	rewind(fp);
	return ret_val;
}
