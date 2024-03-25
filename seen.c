#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "lib/linked_list.h"
#include <ctype.h>

#define MAX_WORD_LENGTH 50

typedef struct word_node
{
    char word[MAX_WORD_LENGTH];
    int count;
    int compression;
} word_node;


//make a 256 long array containing key_value pairs where compression value is greatest.
//Now these will be replaced. through the compression algo.

//======================================================================

int remove_newline(char *word)
{
    if (word == NULL)
    {
        printf("Invalid string passed \n");
        return -1;
    }
    char *buffer0 = word;
    while (*buffer0 != '\0')
    {
        if (*buffer0 == '\n')
        {
            *buffer0 = '\0';
            return 0;
        }
        buffer0 = buffer0 + sizeof(char);
    }
    return 2;
}
//======================================================================
bool word_node_comp(word_node* node, char* word) {
    if (strcasecmp(node->word, word)==0) {
        return true;
    }
    else {
        return false;
    }
}
//======================================================================
int seen_check(NODE *head_node, char *word)
{
    NODE *buffer_node = head_node;
    while (buffer_node != NULL)
    {
        if (word_node_comp((word_node*)buffer_node->data, word) == true)
        {
            ((word_node*)buffer_node->data)->count++;
            return 0; // means found
        }
        buffer_node = buffer_node->next_node;
    }
    return 1; // means not found
}

//======================================================================

NODE* generate_seen(FILE* text) {//creates a linked_list of all the new words
                                 //prints out the words with their counts
    FILE *seen = fopen("seen.txt", "w");
                                
    word_node* heading=malloc(sizeof(word_node)); 
    heading->count=0;
    heading->compression=0;                             
    strcpy(heading->word, "WORDS");             
                                                  
    NODE *seen_list = create_list((void *)heading);
    char bufferM[MAX_WORD_LENGTH];
    char letter;
    int word_head = 0;
    char n = '\n';
    while (fread(&letter, sizeof(char), 1, text) != 0)
    {
        if (isalnum(letter) == 0 || word_head==49)
        {
            bufferM[word_head] = '\0';
            if (seen_check(seen_list, bufferM) != 0)
            {
                word_node* new_word_node=malloc(sizeof(word_node));
                new_word_node->count=1;
                new_word_node->compression=0;
                strcpy(new_word_node->word, bufferM);      
                insert_at_end(seen_list, new_word_node); 
            }
            word_head = 0;
            continue;
        }
        bufferM[word_head] = letter;
        word_head++;
    }

    //write to file part
    NODE *node_buffer = seen_list;
    while (node_buffer != NULL)
    {                                                                                             //
        fwrite(((word_node*)node_buffer->data)->word, strlen((char *)node_buffer->data), 1, seen);  //
        fwrite(&n, 1, 1, seen);                                                                     //-=--=-=-=-=-=-=-=-=-=-=-=-=-=-
        node_buffer = node_buffer->next_node;                                                       //
    }                                                                                             //  

    return seen_list;

    fclose(text);
    fclose(seen);
}
//======================================================================
void get_compression(NODE* head_node) {
    int compression;
    int length;
    int count;

    NODE* buffer_node=head_node;
    while (buffer_node!=NULL) {

        //saving=(length * count) - length - count - 1
        length=strlen(((word_node*)buffer_node->data)->word);
        count=((word_node*)buffer_node->data)->count;

        compression=(length * count) - length - count -1;

        ((word_node*)buffer_node->data)->compression=compression;

        buffer_node=buffer_node->next_node;
    }
}
//======================================================================

void custom_print_func(void* data_ptr) {
    printf("%s || count=%i :: compression::%i\n" , ((word_node*)data_ptr)->word, ((word_node*)data_ptr)->count, ((word_node*)data_ptr)->compression);
}
//======================================================================

bool incheck(int element, int array[], int length) {
    for (int i=0; i<length; i++) {
        if (array[i]==element) {
            return true;
        }
    }
    return false;
}

int choose_max(NODE* seen_list, int used[]) {
    NODE* buffer_node=seen_list;
    int counter=0;
    int current_max=-50;
    int current_max_index=0;
    while (buffer_node!=NULL) {
        if (((word_node*)buffer_node->data)->compression>current_max && (incheck(counter, used, 256)==false) && ((word_node*)buffer_node->data)->compression>0) {
            current_max=((word_node*)buffer_node->data)->compression;
            current_max_index=counter;
        }
        buffer_node=buffer_node->next_node;
        counter++;
    }
    return current_max_index;
}
//======================================================================

int main(int argc, char* argv[])
{   
    FILE* text=fopen(argv[1], "r");
    NODE* seen_list=generate_seen(text);

    get_compression(seen_list);

    custom_print(seen_list, custom_print_func);

    printf("done\n");
    printf("//======================================================================\n");


    int total_compression=0;
    int max_compression_index;

    int used[256];
    for (int j=0; j<256; j++) {
        used[j]=-1;
    }

    for (int i=0; i<256; i++) {
        max_compression_index=choose_max(seen_list, used);
        used[i]=max_compression_index;
        total_compression+=((word_node*)indexing(seen_list, max_compression_index))->compression;
    }

    //printf("%i\n" , total_compression);
    for (int p=0; p<256; p++) {
        printf("%ith--%s::saved %i\n", used[p] , ((word_node*)indexing(seen_list, used[p]))->word, ((word_node*)indexing(seen_list, used[p]))->compression);
    }
}