#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

char* GenerateSimple(char* filename,int len,int rank){
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
            removed[size] = c;
            size++;
        }
    }

    srand(time(NULL));
    char* generated = (char*)malloc(len);
    if(removed == NULL) return NULL;

    srand(time(NULL));
    for(int i=0;i<len;i+=rank){
        long r = (size-rank)*((float)rand()/RAND_MAX);
        for(int j=0;j<rank;j++) generated[i+j] = removed[r+j];
    }

    free(removed);
    close(fd);
    return generated;
}


int main(){
    char* generated = GenerateSimple("./Airplane",1000,5);
    if(generated == NULL) return -1;

    printf("%s\r\n",generated);

    free(generated);
    return 0;
}