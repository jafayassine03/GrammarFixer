#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 1000

void fixGrammar(char text[]) {
    int i;
    int capitalizeNext = 1;
    int spaceFlag = 0;

    for (i = 0; text[i] != '\0'; i++) {

        if (text[i] == ' ') {
            if (spaceFlag == 1) {
                int j = i;
                while (text[j] != '\0') {
                    text[j] = text[j + 1];
                    j++;
                }
                i--;
                continue;
            }
            spaceFlag = 1;
        } else {
            spaceFlag = 0;
        }

        if ((text[i] == '.' || text[i] == ',' || text[i] == '!' || text[i] == '?') 
            && i > 0 && text[i - 1] == ' ') {
            
            int j = i - 1;
            while (text[j] != '\0') {
                text[j] = text[j + 1];
                j++;
            }
            i--;
            continue;
        }

        if (capitalizeNext && isalpha(text[i])) {
            text[i] = toupper(text[i]);
            capitalizeNext = 0;
        }

        if ((text[i] == 'i') &&
            (i == 0 || text[i - 1] == ' ') &&
            (text[i + 1] == ' ' || text[i + 1] == '.' || 
             text[i + 1] == ',' || text[i + 1] == '!' || text[i + 1] == '?')) {
            text[i] = 'I';
        }

        if (text[i] == '.' || text[i] == '!' || text[i] == '?') {

            if (text[i + 1] != ' ' && text[i + 1] != '\0') {
                int len = strlen(text);
                for (int j = len; j > i + 1; j--) {
                    text[j] = text[j - 1];
                }
                text[i + 1] = ' ';
            }

            capitalizeNext = 1;
        }
    }

    int len = strlen(text);
    if (len > 0 &&
        text[len - 1] != '.' &&
        text[len - 1] != '!' &&
        text[len - 1] != '?') {

        text[len] = '.';
        text[len + 1] = '\0';
    }
}

int countWords(char text[]) {
    int words = 0;
    int inWord = 0;

    for (int i = 0; text[i] != '\0'; i++) {
        if (isspace(text[i])) {
            inWord = 0;
        } else if (!inWord) {
            inWord = 1;
            words++;
        }
    }

    return words;
}

int main() {
    char text[MAX];

    printf("Enter your essay:\n");
    fgets(text, MAX, stdin);

    text[strcspn(text, "\n")] = '\0';

    fixGrammar(text);

    printf("\nCorrected Essay:\n%s\n", text);

    int wordCount = countWords(text);
    printf("\nWord Count: %d\n", wordCount);

    return 0;
}
