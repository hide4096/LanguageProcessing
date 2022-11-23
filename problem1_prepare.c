//SPDX-FileCopyrightText: 2022 Aso Hidetoshi asouhide2002@gmail.com
//SPDX-License-Identifier: BSD-3-Clause
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>

char* RemoveSymbol(char* filename){
    int fd = open(filename,O_RDONLY);

    struct stat st;
    if(fstat(fd,&st) == -1) return NULL;
    char* removed = (char*)malloc((size_t)st.st_size);
    if(removed == NULL) return NULL;

    for(off_t i=0;i<st.st_size;i++){
        char c;
        read(fd,&c,1);
        if(isalpha(c) != 0 || c == '\n'){
            if(isupper(c) != 0) c+='a'-'A';
            removed[i] = c;
        }else{
            removed[i] = ' ';
        }
    }
    close(fd);
    return removed;
}

int main(){
    char* removed = RemoveSymbol("./hamlet");
    printf("%s\r\n",removed);
    free(removed);
    return 0;
}