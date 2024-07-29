#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1000
#define MAX_LEN 100

typedef struct Word {
    char *word;
    int count;
    struct Word *next;
} Word;

Word word_list[MAX_WORDS];

Word *find_word(char *word) {
    for (int i = 0; i < MAX_WORDS; i++) {
        if (word_list[i].word == NULL) continue;
        if (strcmp(word_list[i].word, word) == 0) {
            return &word_list[i];
        }
    }
    return NULL;
}

void add_word(char *word) {
    Word *w = find_word(word);
    if (w == NULL) {
        for (int i = 0; i < MAX_WORDS; i++) {
            if (word_list[i].word == NULL) {
                w = &word_list[i];
                break;
            }
        }
        w->word = strdup(word);
        w->count = 1;
        w->next = NULL;
    } else {
        w->count++;
    }
}

int main() {
    printf("Enter a paragraph: ");

    // Read the paragraph into a buffer
    char buf[MAX_LEN];
    fgets(buf, sizeof(buf), stdin);

    // Tokenize the paragraph into words
    char *token = strtok(buf, " \t\n\r.,;:!?");
    while (token != NULL) {
        // Convert the word to lowercase
        for (int i = 0; token[i]; i++) {
            token[i] = tolower(token[i]);
        }

        // Add the word to the hash table
        add_word(token);

        // Get the next word
        token = strtok(NULL, " \t\n\r.,;:!?");
    }

    // Print the frequencies of the words
    for (int i = 0; i < MAX_WORDS; i++) {
        if (word_list[i].word == NULL) continue;
        printf("%s: %d\n", word_list[i].word, word_list[i].count);
        free(word_list[i].word);
    }

    return 0;
}