#include"fun_verifyKeyFun.h"
#include"fun_getFileSizeFun.h"

unsigned char verifyKeyFun(FILE *fp_file,FILE *fp_key){
	size_t file_size=getFileSizeFun(fp_file);
	size_t key_size=getFileSizeFun(fp_key);
	size_t total_len=0;
	unsigned char each_len=0;
	for(size_t i=0;i<(key_size/2);i++){
		fread(&each_len,1,1,fp_key);
		fseek(fp_key,1,SEEK_CUR);
		total_len+=each_len;
	}
	rewind(fp_key);
	printf("Key file length:\t%d\n",total_len);
	if(total_len!=file_size){
		printf("Key file length doesn't match file size.\n");
		return 1;
	}
	printf("Key file length matched!\n");
	return 0;
}
