#include <stdio.h>
#include <limits.h>

int numPlaces (int n) {
    if (n < 0) return numPlaces ((n == INT_MIN) ? INT_MAX: -n);
    if (n < 10) return 1;
    return 1 + numPlaces (n / 10);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr,"[ERROR] Not enough args provided\r\n");
        return -1;
    }
    // open file
    FILE *f = fopen(argv[1],"r"); 
    if (f==NULL){
        fprintf(stderr,"[ERROR] Cannot open file\r\n");
        return -1;
    }
    int c, num = 0, start_len = -1, end_len = -1;
    // go to the end of the file
    fseek(f, 0, SEEK_END);
    // see how far skipped
    int lenOfFile = ftell(f);
    // go back to the start of the file
    fseek(f,0, SEEK_SET);
    // read every char

    int numDigits = numPlaces(lenOfFile);

    printf("Reading char");
    while ((c=fgetc(f))!=EOF) 
        if (end_len == -1 || start_len == -1) 
            printf("\rReading char %n%*d of %d%n", &start_len, numDigits, ++num, lenOfFile, &end_len);
        else {
            for (int i = 0; i < (end_len-start_len); i++)
                printf("\b"); // delete up to "Reading char " from the back
            printf("%n%*d of %d%n", &start_len,numDigits, ++num, lenOfFile, &end_len);
        }
    // 
    printf("\r\nEOF\r\n");
    // close the file
    fclose(f);
    return 0;
}