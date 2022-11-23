//SPDX-FileCopyrightText: 2022 Aso Hidetoshi asouhide2002@gmail.com
//SPDX-License-Identifier: BSD-3-Clause
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

char* GenerateSimple2(char* filename,int len){
    int fd = open(filename,O_RDONLY);

    struct stat st;
    if(fstat(fd,&st) == -1) return NULL;
    char* removed = (char*)malloc((size_t)st.st_size);
    if(removed == NULL) return NULL;

    long size = 0;
    for(long i=0;i<st.st_size;i++){
        char c;
        read(fd,&c,1);
        if(isalpha(c) != 0 || c == '\n' || c == ' '){
            if(isupper(c) != 0) c+='a'-'A';
            removed[size] = c;
            size++;
        }
    }

    srand(time(NULL));
    char* generated = (char*)malloc(len+1);
    if(removed == NULL) return NULL;

    srand(time(NULL));
    long r = size*((float)rand()/RAND_MAX);
    char A = removed[r];
    generated[0] = A;
    for(int i=1;i<len;i++){
        r = size*((float)rand()/RAND_MAX);
        while(removed[r] != A){
            r++;
            if(r>=size-1) r = size*((float)rand()/RAND_MAX);
        }
        A = removed[r+1];
        generated[i] = A;
    }

    free(removed);
    close(fd);
    return generated;
}


int main(){
    char* generated = GenerateSimple2("./hamlet",1000);
    if(generated == NULL) return -1;

    printf("%s\r\n",generated);

    free(generated);
    return 0;
}