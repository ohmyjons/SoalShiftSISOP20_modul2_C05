SoalShiftSISOP20_modul2_C05

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
