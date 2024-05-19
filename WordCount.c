#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// ��������
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

    parameter = argv[1][1]; // ��ȡ����-c��-w
    filename = argv[2];     // ��ȡ�ļ���

    // ���ļ�
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // ���ݲ���ִ�в�ͬ��ͳ��
    if (parameter == 'c') {
        int characters = count_characters(file);
        printf("�ַ�����%d\n", characters);
    } else if (parameter == 'w') {
        int words = count_words(file);
        printf("��������%d\n", words);
    } else {
        printf("Invalid parameter: %c\n", parameter);
    }

    // �ر��ļ�
    fclose(file);
    printf("1"); 
    return 0;
}

// ͳ���ַ����ĺ���
int count_characters(FILE *file) {
    int count = 0;
    char ch;

    while ((ch = fgetc(file)) != EOF) {
        count++;
    }

    // �����Ҫ�����ļ�ָ�����õ��ļ���ʼ���Ա������ȡ��
    rewind(file);

    return count;
}

// ͳ�Ƶ������ĺ���
int count_words(FILE *file) {
    int count = 0;
    int in_word = 0;
    char ch;

    while ((ch = fgetc(file)) != EOF) {
        // ��������ո񡢶��Ż��з������ҵ�ǰ�ڵ����У������ӵ��ʼ���
        if ((isspace(ch) || ch == ',') && in_word) {
            count++;
            in_word = 0;
        }
        // ��������ǿո��ַ�������뵥��״̬
        else if (!isspace(ch) && ch != ',') {
            in_word = 1;
        }
    }

    // ���һ�����ʿ���û����ѭ���м�������������ڵ����У������Ӽ���
    if (in_word) {
        count++;
    }

    // �����Ҫ�����ļ�ָ�����õ��ļ���ʼ���Ա������ȡ��
    rewind(file);

    return count;
}



