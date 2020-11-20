#include <stdio.h>
#include "list.h"
#include "parser.h"
#include <stdint.h>

typedef enum NodeType { R='R', C='C', L='L', V='V', I='I' } NodeType;

typedef struct NetNode {
    NodeType type;
    char* high_node;
    char* low_node;
    double value;
}NetNode;
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
int main() {

    print_file("hello.txt");
//    List* my_list = new_List("int");
//    add_list_node(my_list, 10);
//    add_list_node(my_list, 6);
//    add_list_node(my_list, 1);
//    add_list_node(my_list, 45);
//    add_list_node(my_list, 9);
//    sort_list(my_list, compare);
//
//    print_list(my_list);

    return 0;
}
