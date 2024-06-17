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
