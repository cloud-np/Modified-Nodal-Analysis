//
// Created by cloud on 11/20/2020.
//

#ifndef ERGASIAPROSOMOIWSHSKYKLWMATWN_PARSER_H
#define ERGASIAPROSOMOIWSHSKYKLWMATWN_PARSER_H


#include <stdio.h>
#include <stdlib.h>

void print_file(char* file_path){
    FILE* fp;
    fp = fopen(file_path, "r");

    if (fp == NULL) {perror("Opening the file failed "); exit(-1);}
    printf("Hello!");

    fclose(fp);
}

#endif //ERGASIAPROSOMOIWSHSKYKLWMATWN_PARSER_H
