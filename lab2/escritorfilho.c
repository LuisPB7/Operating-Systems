#include "LAB2.h"

int main(){
	int i,j, op, wr,cl;
	char *file, *string;
	char* files[NFILES] = {"SO2014-0.txt","SO2014-1.txt","SO2014-2.txt","SO2014-3.txt","SO2014-4.txt"};
	char* strings[NSTRINGS] = {"aaaaaaaaa\n","bbbbbbbbb\n","ccccccccc\n","ddddddddd\n","eeeeeeeee\n","fffffffff\n","ggggggggg\n","hhhhhhhhh\n","iiiiiiiii\n","jjjjjjjjj\n"};
	srand(time(NULL));
	for(i=0; i<NTIMES;i++){
		file = files[rand()%NFILES];
		string = strings[rand()%NSTRINGS];
		op = open(file, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IROTH);
		if(op == -1) {
			printf("Open unsuccessful\n");
			return -1;
		}
		for(j=0; j<NLINES;j++){
			wr = write(op, string, NBYTES);
			if(wr == -1){
				printf("Write unsuccessful\n");
				return -1;
			}
		}
		cl = close (op);
		if(cl == -1){
			printf("Close unsuccessful\n");
			return -1;
		}
	}
	return 0;
}
