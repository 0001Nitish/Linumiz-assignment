Implementing pushd and popd commands in C requires managing a stack of directories. We'll use a linked list to represent the stack.
1. Node Structure
The Node structure represents each directory in the stack.
Fields:
char dir[PATH_MAX]: Stores the directory path.
struct Node* next: Pointer to the next node in the stack.

2. createNode Function
Creates a new node with the given directory path.
Parameters:
const char* dir: Directory path to store in the node.
Returns:
Node*: Pointer to the newly created node.

3. pushd Function
Pushes the current directory onto the stack and changes to the specified directory.
Parameters:
Node** top: Pointer to the top of the stack.
const char* newDir: Directory to change to.
Steps:
-Get the current directory using getcwd.
-Create a new node with the current directory.
-Push the new node onto the stack.
-Change to the specified directory using chdir.

4. popd Function
Pops the top directory from the stack and changes to that directory.
Parameters:
Node** top: Pointer to the top of the stack.
Steps:
-Check if the stack is empty.
-Pop the top node from the stack.
-Change to the directory stored in the popped node using chdir.
-Free the memory allocated for the popped node.

6. Main Function
Demonstrates the usage of pushd and popd functions.
Steps:
Initialize an empty stack.
Use pushd to change directories and push the current directory onto the stack.
Use popd to change back to the previous directory by popping the top directory from the stack.
Attempt to pop from an empty stack to handle the edge case.

This implementation uses a linked list to manage a stack of directories, allowing for the pushd and popd commands to change and navigate through directories. The pushd function saves the current directory and changes to a new one, while popd restores the last saved directory. This example demonstrates the basic functionality and can be extended with additional features and error handling as needed.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

// Define the node structure
typedef struct Node {
    char dir[PATH_MAX];
    struct Node* next;
} Node;

// Function to create a new node
Node* createNode(const char* dir) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    strncpy(newNode->dir, dir, PATH_MAX);
    newNode->next = NULL;
    return newNode;
}
void pushd(Node** top, const char* newDir) {
    char currentDir[PATH_MAX];
    if (!getcwd(currentDir, PATH_MAX)) {
        perror("getcwd failed");
        return;
    }
    Node* newNode = createNode(currentDir);
    newNode->next = *top;
    *top = newNode;
    if (chdir(newDir) != 0) {
        perror("chdir failed");
    } else {
        printf("Changed directory to: %s\n", newDir);
    }
}
void popd(Node** top) {
    if (*top == NULL) {
        printf("Stack is empty, cannot popd\n");
        return;
    }
    Node* temp = *top;
    *top = (*top)->next;
    if (chdir(temp->dir) != 0) {
        perror("chdir failed");
    } else {
        printf("Changed directory to: %s\n", temp->dir);
    }
    free(temp);
}
int main() {
    Node* stack = NULL;
    
    // Push current directory and change to /tmp
    pushd(&stack, "/tmp");
    
    // Push current directory and change to /usr
    pushd(&stack, "/usr");
    
    // Pop directory and change back to previous
    popd(&stack);
    
    // Pop directory and change back to original
    popd(&stack);
    
    // Attempt to pop from empty stack
    popd(&stack);
    
    return 0;
}
