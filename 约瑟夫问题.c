#include<stdio.h>  
#include<stdlib.h>  
typedef struct Node{  
    int data;  
    struct Node* next;  
}Node;  
Node* createNode(int data){  
    Node* newNode = (Node*)malloc(sizeof(Node));  
    if(newNode==NULL){  
        exit(EXIT_FAILURE);  
    }  
    newNode->data = data;  
    newNode->next = NULL;  
    return newNode;  
}  
void insertAtTail(Node** head,int data){  
    Node* newNode = createNode(data);  
    if(*head == NULL){   
        newNode->next = newNode;  
        *head = newNode;  
        return;  
    }  
    Node* tail = *head;  
    while(tail->next != *head){  
        tail = tail->next;  
    }  
    tail->next = newNode;  
    newNode->next = *head;  
}  
void deleteNodeByPtr(Node** head, Node* delNode) {  
    if (*head == NULL || delNode == NULL) return;  
    Node* tail = *head;  
    while(tail->next != *head){  
        tail = tail->next;  
    }  
    if(*head == delNode && (*head)->next == *head){  
        *head = NULL;  
        free(delNode);  
        return;  
    }  
    if (*head == delNode) {  
        *head = delNode->next;  
        tail->next = *head;  
        free(delNode);  
        return;  
    }  
    Node* prev = *head;  
    while (prev->next != delNode) {  
        prev = prev->next;  
        if(prev == *head) return;   
    }  
    prev->next = delNode->next;  
    free(delNode);  
}  
void freeList(Node** head) {  
    if (*head == NULL) return;  
    Node* current = *head;  
    Node* next;  
    do {  
        next = current->next;  
        free(current);  
        current = next;  
    } while (current != *head);  
    *head = NULL;   
}  
int main(){  
    int n, k, m;  
    Node* head = NULL;  
    int input_flag = scanf("%d,%d,%d", &n, &k, &m);  
    if (input_flag != 3) {   
        return 1;  
    }  
    if (n < 1 || k < 1 || m < 1) {  
        printf("n,m,k must bigger than 0.\n");  
        return 1;  
    }  
    if (k > n) {  
        printf("k should not bigger than n.\n");  
        return 1;  
    }  
    for (int i = 0; i < n; i++) {  
        insertAtTail(&head, i + 1);  
    }  
    Node* current = head;  
    int count = 0;   
    for (int i = 1; i < k; i++) {  
        current = current->next;  
    }  
    while (head != NULL) {  
        for (int i = 1; i < m; i++) {  
            current = current->next;  
        }  
        Node* delNode = current;         
        Node* nextNode = delNode->next;  
        printf("%d", delNode->data);  
        count++;  
        if (count % 10 == 0) {          
            printf("\n        ");        
        } else if (head->next != head) {   
            printf(" ");  
        }  
        deleteNodeByPtr(&head, delNode);  
        current = nextNode;  
    }  
    printf("\n");  
    freeList(&head);  
    return 0;  
}