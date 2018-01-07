#include "LAB4.h"

int main(int argc, char *argv[]){
	int op,i,r,cl,fl, nFile;
	char file[LENFILENAME];
	char buff[NCHARS];
	char teste[NCHARS];
	nFile = atoi(argv[1]);
	if((nFile>NFILES)||(nFile<0)){
		printf("Invalid file!\n");
		exit(-1);
	}
	sprintf(file, "SO2014-%d.txt", nFile);
	op = open(file, O_RDONLY);
	if(op == -1) {
		perror("Open unsuccessful");
		exit(-1);
	}
	fl = flock(op, LOCK_SH);
	if (fl ==-1){
		perror("flock unsuccessful\n");
		exit(-1);
	}
	r = read(op, teste, NBYTES);
	if(r == -1){
		perror("Read unsuccessful\n");
		exit(-1);
	}
	for(i=0; i<NLINES-1; i++){
	 r = read(op, buff, NBYTES);
	 if(r == -1){
		perror("Read unsuccessful\n");
		exit(-1);
	 }
	 if(strcmp(buff,teste) != 0){
	  printf("Incorrect file: %s\n", file);
	  exit(-1);
	 }
	}
	fl = flock(op, LOCK_UN);
	if (fl ==-1){
		perror("flock unsuccessful\n");
		exit(-1);
	}
	cl = close (op);
	if(cl == -1){
		perror("Close unsuccessful\n");
		exit(-1);
	}
	printf("Correct file: %s\n", file);
	return 0;
}
