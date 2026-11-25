#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Product {
    int id, qty;
    char name[30];
    float price;
    struct Product *next;
};

struct BST {
    int id;
    struct Product *p;
    struct BST *left, *right;
};

struct Product *head = NULL;
struct BST *root = NULL;

// Clear invalid input
void clearInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Search ID in BST
struct BST* findID(int id) {
    struct BST *t = root;

    while (t != NULL) {
        if (id == t->id)
            return t;
        else if (id < t->id)
            t = t->left;
        else
            t = t->right;
    }
    return NULL;
}

// Insert in BST
struct BST* insert(struct BST *r, struct BST *node) {
    if (r == NULL)
        return node;

    if (node->id < r->id)
        r->left = insert(r->left, node);
    else if (node->id > r->id)
        r->right = insert(r->right, node);

    return r;
}

// Add Product
void add() {
    struct Product *p = (struct Product*)malloc(sizeof(struct Product));
    struct BST *node = (struct BST*)malloc(sizeof(struct BST));

    if (p == NULL || node == NULL) {
        printf("Memory Allocation Failed!\n");
        free(p);
        free(node);
        return;
    }

    printf("Enter ID: ");
    if (scanf("%d", &p->id) != 1) {
        printf("Invalid ID!\n");
        clearInput();
        free(p);
        free(node);
        return;
    }

    if (findID(p->id) != NULL) {
        printf("ID Already Exists!\n");
        free(p);
        free(node);
        return;
    }

    printf("Enter Name: ");
    if (scanf(" %29[^\n]", p->name) != 1) {
        printf("Invalid Name!\n");
        clearInput();
        free(p);
        free(node);
        return;
    }

    printf("Enter Quantity: ");
    if (scanf("%d", &p->qty) != 1 || p->qty < 0) {
        printf("Invalid Quantity!\n");
        clearInput();
        free(p);
        free(node);
        return;
    }

    printf("Enter Price: ");
    if (scanf("%f", &p->price) != 1 ||
        p->price < 0) {
        printf("Invalid Price!\n");
        clearInput();
        free(p);
        free(node);
        return;
    }

    p->next = head;
    head = p;

    node->id = p->id;
    node->p = p;
    node->left = NULL;
    node->right = NULL;

    root = insert(root, node);

    printf("Product Added Successfully!\n");
}

// Display Products
void display() {
    struct Product *t = head;

    if (t == NULL) {
        printf("Warehouse Empty!\n");
        return;
    }

    while (t != NULL) {
        printf("\nID: %d | Name: %s | Qty: %d | Price: %.2f\n",
               t->id, t->name, t->qty, t->price);
        t = t->next;
    }
}

// Search by ID
void searchID() {
    int id;

    printf("Enter ID: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid ID!\n");
        clearInput();
        return;
    }

    struct BST *t = findID(id);

    if (t != NULL) {
        printf("Found: %s | Qty: %d | Price: %.2f\n",
               t->p->name, t->p->qty, t->p->price);
    } else {
        printf("Product Not Found!\n");
    }
}

// Search by Name
void searchName() {
    char name[30];

    printf("Enter Name: ");
    if (scanf(" %29[^\n]", name) != 1) {
        printf("Invalid Name!\n");
        clearInput();
        return;
    }

    struct Product *t = head;

    while (t != NULL) {
        if (strcmp(name, t->name) == 0) {
            printf("Found! ID: %d | Qty: %d | Price: %.2f\n",
                   t->id, t->qty, t->price);
            return;
        }
        t = t->next;
    }

    printf("Product Not Found!\n");
}

// Free BST memory
void freeBST(struct BST *r) {
    if (r == NULL)
        return;

    freeBST(r->left);
    freeBST(r->right);
    free(r);
}

// Free Linked List memory
void freeList() {
    struct Product *t;

    while (head != NULL) {
        t = head;
        head = head->next;
        free(t);
    }
}

// Main Menu
int main() {
    int ch;

    do {
        printf("\n--- Warehouse Stock Management ---\n");
        printf("1. Add Product\n");
        printf("2. Display Products\n");
        printf("3. Search by ID\n");
        printf("4. Search by Name\n");
        printf("5. Exit\n");
        printf("Enter Choice: ");

        if (scanf("%d", &ch) != 1) {
            printf("Invalid Choice!\n");
            clearInput();
            continue;
        }

        switch (ch) {
            case 1: add(); break;
            case 2: display(); break;
            case 3: searchID(); break;
            case 4: searchName(); break;
            case 5:
                freeBST(root);
                freeList();
                printf("Thank You!\n");
                break;
            default:
                printf("Invalid Choice!\n");
        }

    } while (ch != 5);

    return 0;
}
