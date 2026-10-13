#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Song {
    char name[50];
    struct Song* next;
    struct Song* prev;
} Song;

void addSongToEnd(Song** head, char* name);
void removeSong(Song** head, char* name);
void playNext(Song** current);
void playPrevious(Song** current);
void displayPlaylist(Song* head);

void addSongToEnd(Song** head, char* name) {
    Song* newSong = (Song*)malloc(sizeof(Song));
    strcpy(newSong->name, name);
    newSong->next = NULL;
    newSong->prev = NULL;

    if (*head == NULL) {
        *head = newSong;
        printf("'%s' eklendi (Ilk sarki).\n", name);
        return;
    }

    Song* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = newSong;
    newSong->prev = temp;
    printf("'%s' calma listesinin sonuna eklendi.\n", name);
}

void removeSong(Song** head, char* name) {
    if (*head == NULL) {
        printf("Liste bos!\n");
        return;
    }

    Song* temp = *head;
    while (temp != NULL && strcmp(temp->name, name) != 0) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("'%s' listede bulunamadi!\n", name);
        return;
    }

    if (temp->prev == NULL) {
        *head = temp->next;
        if (*head != NULL) {
            (*head)->prev = NULL;
        }
    } else {
        temp->prev->next = temp->next;
        if (temp->next != NULL) {
            temp->next->prev = temp->prev;
        }
    }

    free(temp);
    printf("'%s' listeden silindi.\n", name);
}

void playNext(Song** current) {
    if (*current == NULL) {
        printf("Liste bos!\n");
        return;
    }
    if ((*current)->next != NULL) {
        *current = (*current)->next;
        printf("Simdi caliyor: %s\n", (*current)->name);
    } else {
        printf("Zaten son sarkidasiniz! Calmaya devam ediyor: %s\n", (*current)->name);
    }
}

void playPrevious(Song** current) {
    if (*current == NULL) {
        printf("Liste bos!\n");
        return;
    }
    if ((*current)->prev != NULL) {
        *current = (*current)->prev;
        printf("Simdi caliyor: %s\n", (*current)->name);
    } else {
        printf("Zaten ilk sarkidasiniz! Calmaya devam ediyor: %s\n", (*current)->name);
    }
}

void displayPlaylist(Song* head) {
    if (head == NULL) {
        printf("Liste bos!\n");
        return;
    }
    printf("\n--- Calma Listesi ---\n");
    Song* temp = head;
    int i = 1;
    while (temp != NULL) {
        printf("%d. %s\n", i++, temp->name);
        temp = temp->next;
    }
    printf("---------------------\n");
}

int main() {
    Song* head = NULL;
    Song* current = NULL;
    int choice;
    char songName[50];

    while (1) {
        printf("\n=== MUZIK CALAR MENUSU ===\n");
        if (current != NULL) {
            printf("[Su An Calan: %s]\n", current->name);
        } else {
            printf("[Su An Calan: Yok]\n");
        }
        printf("1. Sarki Ekle\n");
        printf("2. Sarki Sil\n");
        printf("3. Sonraki Sarkiyi Cal (Next)\n");
        printf("4. Onceki Sarkiyi Cal (Prev)\n");
        printf("5. Listeyi Goster\n");
        printf("0. Cikis\n");
        printf("Seciminiz: ");
        
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); 
            continue;
        }
        getchar();

        switch (choice) {
            case 1:
                printf("Eklenecek sarki adi: ");
                fgets(songName, sizeof(songName), stdin);
                songName[strcspn(songName, "\n")] = 0;

                addSongToEnd(&head, songName);
              
                if (current == NULL) {
                    current = head;
                }
                break;

            case 2:
                if (head == NULL) {
                    printf("Liste bos!\n");
                    break;
                }
                printf("Silinecek sarki adi: ");
                fgets(songName, sizeof(songName), stdin);
                songName[strcspn(songName, "\n")] = 0;

                if (current != NULL && strcmp(current->name, songName) == 0) {
                    if (current->next != NULL) {
                        current = current->next;
                    } else {
                        current = current->prev;
                    }
                }
                removeSong(&head, songName);
                if (head == NULL) {
                    current = NULL;
                }
                break;

            case 3:
                playNext(&current);
                break;

            case 4:
                playPrevious(&current);
                break;

            case 5:
                displayPlaylist(head);
                break;

            case 0:
                printf("Muzik calar kapatiliyor...\n");
                while (head != NULL) {
                    Song* temp = head;
                    head = head->next;
                    free(temp);
                }
                return 0;

            default:
                printf("Gecersiz secim! Lutfen tekrar deneyin.\n");
        }
    }
    return 0;
}