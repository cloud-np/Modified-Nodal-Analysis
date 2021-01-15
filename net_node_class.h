#ifndef ERGASIAPROSOMOIWSHSKYKLWMATWN_NET_NODE_CLASS_H
#define ERGASIAPROSOMOIWSHSKYKLWMATWN_NET_NODE_CLASS_H
#include "list.h"

// This should be pointing to a val at A table e.g:
// A[0][3]
// row: 0
// col: 3

typedef struct SparseItem{
    unsigned int row;
    unsigned int col;
    double* val;  // Just so we won't be copying the values we point to the existing ones.
}SparseItem;

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
    double** A;
    double* x;
    double* B;
    int len_of_arrays;
}MatrixEquation;

void free_FileData(FileData* file_data){
    free_list(file_data->net_list);
    free_list(file_data->nodes_list);
    free_list(file_data->volt_list);
    free(file_data);
}

SparseItem* create_sparse_table(double** A, int matrix_len, int *sparse_matrix_len){
    SparseItem* sparse_matrix = (SparseItem*) malloc(sizeof(SparseItem) * matrix_len);
    if(!sparse_matrix){perror("MALLOC ON sparse matrix A FAILED"); exit(-5);}

    static int pos = 0;
    for(int i = 0; i < matrix_len; i++){
        for(int j = 0; j < matrix_len; j++){
            if (A[i][j] != 0){
                sparse_matrix[pos].row = i;
                sparse_matrix[pos].col = j;
                sparse_matrix[pos].val = &A[i][j];
                ++pos;
            }
        }
    }

    *sparse_matrix_len = pos;
    return sparse_matrix;
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
    double** A = (double**) calloc(len_of_arrays, sizeof(double*));
    if (!A) {perror("Calloc failed to create A matrix!\n"); exit(-2);}
    for (int i = 0; i < len_of_arrays; i++){
        A[i] = (double*) calloc(len_of_arrays, sizeof(double));
        if (!A[i]) {printf("Calloc failed to create A[%d]!\n", i); exit(-2);}
    }

    // Initialize the x array
    double* x = (double*) calloc(len_of_arrays, sizeof(double*));
    if (!x) {perror("Calloc failed to create x array!\n"); exit(-2);}

    // Initialize the B array
    double* B = (double*) calloc(len_of_arrays, sizeof(double*));
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
