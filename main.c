#include <stdio.h>
#include "parser.h"
#include "net_node_class.h"
#include "misc_functions.h"
#include "solving_ax_b.h"
#include <stdint.h>
#include <conio.h>

void free_memory(FileData*, MatrixEquation*, List**);

int compare(void* search_data, void* data){
    // We do not dereference it !
    int* search = (int*)search_data;
    int* try    = (int*)data;

    if(search > try){
        return 1;
    }else if(search == try){
        return 0;
    }else if(search < try){
        return -1;
    }
    return -9;
}

void print_the_system(FileData* file_data){

    printf("\n\n\t\t\t\t\tNET LIST ITEMS\n");
    print_custom_list(file_data->net_list, print_custom_node);

    printf("\n\n\t\t\t\t\tNODE LIST\n");
    print_custom_list(file_data->nodes_list, print_hash_table_list);
}

void solve_the_circuit(double* A, double* x, double* B){

}

int main() {

    List** hash_table = new_HashTable();
    FileData* file_data = get_data_from_txt("../dataset/test.txt", hash_table);
    //FileData* file_data = get_data_from_txt("../dataset/ibmpg1.spice.txt", hash_table);
    //FileData* file_data = get_data_from_txt("../dataset/parser_test2.txt", hash_table);



    // A x = B
    MatrixEquation* matrix_equation = initialize_the_matrix_equation(file_data);
    fill_the_matrix(matrix_equation, file_data, hash_table);

    print_the_system(file_data);
    print_the_matrix_equation(matrix_equation);
    free_memory(file_data, matrix_equation, hash_table);
    return 0;
}

void free_memory(FileData* file_data, MatrixEquation* matrix_equation, List** hash_table){
    free_FileData(file_data);
    free_HashTable(hash_table);
    free_MatrixEquation(matrix_equation);
}
