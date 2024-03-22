#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a node into BST
struct Node* insertNode(struct Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }

    if (data < root->data) {
        root->left = insertNode(root->left, data);
    } else if (data > root->data) {
        root->right = insertNode(root->right, data);
    }

    return root;
}

// Function to delete a node from BST
struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL) {
        return root;
    }

    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    } else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        struct Node* temp = root->right;
        while (temp->left != NULL) {
            temp = temp->left;
        }

        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}

// Function to calculate the height of BST
int height(struct Node* root) {
    if (root == NULL) {
        return 0;
    } else {
        int leftHeight = height(root->left);
        int rightHeight = height(root->right);

        if (leftHeight > rightHeight) {
            return leftHeight + 1;
        } else {
            return rightHeight + 1;
        }
    }
}

// Function to print level and height of a node
void printLevelAndHeight(struct Node* root, int key, int level) {
    if (root == NULL) {
        printf("Node not found.\n");
        return;
    }

    if (root->data == key) {
        printf("Node found at level %d with height %d.\n", level, height(root));
        return;
    }

    if (key < root->data) {
        printLevelAndHeight(root->left, key, level + 1);
    } else {
        printLevelAndHeight(root->right, key, level + 1);
    }
}

// Function to print inorder traversal of BST
void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

int main() {
    int arr[] = {30, 20, 40, 10, 25, 35};
    int n = sizeof(arr) / sizeof(arr[0]);

    struct Node* root = NULL;
    for (int i = 0; i < n; i++) {
        root = insertNode(root, arr[i]);
    }

    printf("Inorder traversal of BST: ");
    inorderTraversal(root);
    printf("\n");

    int nodeToDelete = 20;
    root = deleteNode(root, nodeToDelete);
    printf("Inorder traversal after deleting node %d: ", nodeToDelete);
    inorderTraversal(root);
    printf("\n");

    printf("Height of BST: %d\n", height(root));

    int nodeToFind = 40;
    printLevelAndHeight(root, nodeToFind, 1);

    return 0;
}
