all: genkey encrypt decrypt
.PHONY: all
genkey:
	@cc \
		-c \
		*.c
	@cc \
		genkey.o \
		fun_getFileSizeFun.o \
		-o \
		genkey
encrypt:
	@cc \
		-c \
		*.c
	@cc \
		encrypt.o \
		fun_getFileSizeFun.o \
		fun_calcMirrorFun.o \
		fun_verifyKeyFun.o \
		-o \
		encrypt
decrypt:
	@cc \
		-c \
		*.c
	@cc \
		decrypt.o \
		fun_getFileSizeFun.o \
		fun_calcMirrorFun.o \
		fun_verifyKeyFun.o \
		-o \
		decrypt
cl:
	@rm \
		genkey \
		encrypt \
		decrypt \
		*.o
