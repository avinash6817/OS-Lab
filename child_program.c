#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

    int *array = (int *)malloc(sizeof(int) * argc);
    
    for (int i = 1; i < argc; i++) {
        array[i - 1] = atoi(argv[i]);
    }

    int key;
    printf("Enter the item to search: ");
    scanf("%d", &key);

    int index = binarySearch(array, argc - 1, key);
    if(index != -1) {
        printf("The item is found at index %d\n", index);
    } 
    else {
        printf("The item is not found in the array\n");
    }

    free(array);

    return 0;
}
