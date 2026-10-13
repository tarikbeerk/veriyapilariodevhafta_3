#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct PrintJob {
    char fileName[50];
    struct PrintJob* next;
} PrintJob;

typedef struct Queue {
    PrintJob* front;
    PrintJob* rear;
} Queue;

void enqueuePrintJob(Queue* q, char* fileName);
void processNextJob(Queue* q);
void showQueue(Queue q);

void enqueuePrintJob(Queue* q, char* fileName) {
    PrintJob* newJob = (PrintJob*)malloc(sizeof(PrintJob));
    strcpy(newJob->fileName, fileName);
    newJob->next = NULL;

    // Kuyruk boşsa
    if (q->rear == NULL) {
        q->front = q->rear = newJob;
    } else {
        q->rear->next = newJob;
        q->rear = newJob;
    }
    printf("-> '%s' yazdirma kuyruguna eklendi.\n", fileName);
}

void processNextJob(Queue* q) {
    if (q->front == NULL) {
        printf("Uyari: Yazdirma kuyrugu bos! Yazdirilacak dosya yok.\n");
        return;
    }

    PrintJob* temp = q->front;
    printf("-> YAZDIRILIYOR: '%s' basariyla yazdirildi ve kuyruktan cikarildi.\n", temp->fileName);

    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
}

void showQueue(Queue q) {
    if (q.front == NULL) {
        printf("Yazdirma kuyrugu su an bos.\n");
        return;
    }

    printf("\n--- Bekleyen Yazdirma Kuyrugu ---\n");
    PrintJob* temp = q.front;
    int sira = 1;
    while (temp != NULL) {
        printf("%d. %s\n", sira++, temp->fileName);
        temp = temp->next;
    }
    printf("---------------------------------\n");
}

int main() {
    Queue printerQueue = {NULL, NULL};
    int choice;
    char fileName[50];

    while (1) {
        printf("\n=== YAZICI KUYRUK YONETIMI ===\n");
        printf("1) Yeni dosya ekle\n");
        printf("2) Yazdir\n");
        printf("3) Kuyrugu goster\n");
        printf("0) Cikis\n");
        printf("Seciminiz: ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); 
            continue;
        }
        getchar(); 

        switch (choice) {
            case 1:
                printf("Dosya adini girin (Orn: Odev3.pdf): ");
                fgets(fileName, sizeof(fileName), stdin);
                fileName[strcspn(fileName, "\n")] = 0; 

                enqueuePrintJob(&printerQueue, fileName);
                break;

            case 2:
                processNextJob(&printerQueue);
                break;

            case 3:
                showQueue(printerQueue);
                break;

            case 0:
                printf("Yazici sistemi kapatiliyor...\n");
                while (printerQueue.front != NULL) {
                    PrintJob* temp = printerQueue.front;
                    printerQueue.front = printerQueue.front->next;
                    free(temp);
                }
                printerQueue.rear = NULL;
                return 0;

            default:
                printf("Gecersiz secim! Lutfen 0-3 arasi bir deger girin.\n");
        }
    }

    return 0;
}