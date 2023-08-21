#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

char *Keywords[] = {"auto", "break", "case", "char", "const", "continue", "default",
                    "do", "double", "else", "enum", "extern", "float", "for", "goto",
                    "if", "int", "long", "register", "return", "short", "signed",
                    "sizeof", "static", "struct", "switch", "typedef", "union",
                    "unsigned", "void", "volatile", "while"};

char *Operators[] = {"+", "-", "*", "/", "%", "++", "--", "==", "!=", ">", "<", ">=", "<=", "&&", "||", "!", "**", "&", "|", "^", "~", "<<", ">>", "<<<", ">>>", "=", "+=", "-=", "*=", "/=", "%=", "<<=", ">>=", "&=", "^=", "|=", ">>>="};

char *Spec_char[] = {";", ",", "{", "}", "[", "]", "(", ")", "@", "$", "#", "^", "&", "|", "~", "`", "_", ":", "\"", "\'", "?", "\\", "."};

// Function to remove single-line and multi-line comments
void removeComments(FILE *inputFile, FILE *outputFile){
    char c, new;
    bool isSingleLineComment = false;
    bool isMultiLineComment = false;
    bool isStringLiteral = false;
    char prev = '\0';

    while ((c = fgetc(inputFile)) != EOF){
        if (isSingleLineComment){
            if (c == '\n'){
                isSingleLineComment = false;
                fputc(c, outputFile);
            }
        }
        else if (isMultiLineComment){
            if (c == '*' && (new = fgetc(inputFile)) == '/'){
                isMultiLineComment = false;
            }
        }
        else if (isStringLiteral){
            if (c == '"' && prev != '\\'){
                isStringLiteral = false;
            }
            fputc(c, outputFile);
        }
        else{
            if (c == '/' && (new = fgetc(inputFile)) == '/'){
                isSingleLineComment = true;
            }
            else if (c == '/' && new == '*'){
                isMultiLineComment = true;
            }
            else if (c == '"'){
                isStringLiteral = true;
                fputc(c, outputFile);
            }
            else{
                fputc(c, outputFile);
            }
        }
        prev = c;
    }
}

int main(){
    FILE *fptr, *fptr1;
    int keywords_count = 0, identifiers_count = 0, operators_count = 0,  spec_chars_count = 0;
    char path[100]="C:\\Users\\lokeshwar\\CLionProjects\\untitled51\\";
    char name[10];
    char str[100];
    // char ch;
    printf("Enter file name : ");
    scanf("%s", name);
    strcat(path, name);
    fptr = fopen(path, "r");
    fptr1 = fopen("C:\\Users\\lokeshwar\\CLionProjects\\untitled51\\output.txt", "w");
    if (fptr == NULL)
        printf("File is not available\n");
    else
        removeComments(fptr, fptr1);
    fclose(fptr);
    fclose(fptr1);
    fptr = fopen("C:\\Users\\lokeshwar\\CLionProjects\\untitled51\\output.txt", "r");
    if (fptr == NULL)
        printf("File is not available\n");
    else{
        while ((fgets(str, sizeof(str), fptr)) != NULL){
            char *token = strtok(str, " ()\t\n");
            while (token != NULL){
                bool isKeyword = false;
                bool isOperator = false;
                bool isSpecchar = false;
                for (int i = 0; i < 32; i++){
                    if (strcmp(token, Keywords[i]) == 0){
                        keywords_count++;
                        isKeyword = true;
                        break;
                    }
                }
                for (int i = 0; i < sizeof(Operators) / sizeof(Operators[0]); i++){
                    if (strcmp(token, Operators[i]) == 0){
                        operators_count++;
                        isOperator = true;
                        break;
                    }
                }
                for (int i = 0; i < sizeof(Spec_char) / sizeof(Spec_char[0]); i++){
                    if (strcmp(token, Spec_char[i]) == 0){
                        spec_chars_count++;
                        isSpecchar = true;
                        break;
                    }
                }
                if (isKeyword){
                    printf("%s is a keyword\n", token);
                }
                else if (isOperator){
                    printf("%s is an Operators\n", token);
                }
                else if (isSpecchar){
                     printf("%s is a special character\n", token);
                }
                else{
                    identifiers_count++;
                     printf("%s is an identifier\n", token);
                }
                token = strtok(NULL, " ()\t\n"); // Move to the next token
            }
        }
    }
    printf("No.of Keywords           : %d\n", keywords_count);
    printf("No.of identifiers        : %d\n", identifiers_count);
    printf("No.of operators          : %d\n", operators_count);
    printf("No.of special characters : %d\n", spec_chars_count);
    fclose(fptr);
    fclose(fptr1);
    fptr = fopen("C:\\Users\\lokeshwar\\CLionProjects\\untitled51\\output.txt", "r");
    fptr1 = fopen("C:\\Users\\lokeshwar\\CLionProjects\\untitled51\\output.txt", "w");
    if (fptr == NULL)
        printf("Error!!\n");
    else{
        while ((fgets(str, sizeof(str), fptr)) != NULL){
            int i = 0;
            while (isspace(str[i]))
                i++;
            if (str[i] != '#'){
                char *token = strtok(str, " \t\n");
                while (token != NULL){
                    fputs(token, fptr1);
                    token = strtok(NULL, " ");
                }
            }
        }
    }
    fclose(fptr);
    fclose(fptr1);
    return 0;
}