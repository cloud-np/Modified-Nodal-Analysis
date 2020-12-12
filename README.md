#Under contruction 🚧 

# Modified-Nodal-Analysis
DC system Modified Nodal Analysis.

### General info
The file format should be like this:
```
R1 node_name_a node_name_b 2
I1 node_name_c node_name_d 9
R2 node_name_c node_name_a 3
V1 node_name_d 0 4
```
For more information: [MNA](https://lpsa.swarthmore.edu/Systems/Electrical/mna/MNA3.html)

### Setup
To run download the project and use the ```test.txt``` file.

```
int main() {
 ...
 
    FileData* file_data = get_data_from_txt("../dataset/test.txt", hash_table);
 
 ...
}
```
