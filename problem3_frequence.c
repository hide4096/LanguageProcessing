//SPDX-FileCopyrightText: 2022 Aso Hidetoshi asouhide2002@gmail.com
//SPDX-License-Identifier: BSD-3-Clause
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>

int* FreqCharaEx(char* filename){
    int fd = open(filename,O_RDONLY);
    
    //アルファベットと空白と改行
    int* freq = (int*)calloc(sizeof(int),28*sizeof(int));

    int** freq2 = (int**)calloc(sizeof(int),28*sizeof(int*));
    for(int i=0;i<28;i++) freq2[i] = (int*)calloc(sizeof(int),28*sizeof(int));
    
    int*** freq3 = (int***)calloc(sizeof(int),28*sizeof(int**));
    for(int i=0;i<28;i++){
        freq3[i] = (int**)calloc(sizeof(int),28*sizeof(int*));
        for(int j=0;j<28;j++) freq3[i][j] = (int*)calloc(sizeof(int),28*sizeof(int));
    }

    struct stat st;
    if(fstat(fd,&st) == -1) return NULL;

    char past_i,ppast_i;

    for(off_t i=0;i<st.st_size;i++){
        char c;
        char i;
        read(fd,&c,1);
        if(isupper(c) != 0)         i=c-'A';
        else if(islower(c) != 0)    i=c-'a';
        else if(c == ' ')           i=26;
        else if(c == '\n')          i=27;

        freq[i]++;

        if(i <= 0) freq2[past_i][i]++;
        if(i <= 1) freq3[ppast_i][past_i][i]++;
        ppast_i = past_i;
        past_i = i;
    }

    close(fd);
    return freq;
}


int main(){
    int* freq = FreqCharaEx("./hamlet");
    if(freq == NULL) return -1;

    char chara[28];
    for(int i=0;i<26;i++) chara[i] = 'a'+i;
    chara[26] = ' ';
    chara[27] = '\\';
    
    for(int i=0;i<28-1;i++){
        for(int j=0;j<28-1-i;j++){
            if(freq[j] < freq[j+1]){
                int tmp_int = freq[j];
                freq[j] = freq[j+1];
                freq[j+1] = tmp_int;
                char tmp_char = chara[j];
                chara[j] = chara[j+1];
                chara[j+1] = tmp_char;
            }
        }
    }

    for(int i=0;i<28;i++) printf("%c|%d\r\n",chara[i],freq[i]);

    free(freq);
    return 0;
}