#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct _node {
    float data;
    struct _node* parent;
    struct _node* left;
    struct _node* right;
    char* name;
} N_Node;

typedef struct _tree {
    N_Node root;
} Tree;

N_Node * newNode(float data) {
    N_Node *node = (N_Node *)malloc(sizeof(N_Node));
    node->data = data;
    node->left = NULL;  // Initialize left child as NULL
    node->right = NULL; // Initialize right child as NULL
    node->name = (char *)malloc(20 * sizeof(char));
    return node;
}

N_Node* addChild(N_Node *parent, float data) {
    N_Node *child = newNode(data);
    child->parent = parent;

    if (parent->left == NULL) {
        parent->left = child;
    } else if (parent->right == NULL) {
        parent->right = child;
    } else {
        printf("Error: Node has two children already.\n");
        free(child); // Important to avoid memory leaks since the node isn't added
        return NULL;
    }
    return child;
}

void cleanup(N_Node *node);

void removeChild(N_Node *parent, N_Node *child) {
    if (parent->left == child) {
        cleanup(parent->left);
        parent->left = NULL;
    } else if (parent->right == child) {
        cleanup(parent->right);
        parent->right = NULL;
    } else {
        printf("Error: Specified node is not a child of this parent.\n");
    }
}

// 1 depth = 1 space
void printTreeHelper(N_Node *node, int space) {
    int i;
    if (node == NULL)
        return;

    space += 10; // Increase distance between levels

    printTreeHelper(node->right, space); // Process right child first

    printf("\n");
    for (i = 10; i < space; i++)
        printf(" ");
    printf("%f\n", node->data);

    printTreeHelper(node->left, space); // Then process left child
}

void printTree(N_Node *node) {
    printTreeHelper(node, 0);
}

void cleanup(N_Node *node) {
    if (node == NULL) {
        return;
    }

    cleanup(node->left);
    cleanup(node->right);
    free(node->name);
    free(node);
}

int getHeight(N_Node *node) {
    if (node == NULL) return 0;
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

bool isAVL(N_Node *node) {
    if (node == NULL) return true;
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);

    if (abs(leftHeight - rightHeight) > 1) return false;

    return isAVL(node->left) && isAVL(node->right);
}

N_Node *findNodeByName(N_Node *node, char *name) {
    if (node == NULL) {
        return NULL;
    }

    if (strcmp(node->name, name) == 0) {
        return node;
    }

    N_Node *foundNode = findNodeByName(node->left, name);
    if (foundNode == NULL) {
        foundNode = findNodeByName(node->right, name);
    }
    return foundNode;
}


int main() {
    N_Node *root = NULL;
    int nodeCount = 0;
    char command[10];
    float value;
    char nodeName1[20], nodeName2[20];
    N_Node *node1, *node2;
    bool exitFlag = false;

    printf("Enter commands:\n");

    while (!exitFlag) {
        scanf("%s", command);

        if (strcmp(command, "add") == 0) {
            scanf("%s %f", nodeName1, &value);
            if (root == NULL && strcmp(nodeName1, "root") == 0) {
                root = (N_Node *)malloc(sizeof(N_Node));
                root->data = value;
                root->left = NULL;  // Correctly initialize left child
                root->right = NULL; // Correctly initialize right child
                root->name = (char *)malloc(20 * sizeof(char));
                strcpy(root->name, "root");
                printf("Created root\n");
            } else {
                node1 = findNodeByName(root, nodeName1);
                if (node1 != NULL) {
                    node2 = addChild(node1, value);
                    if (node2 != NULL) {  // Check if node2 is not NULL
                        nodeCount++;
                        sprintf(node2->name, "node_%d", nodeCount);
                        printf("Created %s\n", node2->name);
                    } else {
                        printf("Failed to add child node\n");
                    }
                } else {
                    printf("Node not found\n");
                }
            }
        } else if (strcmp(command, "remove") == 0) {
            scanf("%s %s", nodeName1, nodeName2);
            node1 = findNodeByName(root, nodeName1);
            node2 = findNodeByName(root, nodeName2);
            if (node1 != NULL && node2 != NULL) {
                if (node1 == root && node2 == root) {
                    cleanup(root);
                    root = NULL;
                    printf("Root purge\n");
                } else {
                    removeChild(node1, node2);
                }
            } else {
                printf("Node(s) not found\n");
            }
        } else if (strcmp(command, "print") == 0) {
            scanf("%s", nodeName1);
            node1 = findNodeByName(root, nodeName1);
            if (node1 != NULL) {
                printTree(node1);
            } else {
                printf("Node not found\n");
            }
        } else if (strcmp(command, "avl") == 0) {
            scanf("%s", nodeName1);
            node1 = findNodeByName(root, nodeName1);
            if (node1 != NULL) {
                bool isAvlTree = isAVL(node1);
                printf("%s\n", isAvlTree ? "AVL" : "Not AVL");
            } else {
                printf("Node not found\n");
            }
        } else if (strcmp(command, "exit") == 0) {
            exitFlag = true;
        } else {
            printf("Invalid command\n");
        }
    }

    cleanup(root);

    return 0;
}
