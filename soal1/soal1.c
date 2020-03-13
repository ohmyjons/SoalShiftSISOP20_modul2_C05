#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <ctype.h>



// dari nama fungsinya dapat diketahui bahwa ini buat cek bintang
int cekstar(char cek[]){

  if(cek[0]=='*') return 1;

  else return 0;
}

int cekfile(char dir[]){

  FILE *file;
  if ( file = fopen(dir,"r")){
    fclose(file);
    return 1;
  }

  return 0;
}

//
int ceknum(char cek[]){
  int n = strlen(cek);
  int test;
  // printf("/%d/",n);
  for(int i=0;i<n;i++){
    if(isdigit(cek[i])){
      test = 0;
    }
    else {
      test = 1;
      break;
    }
    
  }

  return test;

}


int main(int argc, char* argv[]) {
  
  int save[4];

  
  /*
  for(int i=1;i<4;i++){
    printf("%d\n",atoi(argv[i]));
    printf("%d\n",save[i]);
  }*/

  //untuk detik menit
  for(int i = 1 ; i < 3 ; i++ ){
    if(cekstar(argv[i])==1){
      save[i] = -1;
    }
    
    else if(ceknum(argv[i]) == 1){
      printf("invalid input kntl\n");
      exit(0);
      // exit(EXIT_FAILURE);
      break;
    }

    else if( atoi(argv[i]) >= 0 &&  atoi(argv[i])<59 ){
      save[i] = atoi(argv[i]);
    }

    else {
      printf("kasih yang bener cok\n");
      break;
    }
  }

  //untuk jam
  if(cekstar(argv[3])==1){
      save[3] = -1;
    }
    
    else if(ceknum(argv[3]) == 1){
      printf("invalid input kntl\n");
      exit(0);
      // exit(EXIT_FAILURE);
    }

    else if( atoi(argv[3]) >= 0 &&  atoi(argv[3])<23 ){
      save[3] = atoi(argv[3]);
    }

    else {
      printf("kasih yang bener cok\n");
      exit(0);
    }

    int n = strlen(argv[4]);
    char dir[n];
    strcpy(dir,argv[4]);

    if (cekfile(dir)!=1){
      printf("file tidak ada slur\n");
      exit(0);
    }

/*
for(int i=1;i<4;i++){
  printf("%d\n",save[i]);
} */
  // exit(0);
  // exit(EXIT_FAILURE);
  

  
  pid_t pid, sid;        // Variabel untuk menyimpan PID

  pid = fork();     // Menyimpan PID dari Child Process

  /* Keluar saat fork gagal
  * (nilai variabel pid < 0) */
  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  /* Keluar saat fork berhasil
  * (nilai variabel pid adalah PID dari child process) */
  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while (1){
    
    int sec =  save[1];
    int min = save[2];
    int hour = save[3];

    // char dir[] = argv[4];
    
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    if((tm.tm_sec == sec || save[1] == -1)  && (tm.tm_min == min || save[2] == -1) && (tm.tm_hour == hour || save[3] == -1)){
      
      id_t child_id;

      child_id = fork();
  
      if (child_id < 0) {
         exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
      }

      if (child_id == 0) {
        // this is child
          
      char *run[]= {"bash" , argv[4] , NULL};
      execv("/bin/bash", run);
      } else {
        // this is parent
          
      }
    }

    
    
    sleep(1);
  }
}