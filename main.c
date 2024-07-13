#include <stdio.h>

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
    int c, num = 0;
    // go to the end of the file
    fseek(f, 0, SEEK_END);
    // see how far skipped
    int lenOfFile = ftell(f);
    // go back to the start of the file
    fseek(f,0, SEEK_SET);
    // read every char
    while ((c=fgetc(f))!=EOF) 
        printf("\rReading char %d of %d", ++num, lenOfFile);
    // 
    printf("\r\nEOF\r\n");
    // close the file
    fclose(f);
    return 0;
}