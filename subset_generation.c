#include <stdio.h>
#include <stdlib.h>


/*----------------------------------------------------------------------------*/
typedef struct all_subsets_node
{
    int* subset;
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
        int size = sizeof(arr)/sizeof(arr[0]);

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
// we need a function which takes input array and outputs a copy of the array at another location
int* copy(int* ptr)
{
    int size = sizeof(ptr)/sizeof(int);
    int* doppleganger = (int*)malloc(size);

    for(int loop = 0; loop < size; loop++)
    {
        doppleganger[loop] = ptr[loop];
    }

    return doppleganger;
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