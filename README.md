># SoalShitSisop20_modul1_C05
> Penyelesaian Soal Shift Modul 2

## Nomor 1
Berdasarkan soal shift nomer 1 kita dituntut untuk membuat program yang serupa dengan crontab/cronjob.

#### Penyelesaian .
Berikut kode untuk menyelesaikan soal Shift nomer 1
```
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



// Fun buat cek bintang
int cekstar(char cek[]){

  if(cek[0]=='*') return 1;

  else return 0;
}

//cek Directory file
int cekfile(char dir[]){

  FILE *file;
  if ( file = fopen(dir,"r")){
    fclose(file);
    return 1;
  }

  return 0;
}

//num in string
int ceknum(char cek[]){
  int n = strlen(cek);
  int test;
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

  //untuk detik menit
  for(int i = 1 ; i < 3 ; i++ ){
    if(cekstar(argv[i])==1){
      save[i] = -1;
    }
    
    else if(ceknum(argv[i]) == 1){
      printf("invalid input kntl\n");
      exit(0);
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
      } else {}
    }
    sleep(1);
  }
}
```
Awalnya program dijalankan dengan memberi 4 argumen berupa ``detik`` ``menit`` ``jam`` dan ``path file.sh``. dalam code yang kita buat kita mneggunakan ``int main(int argc, char* argv[])``

Untuk mengatasi error yang ada dalam argumen menggunakan
```
  int save[4];
  //untuk detik menit
  for(int i = 1 ; i < 3 ; i++ ){
    if(cekstar(argv[i])==1){
      save[i] = -1;
    }
    
    else if(ceknum(argv[i]) == 1){
      printf("invalid input kntl\n");
      exit(0);
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
```
Fungsi yang bekerja untuk mengecek error yang ada.
```
// Fun buat cek bintang
int cekstar(char cek[]){

  if(cek[0]=='*') return 1;

  else return 0;
}
```
di argumen ke 4 path file harus ada maka dapat mengunaknan
```
//cek Directory file
int cekfile(char dir[]){

  FILE *file;
  if ( file = fopen(dir,"r")){
    fclose(file);
    return 1;
  }
  return 0;
}
```
dalam argumen 1 2 3 inputan harus berupa integer maka untuk mengatasi error yang ada dapat menggunakan fungsi berikut.
```
//num in string
int ceknum(char cek[]){
  int n = strlen(cek);
  int test;
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
```
Kode diatas akan mengecek setiap string-argumen yang dikirim dan mengecek satu-satu mulai dari array ke-0 argumen yang dikirim.

Setelah argumen dicek dan benar maka string argumen di ubah ke integer dengan ``atoi()`` lalu di simpan di array ``save``;

setelah mendapatkan waktu cron yang kita inputkan selanjutnya kita membuat daemon program yang berjalan setiap 1 detik. Setiap 1 detik tersebut program kita kan mencocokkan waktu yang ada pada local time  computer dengan waktu cron yang kita inputkan. Untuk mendapatkan waktu lokal menggunakan
```
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
```
untuk mendapatkan detik,menit dan jam dari localtime dapat menggunakan
```
tm.tm_sec //untuk detik
tm.tm_min //untuk menit
tm.tm_hour//untuk jam
```
Untuk mengsekusi program cron sesuai localtime dapat menggunakan
```
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
      }
    }
```

Untuk mengeksekusi file ``bash`` nya kita menggunakan ``execv`` dan dalam program daemon tersebut kita fork lagi untuk memeberi tempat atau memori untuk execv berjalan. apabila kita langsung melakukan execv tanpa melakukan fork sebelumnya maka program yang berada di bawah execv tidak akan di eksekusi , maka dari itu kita perlu tempat khusus untuk execv. Kita set ``sleep(1)`` supaya program daemon terus mengulangi proses setiap 1 detik.

### no 3
```
int main(){
    pid_t child_id;
    int status;

    child_id = fork();
    
    if(child_id < 0){
        exit(EXIT_FAILURE);
    }

    if(child_id == 0){// child
        // unziping the file
        char *arg[3] = {"unzip", "jpg.zip", NULL};
        execv("/usr/bin/unzip", arg);
    }

    else {// parent
        while ((wait(&status)) > 0);
        pid_t child_id2;
        child_id2 = fork();
        int status2;
        if(child_id2 == 0){
            // membuat folder indomie
            char *argv[] = {"mkdir", "-p", "/home/iqbalhumam73/p2/indomie", NULL};
            execv("/bin/mkdir", argv);
        }
        else{
            while ((wait(&status2)) > 0);
            int status3;
            pid_t child_id3;
            child_id3 = fork();
            if (child_id3 == 0){
                // membuat folder sedaap
                char *argv[] = {"mkdir", "-p", "/home/iqbalhumam73/p2/sedaap", NULL};
                execv("/bin/mkdir", argv);
            }
            else{
                while ((wait(&status3)) > 0);
                // memindahkan 
                struct dirent *de;  // Pointer for directory entry 
  
                // opendir() returns a pointer of DIR type.  
                DIR *dr = opendir("home/iqbalhumam73/p2/jpg"); 
  
                if (dr == NULL){  // opendir returns NULL if couldn't open directory 
                return 0; 
                } 
  
                // Refer http://pubs.opengroup.org/onlinepubs/7990989775/xsh/readdir.html 
                // for readdir() 
                while ((de = readdir(dr)) != NULL) {
                    pid_t child_id4;
                    int status4;
                    child_id4 = fork();

                    if(child_id4 == 0){
                        char *argv[] = {"mv", "-p", "/home/iqbalhumam73/p2/indomie", NULL};
                        execv("/bin/mv", argv);
                    }
                    else {
                        while ((wait(&status4)) > 0);
                    }
                }
  
                closedir(dr);     
                return 0;
            }
        }
    }
}
```
langkah pengerjaan nomor 3 adalah
- membuat fork pertama, child pertama bertujuan untuk melakukan unzip dari file jpg.zip, kemudian pada proses parent dibuat fork lagi.
- pada fork yang kedua, child proses berisi pembuatan folder indomie, dan pada parent proses membuat fork lagi
- pada fork ketiga, child proses membuat folder sedaap dan pada parent proses melakukan pengecekan tiap entry dari folder hasil extract dan akan memindahkan isinya ke folder indomie maupun folder sedaap menggunakan dirent (directory entry). namun codingannya masih belum tepat sehingga nomor 3c masih belum bisa berjalan sesuai dengna semestinya
