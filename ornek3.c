#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int musteriNumarasi;
    struct Node* next;
} Node;

void enqueue(Node** front, Node** rear, int musteriNo) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->musteriNumarasi = musteriNo;
    newNode->next = NULL;

    if (*rear == NULL) {
        *front = *rear = newNode;
    } else {
        (*rear)->next = newNode;
        *rear = newNode;
    }
    printf("Musteri #%d geldi.\n", musteriNo);
}

void dequeue(Node** front, Node** rear) {
    if (*front == NULL) {
        printf("Kuyrukta bekleyen musteri yok!\n");
        return;
    }

    Node* temp = *front;
    printf("Musteri #%d islemi tamamladi.\n", temp->musteriNumarasi);

    *front = (*front)->next;

    if (*front == NULL) {
        *rear = NULL;
        printf("Kuyrukta baska musteri kalmadi.\n");
    } else {
        printf("Yeni siradaki musteri: #%d\n", (*front)->musteriNumarasi);
    }

    free(temp);
}

void display(Node* front) {
    if (front == NULL) {
        printf("Sira bos, bekleyen musteri yok.\n");
        return;
    }

    printf("Siradaki musteri: #%d | Tum Bekleyenler: ", front->musteriNumarasi);
    Node* temp = front;
    while (temp != NULL) {
        printf("#%d ", temp->musteriNumarasi);
        if (temp->next != NULL) printf("<- ");
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    Node* front = NULL;
    Node* rear = NULL;
    int sayac = 1;
    int secim;

    printf("--- Ornek Cikti Simulasyonu ---\n");
    enqueue(&front, &rear, sayac++);
    enqueue(&front, &rear, sayac++);
    printf("Siradaki musteri: #%d\n", front->musteriNumarasi);
    dequeue(&front, &rear);
    printf("-------------------------------\n");

    while (1) {
        printf("\n=== MUSTERI SIRASI MENUSU ===\n");
        printf("1. Musteri Geldi (Enqueue)\n");
        printf("2. Islem Tamamlandi (Dequeue)\n");
        printf("3. Bekleyen Sirayi Goster (Display)\n");
        printf("0. Cikis\n");
        printf("Seciminiz: ");

        if (scanf("%d", &secim) != 1) {
            while (getchar() != '\n');
            continue;
        }

        switch (secim) {
            case 1:
                enqueue(&front, &rear, sayac++);
                break;
            case 2:
                dequeue(&front, &rear);
                break;
            case 3:
                display(front);
                break;
            case 0:
                printf("Sistem kapatiliyor...\n");
                while (front != NULL) {
                    Node* temp = front;
                    front = front->next;
                    free(temp);
                }
                return 0;
            default:
                printf("Gecersiz secim!\n");
        }
    }
    return 0;
}