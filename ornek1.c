#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int numara;
    char isim[50];
    struct Node* next;
    struct Node* prev;
} Node;

Node* createNode(int numara, const char* isim) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->numara = numara;
    strcpy(newNode->isim, isim);
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void insertOrdered(Node** head, int numara, const char* isim) {
    Node* newNode = createNode(numara, isim);

    if (*head == NULL) {
        *head = newNode;
        printf("-> %d numarali %s eklendi.\n", numara, isim);
        return;
    }

    if (numara < (*head)->numara) {
        newNode->next = *head;
        (*head)->prev = newNode;
        *head = newNode;
        printf("-> %d numarali %s basa eklendi.\n", numara, isim);
        return;
    }

    Node* temp = *head;
    while (temp->next != NULL && temp->next->numara < numara) {
        temp = temp->next;
    }

    if (temp->numara == numara || (temp->next != NULL && temp->next->numara == numara)) {
        printf("Uyari: %d numarali ogrenci zaten mevcut!\n", numara);
        free(newNode);
        return;
    }

    newNode->next = temp->next;
    newNode->prev = temp;

    if (temp->next != NULL) {
        temp->next->prev = newNode; 
    }
    temp->next = newNode;

    printf("-> %d numarali %s sirali eklendi.\n", numara, isim);
}

void displayForward(Node* head) {
    if (head == NULL) {
        printf("\nListe bos!\n");
        return;
    }
    printf("\n--- Bastan Sona Ogrenci Listesi ---\n");
    Node* temp = head;
    while (temp != NULL) {
        printf("No: %d | Isim: %s\n", temp->numara, temp->isim);
        temp = temp->next;
    }
}

void displayBackward(Node* head) {
    if (head == NULL) {
        printf("\nListe bos!\n");
        return;
    }
    
    Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    printf("\n--- Sondan Basa Ogrenci Listesi ---\n");
    while (temp != NULL) {
        printf("No: %d | Isim: %s\n", temp->numara, temp->isim);
        temp = temp->prev;
    }
}

int main() {
    Node* head = NULL;

    insertOrdered(&head, 105, "Ahmet");
    insertOrdered(&head, 101, "Zeynep");
    insertOrdered(&head, 109, "Mehmet");
    insertOrdered(&head, 103, "Elif");

    displayForward(head);
    displayBackward(head);

    return 0;
}