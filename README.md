># SoalShitSisop20_modul2_C05
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
Berikut beberapa fungsi yang bekerja untuk mengecek error yang terjadi di argumen.
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

## Nomor 2
### soal
```
Shisoppu mantappu! itulah yang selalu dikatakan Kiwa setiap hari karena sekarang dia merasa sudah jago 
materi sisop. Karena merasa jago, suatu hari Kiwa iseng membuat sebuah program. 
a. Pertama-tama, Kiwa  membuat sebuah folder khusus, di dalamnya dia membuat sebuah program C 
  yang per 30 detik membuat sebuah folder dengan nama timestamp [YYYY-mm-dd_HH:ii:ss]. 
b. Tiap-tiap folder lalu diisi dengan 20 gambar yang di download dari https://picsum.photos/, 
    dimana tiap gambar di download setiap 5 detik. Tiap gambar berbentuk persegi 
    dengan ukuran (t%1000)+100 piksel dimana t adalah detik Epoch Unix. Gambar tersebut diberi nama dengan 
    format timestamp [YYYYmm-dd_HH:ii:ss]. 
c. Agar rapi, setelah sebuah folder telah terisi oleh 20 gambar, folder akan di zip dan folder 
    akan di delete(sehingga hanya menyisakan .zip). 
d. Karena takut program tersebut lepas kendali, Kiwa ingin program tersebut mengenerate sebuah program "killer" 
    yang siap di run(executable) untuk menterminasi semua operasi program tersebut. Setelah di run, program 
    yang menterminasi ini lalu akan mendelete dirinya sendiri. 
e. Kiwa menambahkan bahwa program utama bisa dirun dalam dua mode, yaitu MODE_A dan MODE_B. untuk mengaktifkan MODE_A, 
program harus dijalankan dengan argumen -a. Untuk MODE_B, program harus dijalankan dengan argumen -b. Ketika dijalankan 
dalam MODE_A, program utama akan langsung menghentikan semua operasinya ketika program killer dijalankan. Untuk MODE_B, 
ketika program killer dijalankan, program utama akan berhenti tapi membiarkan proses di setiap folder yang masih berjalan 
sampai selesai(semua folder terisi gambar, terzip lalu di delete). 

Kiwa lalu terbangun dan sedih karena menyadari programnya hanya sebuah mimpi. Buatlah program dalam mimpi Kiwa jadi nyata! 
 
Catatan: - Tidak boleh memakai system(). 
        - Program utama harus ter-detach dari terminal Hint: 
        - Gunakan fitur picsum.photos untuk mendapatkan gambar dengan ukuran    tertentu 
        - Epoch Unix bisa didapatkan dari time() 
```

Berikut kodingan kita
```
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
```

### 2.a
Dalam soal ini kita membuat sebuah folder setiap 30 detik dengan nama sesuai local time folder tersebut di buat. Untuk menyelesaikan dapat menggunakan
```
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
    
    sleep(30);
    
    }
```

