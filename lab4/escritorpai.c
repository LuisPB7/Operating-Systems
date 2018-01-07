#include "LAB4.h"

int main(){
	
	int i, estado, ex, w;
	pid_t pid;
	struct timeval tvstart; 
	struct timeval tvend; 
	struct timeval tvduration; 
	unsigned int duration;
	time_t curtime; 
	char buffer[30]; 
	gettimeofday(&tvstart, NULL); 
	curtime=tvstart.tv_sec;
	strftime(buffer,30,"%m-%d-%Y  %d.",localtime(&curtime));

	for(i=0;i<NTIMESCHILD;i++){
		pid = fork();
		if(pid == -1){
			printf("Fork has failed\n");
			return -1;
		}
		if(pid==0){
			ex = execl("./escritorfilho", "escritorfilho",NULL);
			if(ex==-1){
				printf("Execl has failed\n");
				return -1;
			}
			exit(estado);
		}
	}
	
	for(i=0;i<NTIMESCHILD;i++){
		w = wait(&estado);
		if(w==-1){
			printf("Wait failed\n");
			return -1;
		}
	}
	
    gettimeofday(&tvend, NULL); 
    curtime=tvend.tv_sec;
    strftime(buffer,30,"%m-%d-%Y  %d.",localtime(&curtime));
    tvduration.tv_sec = tvend.tv_sec - tvstart.tv_sec;
    tvduration.tv_usec = tvend.tv_usec - tvstart.tv_usec;
    duration = tvduration.tv_sec * 1000000 + tvduration.tv_usec;
    printf("Duracao: %f segundos\n", (double)duration/1000000);
	return 0;
	
}
