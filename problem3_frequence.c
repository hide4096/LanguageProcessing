//SPDX-FileCopyrightText: 2022 Aso Hidetoshi asouhide2002@gmail.com
//SPDX-License-Identifier: BSD-3-Clause
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>

int** FreqCharaEx(char* filename){
    int fd = open(filename,O_RDONLY);
    
    //アルファベットと空白と改行
    int** retfreq = (int**)calloc(sizeof(int),3*sizeof(int*));
    retfreq[0] = (int*)calloc(sizeof(int),28*sizeof(int));
    retfreq[1] = (int*)calloc(sizeof(int),28*28*sizeof(int));
    retfreq[2] = (int*)calloc(sizeof(int),28*28*28*sizeof(int));

    for(int i=0;i<3;i++) if(retfreq[i] == NULL) return NULL;

    struct stat st;
    if(fstat(fd,&st) == -1) return NULL;

    char past_id,ppast_id;

    for(off_t i=0;i<st.st_size;i++){
        char c;
        char id;
        read(fd,&c,1);
        if(isupper(c) != 0)         id=c-'A';
        else if(islower(c) != 0)    id=c-'a';
        else if(c == ' ')           id=26;
        else if(c == '\n')          id=27;

        retfreq[0][id]++;

        if(i > 0) retfreq[1][28*past_id+id]++;
        if(i > 1) retfreq[2][28*28*ppast_id+28*past_id+id]++;
        ppast_id = past_id;
        past_id = id;
    }

    close(fd);
    return retfreq;
}


int main(){
    int** retfreq = FreqCharaEx("./hamlet");
    if(retfreq == NULL) return -1;

    int* freq = retfreq[0];

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

    int* freq2 = retfreq[1];

    char chara2[28*28][2];
    for(int i=0;i<28;i++){
        for(int j=0;j<28;j++){
            chara2[i*28+j][0] = chara[i];
            chara2[i*28+j][1] = chara[j];
        }
    }

    for(int i=0;i<28*28-1;i++){
        for(int j=0;j<28*28-1-i;j++){
            if(freq2[j] < freq2[j+1]){
                int tmp_int = freq2[j];
                freq2[j] = freq2[j+1];
                freq2[j+1] = tmp_int;
                for(int k=0;k<2;k++){
                    char tmp_char = chara2[j][k];
                    chara2[j][k] = chara2[j+1][k];
                    chara2[j+1][k] = tmp_char;
                }
            }
        }
    }

    int* freq3 = retfreq[2];

    char chara3[28*28*28][3];

    for(int i=0;i<28;i++){
        for(int j=0;j<28;j++){
            for(int k=0;k<28;k++){
                int t = i*28*28+j*28+k;
                chara3[t][0] = chara[i];
                chara3[t][1] = chara[j];
                chara3[t][2] = chara[k];
            }
        }
    }

    for(int i=0;i<28*28*28-1;i++){
        for(int j=0;j<28*28*28-1-i;j++){
            if(freq3[j] < freq3[j+1]){
                int tmp_int = freq3[j];
                freq3[j] = freq3[j+1];
                freq3[j+1] = tmp_int;
                for(int k=0;k<3;k++){
                    char tmp_char = chara3[j][k];
                    chara3[j][k] = chara3[j+1][k];
                    chara3[j+1][k] = tmp_char;
                }
            }
        }
    }
    printf("1つ組\r\n");
    for(int i=0;i<28;i++) printf("%c|%d\r\n",chara[i],freq[i]);
    printf("2つ組\r\n");
    for(int i=0;i<30;i++) printf("%c%c|%d\r\n",chara2[i][0],chara2[i][1],freq2[i]);
    printf("3つ組\r\n");
    for(int i=0;i<30;i++) printf("%c%c%c|%d\r\n",chara3[i][0],chara3[i][1],chara3[i][2],freq3[i]);

    free(freq);
    return 0;
}