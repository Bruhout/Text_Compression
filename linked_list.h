
typedef struct NODE {
    void *data;
    struct NODE *next_node;
} NODE;

NODE *create_node(void *data_element);
/*
Returns pointer to the node created.
Returns NULL if memory allocation failed.
*/
//---------------------------------------------
NODE *create_list(void *data_element);
/*
Returns pointer the first node of the list.
The next_node attribute is set to NULL.
Returns -1 if memory allocation error.
*/
//---------------------------------------------
int insert_at_beginning(NODE **first_node_ptr, void *data_element);
/*
list is passed as a NODE**, a pointer to the pointer to the first node.
This is because the NODE* needs to be passed by reference.
Returns -2 if invalid link passed
Returns -1 if memory allocation error
Return 0 on successful insertion
*/
//---------------------------------------------
int insert_at_end(NODE *first_node, void *data_element);
/*
Returns -2 if invalid linked list passed
Returns -1 if memory allocation error
Return 0 on successful insertion
*/
//---------------------------------------------
int list_length(NODE *list_head);
/*
Returns -2 if invalid linked list passed
Otherwise returns integer count of the nodes in the list
*/
//---------------------------------------------
int insert_at_index(NODE *list_head, void *data_element, int index);
/*
Returns -1 in case of memory allocation error
Returns -2 if invalid linked list is passed
Returns -3 if invalid index is passed. (index<0 or index>=list_length(list))
Otherwise returns 0 on successful insersertion. 
*/
//---------------------------------------------
int print_list_char(NODE *head_node);
int print_list_int(NODE *first_node);
/*
print_list_type, The function must be defined for each type that you wish to support printing.
By default, the library only includes char* and int.
Returns -2 if invalid linked list is passed
Otherwise, returns 0 if successfully executed.
*/
//---------------------------------------------
int custom_print(NODE* head_node, void (*print_f)(void*));
/*
This lets you use a custom definition of how you would like the void* to be printed.
The user passes a self defined function.
This function specifies what type void* points to and how its to be printed.
custom_print, the calls this user defined function over all the nodes in the list.
P.S.: the user function can actually be doing anything, so maybe you can use this as a general functionality
to call any function over the entire list. IDK try it
*/
//---------------------------------------------
void *indexing(NODE *first_node, int index);
/*
Since the list only stores void*, indexing will return a pointer to the data.
This pointer must be dereferenced to access the data.
This is done so that the same indexing function can be used for all data types.
Returns NULL if index is invalid. (index<0 or index>=list_length(list))
Returns NULL if invalid linked list is passed
*/
//---------------------------------------------
void concatenate(NODE *first_list, NODE *second_list);
/*
No return value from this function.
The second_list is placed at the end of the first list.
The contatenated list is stored in the first_list pointer.
*/
//---------------------------------------------
void delete_node(NODE **list, int index);
/*
list is passed as a NODE**, a pointer to the pointer to the first node.
This is because the NODE* needs to be passed by reference.
No return value from this function.
Execution terminated if invalid linked list passed
Execution terminated if invalid index passed
*/
//---------------------------------------------
int free_list(NODE* head_node);
/*
Goes through the list freeing node-by-node.
Dont try to access the list after freeing it
I dont know what kinda errors u gonna get, but itll be Undefined Behaviour.
Returns 0 if list sucessfully freed.
Returns -2 if invalid linked list passed.
*/
NODE* LlFromArray_int(int* array_ptr, int length);
/*
Works only for integer arrays.
Returns a pointer to the head_node of the created linked_list.
Length controls the index till which the linked_list is created.
*/
int ArrayFromLl_int(NODE* head_node, int* array_ptr, int length);
/*
Memory must be allocated before calling the functions.
Length controls the index till which the array is populated.
*/

int search_list(NODE* head_node, void* data_element, int(*compare)(void*, void*));
/*
Searches the list for a given data_element and returns its index.
The function to compare two data_elements must be defined by the user.
This is done to allow this function to work with any datatype.
Returns -1 if the data_element is not found within the given list.
*/

int search_list_char(NODE* head_node, char* word);
/*
Implementation of search list for char* type.
Comparison is done using strcasecmp.
Returns -1 if element is not found.
*/

int search_list_int(NODE* head_node, char* word);
/*
Implementation of search list for int type.
Comparision is done using the '==' operator.
Returns -1 if element not found.
*/