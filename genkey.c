#include"genkey.h"
int main(int argc,char **argv){

	//Quit if there's no argument.
	if(argc<2){
		printf("File name, please!\n");
		return EXIT_FAILURE;
	}

	//Get file name and file size.
	FILE *fp_origin;
	fp_origin=fopen(argv[1],"rb+");
	printf("File name:\t%s\n",argv[1]);
	size_t file_size=getFileSizeFun(fp_origin);
	printf("File size:\t%zu\n",file_size);
	fclose(fp_origin);

	//Handle data stream.
	FILE *fp_key;
	char key_name[strlen(argv[1])];
	strcpy(key_name,argv[1]);
	strcat(key_name,".mirror_key");
	fp_key=fopen(key_name,"wb+");
	printf("Key file name:\t%s\n",key_name);

	size_t len_count=0;
	unsigned char each_len=0,each_mirror=0;
	srand(time(0));

	for(size_t i=0;i<file_size;i++){
		//Generate and write.
		each_len=rand()%0x100;
		if(each_len==0x00){
			continue;
		}
		if(each_len+len_count>=file_size){
			each_len=file_size-len_count;
		}
		len_count+=each_len;
		each_mirror=rand()%0x100;

		fwrite(&each_len,1,1,fp_key);
		fwrite(&each_mirror,1,1,fp_key);

		//Check key properties.
		if(len_count>file_size){
			printf("Key length overgrown, make sure your file is bigger than 255byte!\n");
			return EXIT_FAILURE;
		}
		if(len_count==file_size){
			printf("Key length checked successful!\n");
			break;
		}
	}

	printf("Key file size:\t%zu\n",getFileSizeFun(fp_key));
	fclose(fp_key);

	return EXIT_SUCCESS;
}
