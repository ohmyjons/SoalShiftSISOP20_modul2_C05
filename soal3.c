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
                while ((wait(&status2)) > 0);
				struct dirent *drct;
				DIR *dir = opendir("/home/iqbalhumam73/p2/jpg");

				if (dir == NULL) {	
					return 0;
				}
	
				while ((drct = readdir(dir)) != NULL) {
					char path[100];		
					struct stat filetype;
					if (strcmp(drct->d_name, ".") == 0 || strcmp(drct->d_name, "..") == 0) {		
						continue;
					}
                    else {
						strcpy(path, "/home/iqbalhumam73/p2/jpg/");
						strcat(path, drct->d_name);

						if (stat(path, &filetype) == 0) {
							if (filetype.st_mode & S_IFDIR) {
                                if (child_id3 = fork()){
                                    child_id2 = fork();
                                    if (child_id2==0){
                                        char *move1[] = {"mv", path, "/home/iqbalhumam73/p2/indomie/", NULL};
									    execv("/bin/mv", move1);
                                    }
                                    else{
                                        while ((wait(&status2)) > 0);
                                        child_id = fork();
                                        if(child_id==0){
                                            // DIR *dir2 = opendir("/home/iqbalhumam73/p2/indomie/");
							                char *mktxt1[] = {"touch", "indomie/coba1.txt", NULL};
							                execv("/bin/touch", mktxt1);
                                            // closedir(dir2); 
                                        }
                                        else{
                                            // DIR *dir2 = opendir("/home/iqbalhumam73/p2/indomie/");
                                            char *mktxt2[] = {"touch", "indomie/coba2.txt", NULL};
							                execv("/bin/touch", mktxt2);
                                            // closedir(dir2);
                                        }
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
				closedir(dir); 
				sleep(1);
		
				// struct dirent *makefile;
				// DIR *file = opendir("/home/iqbalhumam73/p2/indomie");
		
				// while ((makefile = readdir(file)) != NULL) {
				// 	char location[100];
				// 	if (strcmp(makefile->d_name, ".") == 0 || strcmp(makefile->d_name, "..") == 0) {		
				// 		continue;
				// 	}
                //     else {
				// 		strcpy(location, "/home/iqbalhumam73/p2/indomie/");
				// 		strcat(location, makefile->d_name);
                        // child_id3 = fork();
                        // if (child_id3==0){
                        //     chdir(location);
						// 	char *mktxt1[] = {"touch", "coba1.txt", NULL};
						// 	execv("/bin/touch", mktxt1);
                        // } 
                        // else {
                        //     sleep(3);
                        //     chdir(location);
						// 	char *mktxt2[] = {"touch", "coba2.txt", NULL};
						// 	execv("/bin/touch", mktxt2);
                        // }
						// if (child_id3 = fork() > 0) {
						// 	chdir(location);
						// 	char *mktxt1[] = {"touch", "coba1.txt", NULL};
						// 	execv("/bin/touch", mktxt1);
						// } sleep(3);
						// if (child_id3 = fork() > 0) {
						// 	chdir(location);
						// 	char *mktxt2[] = {"touch", "coba2.txt", NULL};
						// 	execv("/bin/touch", mktxt2);
						// }
				// 	}
				// }
				// closedir(file);
            }
        }
    }
}