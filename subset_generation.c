/* Generate all subsets of in range(n): */
/*     Example: */
/*     n = 2 */
/*     subsets = [[1, 2]], [1], [2], []] */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ---------------------------------------------------------------------------------------------------------------
typedef struct Subset {
    int maxSize; // maxSize (usually n)
    int currentSize;
    int array[]; // FAM
} SUBSET;

SUBSET *makeSubset(int maxSize) {
    SUBSET *newSubset = malloc(sizeof(SUBSET) + maxSize * sizeof(int));
    newSubset -> maxSize = maxSize;
    newSubset -> currentSize = 0;

    // init arrray
    for (int i = 0; i < maxSize; i++) {
        newSubset -> array[i] = -1;
    }

    return newSubset;
}

void freeSubset(SUBSET *s) {
    free(s);
}

void printSubset(SUBSET *subset, char endChar[1]) {
    printf("[");
    for (int i = 0; i < subset -> currentSize; i++) {
        printf("%d", subset -> array[i]);

        if (i < subset -> currentSize - 1) { printf(", "); }
    }
    printf("]");
    printf("%s", endChar);
}

bool subsetFull(SUBSET *s) { return (s -> currentSize == s -> maxSize); } // is subset full?
bool subsetEmpty(SUBSET *s) { return (s -> currentSize == 0); } // is subset empty?

bool subsetAppend(SUBSET *s, int value) {
    if (subsetFull(s)) { return false; }

    s -> array[s -> currentSize] = value;
    s -> currentSize++;

    return true;
}

int subsetPop(SUBSET *s) {
    if (subsetEmpty(s)) { return -1; }

    return s -> array[--(s -> currentSize)];
}

SUBSET *copySubset(SUBSET *s) {
    SUBSET *newS = makeSubset(s -> maxSize);
    newS -> currentSize = s -> currentSize;

    for (int i = 0; i < s -> currentSize; i++) {
        newS -> array[i] = s -> array[i];
    }

    return newS;
}

// ---------------------------------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------------------------------
typedef struct SubsetListNode {
    SUBSET *subset;
    struct SubsetListNode *next;

} SUBSET_LIST; // head node of linked list of subsets

SUBSET_LIST *makeSubsetList() {
    SUBSET_LIST *newList = malloc(sizeof(SUBSET_LIST));

    // init pointers
    newList -> subset = NULL; 
    newList -> next = NULL;

    return newList;
}

SUBSET_LIST *makeNode() { return makeSubsetList(); }

void freeSubsetList(SUBSET_LIST *head) {
    SUBSET_LIST *current = head;
    SUBSET_LIST *temp = NULL;

    while (current != NULL) {
        temp = current -> next;

        if (current -> subset != NULL) { freeSubset(current -> subset); }
        free(current);

        current = temp;
    }
}

void addSubset(SUBSET_LIST *head, SUBSET *subset) {
    SUBSET_LIST *current = head;
    
    // if head does not have a subset
    if (current -> subset == NULL) { current -> subset = subset; return; }

    while (current -> next != NULL) { current = current -> next; }

    current -> next = makeNode();
    current -> next -> subset = subset;
}

void printSubsetList(SUBSET_LIST *head) {
    SUBSET_LIST *current = head;

    printf("[");
    while (current != NULL) {
        if (current -> subset != NULL) {
            printSubset(current -> subset, "");
        } else {  }

        if (current -> next != NULL) { printf(", "); }

        current = current -> next;
    }

    printf("]\n");

};
// ---------------------------------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------------------------------
// generate all subsets in range [1, n]
void generateSubsets(SUBSET_LIST *list, SUBSET *subset, int n, int k) {

    if (k == (n + 1)) { 
        addSubset(list, copySubset(subset));
    } else {
        subsetAppend(subset, k);
        generateSubsets(list, subset, n, k + 1);
        subsetPop(subset);
        generateSubsets(list, subset, n, k + 1);
    }
}
// ---------------------------------------------------------------------------------------------------------------

int main() {
    int n = 3;

    SUBSET_LIST *list = makeSubsetList();
    SUBSET *subset = makeSubset(n); // the subset that is edited and copied on each recursive call

    // generate all subsets in range(n)
    generateSubsets(list, subset, n, 1);

    printSubsetList(list);

    // deallocate
    freeSubsetList(list);
    freeSubset(subset);

    return 0;
}

