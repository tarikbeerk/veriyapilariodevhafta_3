#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Word {
    char text[50];
    struct Word* next;
} Word;

void pushWord(Word** top, char* text);
void popWord(Word** top);
void showWords(Word* top);

void pushWord(Word** top, char* text) {
    Word* newWord = (Word*)malloc(sizeof(Word));
    strcpy(newWord->text, text);
    newWord->next = *top;
    *top = newWord;
}

void popWord(Word** top) {
    if (*top == NULL) {
        printf("Geri alinacak kelime yok (Stack bos)!\n");
        return;
    }
    Word* temp = *top;
    *top = (*top)->next;
    printf("-> '%s' geri alindi (undo).\n", temp->text);
    free(temp);
}

void printInOrder(Word* current) {
    if (current == NULL) {
        return;
    }
    printInOrder(current->next);
    printf("%s ", current->text);
}

void showWords(Word* top) {
    if (top == NULL) {
        printf("-> (Metin bos)\n");
        return;
    }
    printf("-> ");
    printInOrder(top);
    printf("\n");
}

int main() {
    Word* top = NULL;
    char command[20];
    char inputWord[50];

    printf("=== UNDO SIMULASYONU ===\n");
    printf("Komutlar:\n");
    printf("  add <kelime>  (Ornek: add Merhaba)\n");
    printf("  undo          (Son kelimeyi geri alir)\n");
    printf("  show          (Metni gosterir)\n");
    printf("  exit          (Cikis)\n");
    printf("========================\n\n");

    while (1) {
        printf("> ");
        if (scanf("%s", command) != 1) {
            break;
        }

        if (strcmp(command, "add") == 0) {
            scanf("%s", inputWord);
            pushWord(&top, inputWord);
        } 
        else if (strcmp(command, "undo") == 0) {
            popWord(&top);
        } 
        else if (strcmp(command, "show") == 0) {
            showWords(top);
        } 
        else if (strcmp(command, "exit") == 0) {
            printf("Program kapatiliyor...\n");
            while (top != NULL) {
                Word* temp = top;
                top = top->next;
                free(temp);
            }
            break;
        } 
        else {
            printf("Gecersiz komut! ('add <kelime>', 'undo', 'show' veya 'exit' kullanin)\n");
            while (getchar() != '\n');
        }
    }

    return 0;
}