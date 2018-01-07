#include "LAB5.h"

pthread_t threads[NTHREADS];
char* wrongLines[NSTRINGS] ={"0aaaaaaaa\n", "0bbbbbbbb\n", "0cccccccc\n", "0dddddddd\n", "0eeeeeeee\n", "0ffffffff\n", "0gggggggg\n", "0hhhhhhhh\n", "0iiiiiiii\n", "0jjjjjjjj\n"};
int* status;
struct sigaction usr1_action, usr2_action, tstp_action;

/* flags para os signals */
int switchLocks = 0;
int wrongWriting = 0;
int keepWriting = 1;

/* handlers dos signals */
void sigusr1_handler(int signum){
	if (sigaction(SIGUSR1, &usr1_action, NULL)){
	   perror("Failed to handle SIGTSTP signal");
	   exit(-1);
   }
	switchLocks = (switchLocks+1)%2;
}

void sigusr2_handler(int signum){
	if (sigaction(SIGUSR2, &usr2_action, NULL)){
	   perror("Failed to handle SIGTSTP signal");
	   exit(-1);
   }
	wrongWriting = (wrongWriting+1)%2;	
}

void sigtstp_handler(int signum){
	int i;
	if (sigaction(SIGTSTP, &tstp_action, NULL)){
	   perror("Failed to handle SIGTSTP signal");
	   exit(-1);
   }
   keepWriting = 0;
   for (i=0;i<NTHREADS;i++){
        pthread_join(threads[i],(void*)&status);
        if(status != (int*)0){
			perror("Failed to join threads");
			exit(-1);
		}
	}
}


void* escritor(){
	int i,j, op, wr,cl,fl, *status;
	char *file, *string;
	char* files[NFILES] = {"SO2014-0.txt","SO2014-1.txt","SO2014-2.txt","SO2014-3.txt","SO2014-4.txt"};
	char* strings[NSTRINGS] = {"aaaaaaaaa\n","bbbbbbbbb\n","ccccccccc\n","ddddddddd\n","eeeeeeeee\n","fffffffff\n","ggggggggg\n","hhhhhhhhh\n","iiiiiiiii\n","jjjjjjjjj\n"};
	srand(time(NULL));
	while(1){
		if(keepWriting==0){
			break;
		}
		file = files[rand()%NFILES];
		string = strings[rand()%NSTRINGS];
		op = open(file, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IROTH);
		if(op == -1) {
			perror("Open unsuccessful");
			pthread_exit((void*)-1);
		}
		if(!switchLocks){
			fl = flock(op,LOCK_EX);
			if(fl==-1){
				perror("flock unsuccessful");
				pthread_exit((void*)-1);
			}
		}
		for(j=0; j<NLINES;j++){
			if(wrongWriting){
				if(j%2 == 0){
					wr = write(op, string, NBYTES);
					if(wr == -1){
					perror("Write unsuccessful");
					pthread_exit((void*)-1);
					}
				}
				else{
					wr = write(op, wrongLines[rand()%NSTRINGS], NBYTES);
					if(wr == -1){
					perror("Write unsuccessful");
					pthread_exit((void*)-1);
					}
				}
			}
			else{
				wr = write(op, string, NBYTES);
				if(wr == -1){
					perror("Write unsuccessful");
					pthread_exit((void*)-1);
				}
			}
			
		}
		if(!switchLocks){
			fl = flock(op, LOCK_UN);
			if(fl==-1){
				perror("flock unsuccessful");
				pthread_exit((void*)-1);
			}
		}
		cl = close (op);
		if(cl == -1){
			perror("Close unsuccessful");
			pthread_exit((void*)-1);
		}
		if(keepWriting==0){
			break;
		}
	}
	for (i=0;i<NTHREADS;i++){
        pthread_join(threads[i],(void*)&status);
        if(status != (int*)0){
			perror("Failed to join threads");
			exit(-1);
		}
	}
	return NULL;
}

int main(){
	int i, *status;

  /* Tratamento SIGUSR1 */
  usr1_action.sa_handler = sigusr1_handler;
  sigemptyset (&usr1_action.sa_mask);
  sigaddset(&usr1_action.sa_mask, SIGUSR1);
  usr1_action.sa_flags = 0;
  sigaction(SIGUSR1, &usr1_action, NULL);
  
  /* Tratamento SIGUSR2 */
  usr2_action.sa_handler = sigusr2_handler;
  sigemptyset (&usr2_action.sa_mask);
  sigaddset(&usr2_action.sa_mask, SIGUSR2);
  usr2_action.sa_flags = 0;
  sigaction(SIGUSR2, &usr2_action, NULL);
  
  /* Tratamento SIGTSTP */
  tstp_action.sa_handler = sigtstp_handler;
  sigemptyset (&tstp_action.sa_mask);
  sigaddset(&tstp_action.sa_mask, SIGTSTP);
  tstp_action.sa_flags = 0;
  sigaction(SIGTSTP, &tstp_action, NULL); 
  
   if (sigaction(SIGUSR1, &usr1_action, NULL)){
	   perror("Failed to handle SIGUSR1 signal");
	   exit(-1);
   }
   
   if (sigaction(SIGUSR2, &usr2_action, NULL)){
	   perror("Failed to handle SIGUSR2 signal");
	   exit(-1);
   }
    
   if (sigaction(SIGTSTP, &tstp_action, NULL)){
	   perror("Failed to handle SIGTSTP signal");
	   exit(-1);
   }
   
	for(i=0;i<NTHREADS;i++){
		if(pthread_create(&(threads[i]),NULL, escritor, NULL)){
			perror("Failed to create thread");
			exit(-1);
		}
	}
	
	pthread_exit((void*)&status);
	return 0;
}
