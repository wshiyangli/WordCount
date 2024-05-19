#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// 函数声明
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

    parameter = argv[1][1]; // 提取参数-c或-w
    filename = argv[2];     // 提取文件名

    // 打开文件
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // 根据参数执行不同的统计
    if (parameter == 'c') {
        int characters = count_characters(file);
        printf("字符数：%d\n", characters);
    } else if (parameter == 'w') {
        int words = count_words(file);
        printf("单词数：%d\n", words);
    } else {
        printf("Invalid parameter: %c\n", parameter);
    }

    // 关闭文件
    fclose(file);
    printf("1"); 
    return 0;
}

// 统计字符数的函数
int count_characters(FILE *file) {
    int count = 0;
    char ch;

    while ((ch = fgetc(file)) != EOF) {
        count++;
    }

    // 如果需要，将文件指针重置到文件开始（以便后续读取）
    rewind(file);

    return count;
}

// 统计单词数的函数
int count_words(FILE *file) {
    int count = 0;
    int in_word = 0;
    char ch;

    while ((ch = fgetc(file)) != EOF) {
        // 如果遇到空格、逗号或换行符，并且当前在单词中，则增加单词计数
        if ((isspace(ch) || ch == ',') && in_word) {
            count++;
            in_word = 0;
        }
        // 如果遇到非空格字符，则进入单词状态
        else if (!isspace(ch) && ch != ',') {
            in_word = 1;
        }
    }

    // 最后一个单词可能没有在循环中计数，如果我们在单词中，则增加计数
    if (in_word) {
        count++;
    }

    // 如果需要，将文件指针重置到文件开始（以便后续读取）
    rewind(file);

    return count;
}



