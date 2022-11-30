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

char* GenerateSimple3(char* filename,int len){
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
    char* generated = (char*)malloc(len+2);
    if(generated == NULL) return NULL;

    long r = (size-1)*((float)rand()/RAND_MAX);
    char A[2];
    A[0] = removed[r];

    while(removed[r] != A[0]){
        r++;
        if(r>=size-2) r = (size-2)*((float)rand()/RAND_MAX);
    }
    A[1] = removed[r+1];

    generated[0] = A[0];
    generated[1] = A[1];

    for(int i=2;i<len;i++){
        r = size*((float)rand()/RAND_MAX);
        while(removed[r] != A[0] || removed[r+1] != A[1]){
            r++;
            if(r>=size-2) r = (size-2)*((float)rand()/RAND_MAX);
        }
        A[0] = A[1];
        A[1] = removed[r+2];
        generated[i] = A[1];
    }

    free(removed);
    close(fd);
    return generated;
}

int main(){
    char* generated = GenerateSimple3("./pg11.txt",1000);
    if(generated == NULL) return -1;

    printf("%s\r\n",generated);

    free(generated);
    return 0;
}