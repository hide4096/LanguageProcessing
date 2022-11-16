#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

float* PrbtyChara(char* filename){
    int fd = open(filename,O_RDONLY);
    
    //アルファベットと空白と改行
    int freq[28] = {0};
    float* prbty = (float*)calloc(sizeof(float),28*sizeof(float));
    if(prbty == NULL) return NULL;

    struct stat st;
    if(fstat(fd,&st) == -1) return NULL;

    long sum = 0;
    for(off_t i=0;i<st.st_size;i++){
        char c;
        read(fd,&c,1);
        sum++;
        if(isupper(c) != 0)         freq[c-'A']++;
        else if(islower(c) != 0)    freq[c-'a']++;
        else if(c == ' ')           freq[26]++;
        else if(c == '\n')          freq[27]++;
        else sum--;
    }

    for(int i=0;i<28;i++){
        prbty[i] = freq[i] / (float)sum;
    }

    close(fd);
    return prbty;
}


int main(){
    float* prbty = PrbtyChara("./Airplane");
    if(prbty == NULL) return -1;

    char chara[28];
    for(int i=0;i<26;i++) chara[i] = 'a'+i;
    chara[26] = ' ';
    chara[27] = '\n';

    srand(time(NULL));

    for(int i=0;i<500;i++){
        float r = (float)rand()/RAND_MAX;
        int j=0;
        while(r>0.){
            r-=prbty[j];
            j++;

            if(j>28) return -1;
        }
        printf("%c",chara[j-1]);
    }

    printf("\r\n");

    return 0;
}