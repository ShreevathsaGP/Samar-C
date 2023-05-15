#include <stdio.h>
#include <stdlib.h>


/*----------------------------------------------------------------------------*/
typedef struct all_subsets_node
{
    int* subset;
    int size;
    struct all_subsets_node* link;
}ALL_SUBSETS;

ALL_SUBSETS* all_subsets; // creating an instance of struct all_subsets_node

ALL_SUBSETS* createNodeArr(int* data)
{
    ALL_SUBSETS* newNode = (ALL_SUBSETS*)malloc(sizeof(ALL_SUBSETS));
    newNode -> subset = data;
    newNode -> link = NULL;
    return newNode;
}

ALL_SUBSETS* insertFrontArr(ALL_SUBSETS* head, int* data)
{
    ALL_SUBSETS* newNode = createNodeArr(data);
    newNode -> link = head;
    head = newNode;
    return head;
}

void display(ALL_SUBSETS* head)
{
    while (head != NULL)
    {
        int* arr = head -> subset;
        int size = head -> size;

        for(int loop = 0; loop < size; loop++)
        {
            printf("%d ", arr[loop]);
        }

        printf("\n\n");

        head = head->link;
    }
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
typedef struct subset
{
    int data;
    struct subset* link;
}SUBSET;

SUBSET* subset; // creating an instance of struct subset

SUBSET* createNodeInt(int data)
{
    SUBSET* newNode = (SUBSET*)malloc(sizeof(SUBSET));
    newNode -> data = data;
    newNode -> link = NULL;
    return newNode;
}

SUBSET* insertFrontInt(SUBSET* head, int data)
{
    SUBSET* newNode = createNodeInt(data);
    newNode -> link = head;
    head = newNode;
    return head;
}

SUBSET* deleteFrontInt(SUBSET* head)
{
    SUBSET* next = head -> link;
    free(head);
    head = NULL;
    head = next;
    return head;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
// initialising a global variable to store the size of the array we calculate here
int size_of_subset = 0;
// we need a function to convert a linked list to an array
int* list_to_array(SUBSET* head)
{
    // Parsing through the list to find out the required size of our array
    int size = 0;
    SUBSET* head_copy = head;
    while(head_copy != NULL)
    {
        head_copy = head_copy -> link;
        size++;
    }

    size_of_subset = size;

    // converting list to array
    int* arr = (int*)malloc(size*sizeof(int));
    int count = 0;
    while (head != NULL)
    {
        arr[count] = head -> data;
        head = head->link;
        count++;
    }

    return arr;
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
void search(int k)
{
    if (k == 4)
    {
        // Converting current subset from a linked list to an array
        int* cur_sub = list_to_array(subset);
        // Adding cur_sub to final output ALL_SUBSETS
        all_subsets = insertFrontArr(all_subsets, cur_sub);
        all_subsets -> size = size_of_subset;
    }
    else
    {
        // add k to the subset
        subset = insertFrontInt(subset, k);
        search(k + 1);
        // remove k from the subset
        subset = deleteFrontInt(subset);
        search(k + 1);
    }
}
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
void main()
{
    search(1);
    display(all_subsets);
}
