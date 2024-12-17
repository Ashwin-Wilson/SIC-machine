#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void swap(char *x, char *y) {
    char t = *x; *x = *y; *y = t;
}

char* reverse(char *buffer, int i, int j) {
    while (i < j) {
        swap(&buffer[i++], &buffer[j--]);
    }
    return buffer;
}

char* itoa(int value, char* buffer, int base) {
    if (base < 2 || base > 32) {
        return buffer;
    }
    int n = abs(value);
    int i = 0;
    while (n) {
        int r = n % base;
        if (r >= 10) {
            buffer[i++] = 65 + (r - 10);
        } else {
            buffer[i++] = 48 + r;
        }
        n = n / base;
    }
    if (i == 0) {
        buffer[i++] = '0';
    }
    if (value < 0 && base == 10) {
        buffer[i++] = '-';
    }
    buffer[i] = '\0';
    return reverse(buffer, 0, i - 1);
}

int main() {
    char opcode[10], operand[10], label[10], a[10], ad[10], symbol[10], ch;
    char code[10][10], code1[10][10] = {"00", "0f", "53", "57"};
    char mnemonic[10][10] = {"START", "LDA", "STA", "LDCH", "STCH", "END"};
    char mnemonic1[10][10] = {"LDA", "STA", "LDCH", "STCH"};
    int locctr, start, length, i = 0, j = 0, k, l = 0;
    int st, diff, address, add, len, actual_len, finaddr, prevaddr;
    FILE *fp1, *fp2, *fp3, *fp4, *fp5, *fp6, *fp7;

    // Open files with error checking
    if ((fp1 = fopen("input.txt", "r")) == NULL ||
        (fp2 = fopen("symtab.txt", "w")) == NULL ||
        (fp3 = fopen("intermediate.txt", "w")) == NULL) {
        perror("Error opening files");
        return EXIT_FAILURE;
    }

    fscanf(fp1, "%s%s%s", label, opcode, operand);
    if (strcmp(opcode, "START") == 0) {
        start = atoi(operand);
        locctr = start;
        fprintf(fp3, "%d\t%s\t%s\t%s\n", locctr, label, opcode, operand);
        fscanf(fp1, "%s%s%s", label, opcode, operand);
    } else {
        locctr = 0;
    }

    while (strcmp(opcode, "END") != 0) {
        fprintf(fp3, "%d\t%s\t%s\t%s\n", locctr, label, opcode, operand);

        if (strcmp(label, "**") != 0) {
            fprintf(fp2, "%s\t%d\n", label, locctr);
        }

        if (strcmp(opcode, "WORD") == 0) {
            locctr += 3;
        } else if (strcmp(opcode, "RESW") == 0) {
            locctr += (3 * atoi(operand));
        } else if (strcmp(opcode, "RESB") == 0) {
            locctr += atoi(operand);
        } else if (strcmp(opcode, "BYTE") == 0) {
            locctr += 1; // BYTE typically occupies 1 byte in machine code
        } else {
            // Lookup and process opcodes
            for (j = 0; j < 10; j++) {
                if (strcmp(opcode, mnemonic[j]) == 0) {
                    locctr += 3;
                    break;
                }
            }
        }
        fscanf(fp1, "%s%s%s", label, opcode, operand);
    }

    fprintf(fp3, "%d\t%s\t%s\t%s\n", locctr, label, opcode, operand);
    length = locctr - start;

    fclose(fp3);
    fclose(fp2);
    fclose(fp1);

    // Display contents of input file and symbol table
    printf("\n\nThe contents of Input file:\n\n");
    if ((fp1 = fopen("input.txt", "r")) == NULL) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }
    ch = fgetc(fp1);
    while (ch != EOF) {
        printf("%c", ch);
        ch = fgetc(fp1);
    }
    fclose(fp1);

    printf("\n\nLength of the input program is %d.\n", length);

    printf("\n\nThe contents of Symbol Table:\n\n");
    if ((fp2 = fopen("symtab.txt", "r")) == NULL) {
        perror("Error opening symbol table file");
        return EXIT_FAILURE;
    }
    ch = fgetc(fp2);
    while (ch != EOF) {
        printf("%c", ch);
        ch = fgetc(fp2);
    }
    fclose(fp2);

    // Prepare output files
    if ((fp4 = fopen("output.txt", "w")) == NULL ||
        (fp5 = fopen("symtab.txt", "r")) == NULL ||
        (fp6 = fopen("intermediate.txt", "r")) == NULL ||
        (fp7 = fopen("objcode.txt", "w")) == NULL) {
        perror("Error opening output files");
        return EXIT_FAILURE;
    }

    fscanf(fp6, "%d%s%s%s", &address, label, opcode, operand);
    int n = atoi(operand);

    while (strcmp(opcode, "END") != 0) {
        prevaddr = address;
        fscanf(fp6, "%d%s%s%s", &address, label, opcode, operand);
    }
    finaddr = address - n;

    fclose(fp6);
    if ((fp6 = fopen("intermediate.txt", "r")) == NULL) {
        perror("Error reopening intermediate file");
        return EXIT_FAILURE;
    }
    fscanf(fp6, "%d%s%s%s", &address, label, opcode, operand);

    if (strcmp(opcode, "START") == 0) {
        fprintf(fp4, "%d\t%s\t%s\t%s\n", address, label, opcode, operand);
        fprintf(fp7, "H^%s^00%s^00%d\n", label, operand, finaddr);
        fscanf(fp6, "%d%s%s%s", &address, label, opcode, operand);
        st = address;
        diff = prevaddr - st;
        fprintf(fp7, "T^00%d^%d", address, diff); 
    }

    while (strcmp(opcode, "END") != 0) {
        if (strcmp(opcode, "BYTE") == 0) {
            fprintf(fp4, "%d\t%s\t%s\t%s\t", address, label, opcode, operand);
            len = strlen(operand);
            actual_len = len - 3; // Exclude "C'" or "X'"
            fprintf(fp7, "^");
            for (k = 2; k < (actual_len + 2); k++) {
                itoa(operand[k], ad, 16);
                fprintf(fp4, "%s", ad);
                fprintf(fp7, "%s", ad);
            }
            fprintf(fp4, "\n");
        } else if (strcmp(opcode, "WORD") == 0) {
         len = strlen(operand); 
            itoa(atoi(operand), a, 10);
            fprintf(fp4, "%d\t%s\t%s\t%s\t00000%s\n", address, label, opcode, operand, a);
            fprintf(fp7, "^00000%s", a);
        } else if ((strcmp(opcode, "RESB") == 0) || (strcmp(opcode, "RESW") == 0)) {
            fprintf(fp4, "%d\t%s\t%s\t%s\n", address, label, opcode, operand);
        } else {
            // Process instructions
            while (strcmp(opcode, mnemonic1[l]) != 0) 
                l++; 
            if (strcmp(operand, "COPY") == 0) 
                fprintf(fp4, "%d\t%s\t%s\t%s\t%s0000\n", address, label, opcode, 
operand, code1[l]); 
            else 
            { 
                rewind(fp5); 
                fscanf(fp5, "%s%d", symbol, &add); 
                while (strcmp(operand, symbol) != 0) 
                    fscanf(fp5, "%s%d", symbol, &add); 
                fprintf(fp4, "%d\t%s\t%s\t%s\t%s%d\n", address, label, opcode, operand, 
code1[l], add); 
                fprintf(fp7, "^%s%d", code1[l], add); 
            } 
        } 
        fscanf(fp6, "%d%s%s%s", &address, label, opcode, operand); 
    }
       fprintf(fp4, "%d\t%s\t%s\t%s\n", address, label, opcode, operand); 
    fprintf(fp7, "\nE^00%d", st); 
    printf("\nObject Program has been generated."); 

    fclose(fp7);
    fclose(fp6);
    fclose(fp5);
    fclose(fp4);

    printf("\n\nObject Program:\n\n"); 
    fp7 = fopen("objcode.txt", "r"); 
    ch = fgetc(fp7); 
    while (ch != EOF) 
    { 
        printf("%c", ch); 
        ch = fgetc(fp7); 
    } 
    fclose(fp7); 

    return 0;
}

