#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define STACKSIZE 10

typedef struct {
    int* collection; // memory that will hold the stack's elements
    int capacity;    // the maximum capacity of the memory
    int size;        // the number of elements of the memory is currently
} Stack;

int menu();
Stack* createStack(int capacity); // creates a stack
void destroy_stack(Stack* stack); // release stack from memory
bool is_full(Stack* stack);       // checks whether the stack is full or not
bool is_empty(Stack* stack);      // checks whether the stack is empty or not
bool pop(Stack* stack, int* item);// we'll get the element out of the stack
bool push(Stack* stack, int item);// we add elements to the stack
bool peek(Stack* stack, int* item);// shows the last element in the stack (the top one)

int main() {
    Stack* stack = createStack(STACKSIZE);

    if (stack == NULL) { // if stack is empty, it shows error
        printf("Error creating stack...\n");
        return 1;
    }

    int option;
    do { // to choose process
        option = menu();
        int item;
        switch (option) {
            case 1:
                if (pop(stack, &item))
                    printf("Removed element: %d\n", item);// removes the last element
                else
                    printf("Stack is empty.\n");// firstly, it checks pop function. if pop function return false, it means stack is empty
                break;
            case 2:
                printf("!!Don't forget, stack size is maximum 10 elements!!\n");
                printf("Which element will you add?\n");
                scanf("%d", &item);
                if (push(stack, item))
                    printf("Added element: %d\n", item);
                else
                    printf("Stack is full.\n");// first of all, checks push function. if push function return false, it means stack is full
                break;
            case 3:
                if (peek(stack, &item))
                    printf("Last element is %d\n", item);// shows the last element
                else
                    printf("Stack is empty.\n");// foremost, checks peek function. if peek function return false, it means stack is empty
                break;
            case 4:
                printf("Stack size %d\n", stack->size);// gives the number of elements in the stack
                break;
            case 5:
                for(int i = 0 ; i < stack->size; i++){// shows us elements in the stack
                    printf(" %d |", stack->collection[i]);
                }
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid option. Try again.\n");
        }
    } while (option != 6);

    destroy_stack(stack);// in the last process, program releases stack from memory
    return 0;
}

int menu() {// to choose option
    int option;
    printf("\n1 -> Pop");
    printf("\n2 -> Push");
    printf("\n3 -> Peek");
    printf("\n4 -> Show size of stack");
    printf("\n5 -> Show element of the stack");
    printf("\n6 -> Exit");
    printf("\nEnter your choice:\n");
    scanf("%d", &option);
    return option;
}

Stack* createStack(int capacity) {// to creative a stack
    if (capacity <= 0) return NULL;

    Stack* stack = malloc(sizeof(Stack)); // allocates space in memory
    if (stack == NULL) return NULL; // if stack is empty, it shows NULL

    stack->collection = malloc(sizeof(int) * capacity); // stack->collection = stack.collection
    if (stack->collection == NULL) {
        free(stack); // if we succeed in memory allocation, it clears the memory
        return NULL;
    }
    stack->capacity = capacity;// capacity consists after stack creative
    stack->size = 0;// that's why capacity is 0
    return stack;
}

void destroy_stack(Stack* stack) { // release stack from memory
    free(stack->collection); // releases memory
    free(stack); // releases stack
}

bool is_full(Stack* stack) { // checks whether the stack is full or not
    return stack->size == stack->capacity;
}

bool is_empty(Stack* stack) { // checks whether the stack is empty or not
    return stack->size == 0;
}

bool pop(Stack* stack, int* item) { // we'll get the element out of the stack
    if (is_empty(stack)) return false; // if stack is empty, returns false

    stack->size--; // the size is reduced by one
    *item = stack->collection[stack->size]; // the extracted element is assigned to the item
    return true; // if it is success, returns true
}

bool push(Stack* stack, int item) { // we add elements to the stack
    if (is_full(stack)) return false; // if stack is full, returns false

    stack->collection[stack->size] = item; // the element is added to the stack
    stack->size++; // the size is increased by one
    return true; // if it is success, returns true
}

bool peek(Stack* stack, int* item) { // shows the last element in the stack (the top one)
    if (is_empty(stack)) return false; // if stack is empty, returns false

    *item = stack->collection[stack->size - 1]; // the last element is assigned to the item
    return true; // if it is success, returns true
}
