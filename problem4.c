#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

char* GenerateFirst(char* filename,int size){
    srand(time(NULL));
    int fd = open(filename,O_RDONLY);

    struct stat st;
    if(fstat(fd,&st) == -1) return NULL;
    char* generated = (char*)malloc(size);
    if(generated == NULL) return NULL;

    for(int i=0;i<size;i++){
        char c;
        printf("%ld\r\n",(off_t)st.st_size*(double)(rand()/RAND_MAX));
        lseek(fd,0,0);
        read(fd,&c,1);
        generated[i] = c;
    }

    close(fd);
    return generated;
}

int main(){
    printf("%s\r\n",GenerateFirst("./problem1_prepare.c",100));
    return 0;
}