cmake_minimum_required(VERSION 3.15)

project(mirror_encryptor)

add_executable(genkey genkey.c fun_getFileSizeFun.c)
add_executable(encrypt encrypt.c fun_getFileSizeFun.c fun_calcMirrorFun.c fun_verifyKeyFun.c)
add_executable(decrypt decrypt.c fun_getFileSizeFun.c fun_calcMirrorFun.c fun_verifyKeyFun.c)

