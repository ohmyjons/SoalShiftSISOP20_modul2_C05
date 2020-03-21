#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <wait.h>
#include <string.h>

int main() {
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

  while (1) {

    time_t t;
    struct tm *tm;
    char get_time[25];
    time(&t);
    tm = localtime(&t);
    strftime(get_time,sizeof(get_time),"%Y-%M-%d_%X",tm);


    // struct stat st = {0};
    char dir[200] = "/home/dohan/sisop20/modul2/soal/";
    // make folder
    strcat(dir,get_time);
    int result = mkdir(dir, 0777);

    
    pid_t child1,child2;
    int status;

    child1 = fork();

    if (child1 < 0) 
    {
    exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
    }

    if (child1 == 0)
    {
    while((wait(&status)) > 0);
        int i;
        char link[200];
        strcpy(link, "https://picsum.photos/");
        for(i=0; i<20; i++){

            time_t rawtime;
            rawtime = time(NULL);
            struct tm *timeinfo;
            timeinfo = localtime(&rawtime);
            char get_time2[200];
            strftime (get_time2, sizeof(get_time2), "%Y-%m-%d_%H:%M:%S", timeinfo);
            char pictname[200];
            snprintf(pictname, sizeof(pictname), "%s/%s", dir, get_time2);
            char pict_size[200];
            snprintf(pict_size, sizeof(pict_size), "%s/%ld", link, (time(NULL)%1000 + 100));

            pid_t child_id = fork();
            if(child_id == 0)
            {
                char *argv[] = {"wget", "-O", pictname, pict_size, NULL};
                execv("/usr/bin/wget", argv);
            }
            sleep(5);
        }
        for(int i = 0; i< 20;i++)
        wait(NULL);

    }
    // while (wait(&status)>0);
    /*
    child2 = fork();
    if (child2 < 0) exit(EXIT_FAILURE);

        if (child2 == 0) {
            char zip_name[100];
            sprintf(zip_name, "%s.zip", dir);

            char *argv[] = {"zip", "-rm", zip_name, dir, NULL};
            execv("/usr/bin/zip", argv);
            exit(0); 
        }
    */

    sleep(30);
  }
}