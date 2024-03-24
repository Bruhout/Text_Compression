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
} word_node;

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

void custom_print_func(void* data_ptr) {
    printf("%s-->count=%i\n" , ((word_node*)data_ptr)->word, ((word_node*)data_ptr)->count);
}

void get_compression(NODE* head_node) {
    int compression;
    word_node* word_n;
    NODE* buffer_node=head_node;
    while (buffer_node!=NULL) {
        word_n=(word_node*)buffer_node->data;
        compression=((strlen(word_n->word) * word_n->count) - word_n->count - strlen(word_n->word) - 1);
        printf("%s-->comp=%i\n", word_n->word, compression);
        buffer_node=buffer_node->next_node;
    }
}

void generate_seen(FILE* text) {
    FILE *seen = fopen("seen.txt", "w");
                                                  //
    word_node* heading=malloc(sizeof(word_node));   //
    heading->count=0;                               //--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    strcpy(heading->word, "WORDS");                 //
                                                  //
    NODE *seen_list = create_list((void *)heading);
    char bufferM[MAX_WORD_LENGTH];
    char letter;
    int word_head = 0;
    char *word_memory;
    char n = '\n';
    while (fread(&letter, sizeof(char), 1, text) != 0)
    {
        if (isalnum(letter) == 0)
        {
            bufferM[word_head] = '\0';
            if (seen_check(seen_list, bufferM) != 0)
            {                                                         //
                word_node* new_word_node=malloc(sizeof(word_node));     //
                new_word_node->count=1;                                 //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
                strcpy(new_word_node->word, bufferM);                   //-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=
                insert_at_end(seen_list, new_word_node);                //
            }                                                         //
            word_head = 0;
            continue;
        }
        bufferM[word_head] = letter;
        word_head++;
    }
    custom_print(seen_list, custom_print_func);
    NODE *node_buffer = seen_list;
    while (node_buffer != NULL)
    {                                                                                             //
        fwrite(((word_node*)node_buffer->data)->word, strlen((char *)node_buffer->data), 1, seen);  //
        fwrite(&n, 1, 1, seen);                                                                     //-=--=-=-=-=-=-=-=-=-=-=-=-=-=-
        node_buffer = node_buffer->next_node;                                                       //
    }                                                                                             //  

    get_compression(seen_list);

    free_list(seen_list);
    fclose(text);
    fclose(seen);
}

int main(int argc, char* argv[])
{
    FILE* text=fopen(argv[1], "r");
    generate_seen(text);
    printf("done\n");
}














/*
    NODE *node_buffer = seen_list;
    while (node_buffer != NULL)
    {
        fwrite((char *)node_buffer->data, strlen((char *)node_buffer->data), 1, seen);
        fwrite(&n, 1, 1, seen);
        node_buffer = node_buffer->next_node;
    }
    free_list(seen_list);
    fclose(text);
    fclose(seen);
*/



/*
    word_node* word_node1=malloc(sizeof(word_node));
    word_node1->count=0;
    strcpy(word_node1->word, "Hello");

    word_node* word_node2=malloc(sizeof(word_node));
    word_node2->count=0;
    strcpy(word_node2->word, "every");

    word_node* word_node3=malloc(sizeof(word_node));
    word_node3->count=0;
    strcpy(word_node3->word, "nyan");

    NODE* new_list=create_list((void*)word_node1);
    insert_at_end(new_list, (void*)word_node2);
    insert_at_end(new_list, (void*)word_node3);

    custom_print(new_list, custom_print_func);
*/