### 2.b
Untuk soal 2.b kita mendowonload 20 gambar di setiap folder yang telah kita buat . lalu diberi jeda setiap download gambar adalah 5 detik. dan pixel gambar dapat kita atur sesuai epoch time unix yang ada dan kita beri nama sesuai local time.
```
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
```
### 2.c
file file yang telah kita buat dati lalu kita ubah ke format zip.
berikut kodingan yang kita gunakan.
```
 child2 = fork();
    if (child2 < 0) exit(EXIT_FAILURE);
        if (child2 == 0) {
            char zip_name[100];
            sprintf(zip_name, "%s.zip", dir);
            char *argv[] = {"zip", "-rm", zip_name, dir, NULL};
            execv("/usr/bin/zip", argv);
            exit(0); 
        }
```
namun ada kesalah dalam mengerjakan soal nomer 2 ini dimana seharusnya semua program berjalan bersama terus menerus. di program ini sudah benar sampai langkah 2b namun ketika langkah 2c program menuggu 1 file selesai dulu baru di zip dan membuat file baru lagi. ketiga program nomer 2c kita command maka program 2a-2b benar berjalan seperti sewajarnya
### no 3
```
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <dirent.h>


int main(){
    pid_t child_id;
    int status;

    child_id = fork();
```
pembuatan fork pertama
```    
    if(child_id < 0){
        exit(EXIT_FAILURE);
    }

    if(child_id == 0){
        // MENGUNZIP FILE JPG
        char *arg[3] = {"unzip", "jpg.zip", NULL};
        execv("/usr/bin/unzip", arg);
    }
```
child yang pertama berguna untuk melakukan unzip file jpg.zip, pengunzipan menggunakan execv
```
    else {
        while ((wait(&status)) > 0);
        pid_t child_id2;
        child_id2 = fork();
```
pada parent, dibuat fork lagi dan menjadi fork kedua
```        
        int status2;
        if(child_id2 == 0){
            // MEMBUAT FOLDER INDOMIE
            char *argv[] = {"mkdir", "-p", "/home/iqbalhumam73/p2/indomie", NULL};
            execv("/bin/mkdir", argv);
        }
```
child ke-2 digunakan untuk membuat folder indomie, karena tidak diperbolehkan menggunakan C mkdir, maka pembuatan juga menggunakan execv
```
        else{
            while ((wait(&status2)) > 0);
            int status3;
            pid_t child_id3;
            child_id3 = fork();
```
pada parent dibuat fork lagi sebagai fork ke-3
```
            if (child_id3 == 0){
                // MEMBUAT FOLDER SEDAAP
                char *argv[] = {"mkdir", "-p", "/home/iqbalhumam73/p2/sedaap", NULL};
                execv("/bin/mkdir", argv);
            }
```
child ke tiga digunakan untuk membuat folder sedaap, pembuatannya juga menggu nakan execv
```
            else{
                // MEMINDAHKAN DIREKTORI KE INDOMIE, DAN FILE KE SEDAAP
                while ((wait(&status2)) > 0);
				struct dirent *drct;
				DIR *dir = opendir("/home/iqbalhumam73/p2/jpg");
```
untuk memindahkan file dan directory yang berada pada folder jpg, kita harus menggunakan pointer dirent yang akan menunjuk entry dari folder jpg
selanjutnya direktori jpg dibuka menggunakan opendir dan disimpan di variabel dir
				if (dir == NULL) {	
					return 0;
				}
	
				while ((drct = readdir(dir)) != NULL) {
					char path[100];		
					struct stat filetype;
					if (strcmp(drct->d_name, ".") == 0 || strcmp(drct->d_name, "..") == 0) {		
						continue;
					}
```
kemudian folder dir (jpg) dicek apakah kosong atau tidak, apabila kosong langsung di return 0.
kemudian entry yang ditunjuk oleh drct dicek dulu apakah namanya . / .. karena pada soal tidak diperbolehkan, apabila namanya ./.. diskip
```
                    else {
						strcpy(path, "/home/iqbalhumam73/p2/jpg/");
						strcat(path, drct->d_name);
```
kemudian dengan string path, path dari entry disimpan dan ditambahkan nama dari entry dengan strcat untuk selanjutnya
```
						if (stat(path, &filetype) == 0) {
							if (filetype.st_mode & S_IFDIR) {
                                if (child_id3 = fork()){
                                    child_id2 = fork();
                                    if (child_id2==0){
                                        char *move1[] = {"mv", path, "/home/iqbalhumam73/p2/indomie/", NULL};
									    execv("/bin/mv", move1);
                                    }
```
kemudian entry yang ditunjuk dicek menggukann ifdir, apabila iya, dipindahkan ke indomie
```
                                    else{
                                        // MEMBUAT 2 FILE TXT KE DIREKTORI YANG DIPINDAHKAN KE INDOMIE
                                        while ((wait(&status2)) > 0);
                                        child_id = fork();
                                        if(child_id==0){
							                char *mktxt1[] = {"touch", "indomie/coba1.txt", NULL};
							                execv("/bin/touch", mktxt1);
                                        }
                                        else{
                                            char *mktxt2[] = {"touch", "indomie/coba2.txt", NULL};
							                execv("/bin/touch", mktxt2);
                                        }
```
selagi memindahkan, sekalian membuat 2 file coba di dir yang dipindahkan, namun masih salah dan 2 file nya tidak terbuat
```
                                    }
                                }
							}
                            else {
								if (child_id3 = fork() == 0) {
									char *move2[] = {"mv", path, "/home/iqbalhumam73/p2/sedaap/", NULL};
									execv("/bin/mv", move2);
								} 
							}
						}
					}
				}
```
apabila yang ditunjuk bukan directory, maka dipindah ke sedaap
				closedir(dir);
            }
        }
    }
}
