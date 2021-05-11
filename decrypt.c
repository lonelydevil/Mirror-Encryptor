#include"encrypt.h"
int main(int argc,char **argv){
	//Check arguments.
	if(argc<3){
		printf("Arguments:Encrypted file name + Key name\n");
		return EXIT_FAILURE;
	}

	//Get file name and file size.
	FILE *fp_encrypt;
	fp_encrypt=fopen(argv[1],"rb+");
	printf("Encrypted file name:\t%s\n",argv[1]);
	size_t encrypt_file_size=getFileSizeFun(fp_encrypt);
	printf("Encrypted file size:\t%zu\n",encrypt_file_size);

	//Get key name and key size.
	FILE *fp_key;
	fp_key=fopen(argv[2],"rb+");
	printf("Key name:\t%s\n",argv[2]);
	size_t key_size=getFileSizeFun(fp_key);
	printf("Key size:\t%zu\n",key_size);

	//Verify key
	if(verifyKeyFun(fp_encrypt,fp_key)!=0){
		printf("Verify failed\n");
		fclose(fp_encrypt);
		fclose(fp_key);
		return EXIT_FAILURE;
	}else{
		printf("Verify succeed!\n");
	}

	//Open encrypted file and prepare for writing.
	FILE *fp_origin;
	char origin_name[strlen(argv[1])];
	strcpy(origin_name,argv[1]);
	origin_name[strlen(origin_name)-4]='\0';
	fp_origin=fopen(origin_name,"wb+");
	printf("Origin file name:\t%s\n",origin_name);

	//Handle data stream.
	ByteMuduleStruct byte_module;
	size_t unsafe_count=0;
	unsigned char each_len;
	for(size_t i=0;i<(key_size/2);i++){
		fread(&each_len,1,1,fp_key);
		fread(&(byte_module.byte_mirror),1,1,fp_key);
		size_t before_count=unsafe_count,after_count=before_count;
		size_t before_pos=ftell(fp_encrypt),after_pos=before_pos;
		for(size_t j=0;j<each_len;j++){
			fread(&(byte_module.byte_in),1,1,fp_encrypt);
			calcMirrorFun(&byte_module,&unsafe_count);
			fwrite(&(byte_module.byte_out),1,1,fp_origin);
		}
		after_count=unsafe_count;
		after_pos=ftell(fp_encrypt);
		if(after_count-before_count!=0){
			printf("From %zu to %zu, unsafe count:\t%d, unsafe rate:\t%.3f\n",
					before_pos,after_pos,
					after_count-before_count,
					(double)(after_count-before_count)
					/(double)(after_pos-before_pos));
		}
	}

	//Verify Encrypted file size
	printf("Origin file size:\t%zu\n",getFileSizeFun(fp_origin));

	//Calculate unsafe rate
	double unsafe_rate=(double)unsafe_count/(double)encrypt_file_size;
	printf("Unsafe count:\t%zu\n",unsafe_count);
	printf("Unsafe rate:\t%.3f\n",unsafe_rate);

	//Close all file
	fclose(fp_encrypt);
	fclose(fp_key);
	fclose(fp_origin);

	return 0;
}
