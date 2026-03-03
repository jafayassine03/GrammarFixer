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

      
        if (capitalizeNext && isalpha(text[i])) {
            text[i] = toupper(text[i]);
            capitalizeNext = 0;
        }

        if ((text[i] == 'i') &&
            (i == 0 || text[i - 1] == ' ') &&
            (text[i + 1] == ' ' || text[i + 1] == '.' || text[i + 1] == ',')) {
            text[i] = 'I';
        }

        if (text[i] == '.' || text[i] == '!' || text[i] == '?') {
            capitalizeNext = 1;
        }
    }

    int len = strlen(text);
    if (text[len - 1] != '.' && text[len - 1] != '!' && text[len - 1] != '?') {
        text[len] = '.';
        text[len + 1] = '\0';
    }
}

int main() {
    char text[MAX];

    printf("Enter your essay:\n");
    fgets(text, MAX, stdin);

    text[strcspn(text, "\n")] = '\0';

    fixGrammar(text);

    printf("\nCorrected Essay:\n%s\n", text);

    return 0;
}
