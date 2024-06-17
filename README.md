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
