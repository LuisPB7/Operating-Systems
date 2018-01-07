#include "LAB2.h"

int main(){
	int op,i,r,cl;
	char *file;
	char buff[NCHARS];
	char teste[NCHARS];
	char* files[NFILES] = {"SO2014-0.txt","SO2014-1.txt","SO2014-2.txt","SO2014-3.txt","SO2014-4.txt"};
	srand(time(NULL));
	file = files[rand()%NFILES];
	op = open(file, O_RDONLY);
	if(op == -1) {
		printf("Open unsuccessful\n");
		return -1;
	}
	r = read(op, teste, NBYTES);
	if(r == -1){
		printf("Read unsuccessful\n");
		return -1;
	}
	for(i=0; i<NLINES-1; i++){
	 r = read(op, buff, NBYTES);
	 if(r == -1){
		printf("Read unsuccessful\n");
		return -1;
	 }
	 if(strcmp(buff,teste) != 0){
	  printf("Incorrect file\n");
	  return -1;
	 }
	}
	cl = close (op);
	if(cl == -1){
		printf("Close unsuccessful\n");
		return -1;
	}
	printf("Correct file\n");
	return 0;
}
