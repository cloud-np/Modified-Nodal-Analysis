#ifndef ERGASIAPROSOMOIWSHSKYKLWMATWN_NET_NODE_CLASS_H
#define ERGASIAPROSOMOIWSHSKYKLWMATWN_NET_NODE_CLASS_H
#include "list.h"

typedef struct NetItem {
    //NodeType type;
    char* type;
    char* left_node;
    char* right_node;
    float value;
}NetItem;

typedef struct NodeInfo {
    char* name;
    int main_table_pos;
    int hash_table_pos;
}NodeInfo;

typedef struct FileData {
    List* net_list;
    List* nodes_list;
    List* volt_list;
}FileData;

typedef struct MatrixEquation {
    float** A;
    float* x;
    float* B;
    int len_of_arrays;
}MatrixEquation;

void free_FileData(FileData* file_data){
    free_list(file_data->net_list);
    free_list(file_data->nodes_list);
    free_list(file_data->volt_list);
    free(file_data);
}

MatrixEquation* initialize_the_matrix_equation(FileData* file_data){
    int n = file_data->nodes_list->size;
    int m2 = file_data->volt_list->size;

    MatrixEquation* matrix_equation = (MatrixEquation*) malloc(sizeof(MatrixEquation));
    if (!matrix_equation) { perror("Malloc failed at create_A_arr!\n"); exit(-2);}

    // No need to do n - 1 because we
    // don't add at all at the parsing phase the ground node 0
    // (n - 1) + m2
    int len_of_arrays = n + m2;

    // Initialize the A matrix
    // We use calloc because :
    // The calloc() function then gives all the bits of each element an initial value of 0.
    // https://www.ibm.com/support/knowledgecenter/en/ssw_ibm_i_73/rtref/calloc.htm
    float** A = (float**) calloc(len_of_arrays, sizeof(float*));
    if (!A) {perror("Calloc failed to create A matrix!\n"); exit(-2);}
    for (int i = 0; i < len_of_arrays; i++){
        A[i] = (float*) calloc(len_of_arrays, sizeof(float));
        if (!A[i]) {printf("Calloc failed to create A[%d]!\n", i); exit(-2);}
    }

    // Initialize the x array
    float* x = (float*) calloc(len_of_arrays, sizeof(float*));
    if (!x) {perror("Calloc failed to create x array!\n"); exit(-2);}

    // Initialize the B array
    float* B = (float*) calloc(len_of_arrays, sizeof(float*));
    if (!B) {perror("Calloc failed to create B array!\n"); exit(-2);}

    matrix_equation->A = A;
    matrix_equation->x = x;
    matrix_equation->B = B;
    matrix_equation->len_of_arrays = len_of_arrays;


    return matrix_equation;
}

void free_MatrixEquation(MatrixEquation* matrix_equation){
    for(int i = 0; i < matrix_equation->len_of_arrays; i++)
        free(matrix_equation->A[i]);
    free(matrix_equation->x);
    free(matrix_equation->B);
    free(matrix_equation);
}

int compare_node_names(void* search_name, void* data){
    // We do not dereference it !
    const char* search = (char*) search_name;
    NodeInfo* try = (NodeInfo*) data;

    return strcmp(search, try->name);
}

#endif //ERGASIAPROSOMOIWSHSKYKLWMATWN_NET_NODE_CLASS_H
