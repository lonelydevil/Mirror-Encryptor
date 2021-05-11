#include"fun_calcMirrorFun.h"

void calcMirrorFun(ByteMuduleStruct *byte_module_p,size_t *unsafe_count){
	byte_module_p->byte_out=(byte_module_p->byte_mirror*2)-byte_module_p->byte_in;
	if(byte_module_p->byte_in==byte_module_p->byte_out){
		(*unsafe_count)++;
	}
	return;
}
