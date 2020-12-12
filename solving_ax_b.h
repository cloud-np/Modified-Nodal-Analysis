//#include "hashing.h"


void alter_array_B(double* B, int* nodes_pos, double net_item_value, char type){

}

void alter_matrix_A(double** A, const int* nodes_pos, double net_item_value, char type){
    int left_node_pos = nodes_pos[0];
    int right_node_pos = nodes_pos[1];
    if(type == 'R'){
        // -1 means the node is the ground.
        // example -> R1 C B 3.4 -> G1 = 1 / 3.4
        // Matrix A changes:   A[C][C] = G1
        //                     A[B][B] = G1
        //                     A[B][C] = -G1
        //                     A[C][B] = -G1
        if(left_node_pos != -1 && right_node_pos != -1){
            // A[0][0]
            A[left_node_pos][left_node_pos] += 1.00 / net_item_value;
            // A[1][1]
            A[right_node_pos][right_node_pos] += 1.00 / net_item_value;
            // A[0][1]
            A[left_node_pos][right_node_pos] += -1 * (1.00 / net_item_value);
            // A[1][0]
            A[right_node_pos][left_node_pos] += -1 * (1.00 / net_item_value);
        }else if(left_node_pos == -1)
            A[right_node_pos][right_node_pos] += 1.00 / net_item_value;
        else
            A[left_node_pos][left_node_pos] += 1.00 / net_item_value;
    }else if(type == 'V'){
        // A[3][3] = 1
//        if(left_node_pos != -1)
//            A[left_node_pos][left_node_pos] += 1.00;
//        // A[
//        if(right_node_pos != -1)
//            A[right_node_pos][right_node_pos] += 1.00;
    }
}

void fill_the_matrix(MatrixEquation* matrix_equation, FileData* file_data, List** hash_table){
    Node* tmp = file_data->net_list->head_node;

    // We need to iterate all the net_list and
    // change the equation A x = B accordingly
    int i = 0;
    while(tmp != NULL){
        i++;
        // We need to cast to the correct type since the data pointer is void*
        NetItem* net_item = (NetItem*) tmp->data;

        // Get the positions of the nodes in the hash_table.
        int left_n_hash = hash_function(net_item->left_node);
        int right_n_hash = hash_function(net_item->right_node);

        int left_node_pos = -1, right_node_pos = -1;
        // This function basically works like this:
        // 1) We give it a list (we pick the correct list based the hash_id which is always the same for specific str if not gg)
        // 2) We pass the name of the node we are looking for.
        // 3) We pass it a comparing function to determine how the comparing will take place.
        Node* tmp_left = find_node(hash_table[left_n_hash], net_item->left_node, compare_node_names);
        Node* tmp_right = find_node(hash_table[right_n_hash], net_item->right_node, compare_node_names);
        //if(tmp_left == NULL && tmp_right == NULL){ perror("Left node AND Right node are NULL!"); exit(-5);}


//        NodeInfo* epL = (NodeInfo*) tmp_left->data;
//        NodeInfo* epR = (NodeInfo*) tmp_right->data;
//        if(epL != NULL && epR != NULL)
//            printf("%s left-main-pos: %d   right-main-pos: %d", net_item->type, epL->main_table_pos, epR->main_table_pos);

        if(tmp_left != NULL)
            left_node_pos  = ((NodeInfo*) tmp_left->data)->main_table_pos;
        if(tmp_right != NULL)
            right_node_pos = ((NodeInfo*) tmp_right->data)->main_table_pos;
        int nodes_pos[2] = { left_node_pos, right_node_pos };

        // Find which table you gonna alter
        if (net_item->type[0] == 'I')
            alter_array_B(matrix_equation->B, nodes_pos, net_item->value, 'I');
        else if(net_item->type[0] == 'R')
            alter_matrix_A(matrix_equation->A, nodes_pos, net_item->value, 'R');
        else if(net_item->type[0] == 'V'){
            alter_array_B(matrix_equation->B, nodes_pos, net_item->value, 'V');
            alter_matrix_A(matrix_equation->A, nodes_pos, net_item->value, 'V');
        }

        tmp = tmp->next;
    }
}
