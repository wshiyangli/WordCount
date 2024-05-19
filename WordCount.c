#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


int count_characters(FILE *file);
int count_words(FILE *file);

int main(int argc, char *argv[]) {
    FILE *file;
    char *filename;
    char parameter;

    if (argc != 3) {
        printf("Usage: %s [-c|-w] [input_file_name]\n", argv[0]);
        return 1;
    }

    parameter = argv[1][1]; 
    filename = argv[2];   

    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    if (parameter == 'c') {
        int characters = count_characters(file);
        printf("×Ö·ûÊý£º%d\n", characters);
    } else if (parameter == 'w') {
        int words = count_words(file);
        printf("µ¥´ÊÊý£º%d\n", words);
    } else {
        printf("Invalid parameter: %c\n", parameter);
    }

  
    fclose(file);
    printf("22222"); 
    return 0;
}

int count_characters(FILE *file) {
    int count = 0;
    char ch;

    while ((ch = fgetc(file)) != EOF) {
        count++;
    }

   
    rewind(file);

    return count;
}

int count_words(FILE *file) {
    int count = 0;
    int in_word = 0;
    char ch;

    while ((ch = fgetc(file)) != EOF) {
        
        if ((isspace(ch) || ch == ',') && in_word) {
            count++;
            in_word = 0;
        }
      
        else if (!isspace(ch) && ch != ',') {
            in_word = 1;
        }
    }

    if (in_word) {
        count++;
    }

    rewind(file);

    return count;
}



