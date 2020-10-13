#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main (int argc, char *argv[], char *env[]) {
    if (argc > 1) {
        char * word = strtok (argv[1], " ");
        char path[128] = "/bin/";
        strcat (path, word);

        printf ("%s\n", path);
		char *p_env[] = { path, NULL };
        int ret = execve (path, NULL, p_env);
        if (ret == -1) {
            perror("execve error");
        }
		else {
			printf ("\nreturn : %d\n", ret);
		}
    }
    return 0;
}
