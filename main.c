#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <strings.h>

int MAX_WORD = 20;
int MAX_CHAR = 200;

void fileHandler ()
{
    FILE* fileptr = fopen("log.txt","a");
    fputs("Chiled process done!\n", fileptr);
    fclose(fileptr);

}

int process_line(char* args[],char line[])
{
    int i = 0;
    args[i] = strtok (line," ");

    if (args[i] == NULL)
    {
        return 1;
    }

    while (args[i] != NULL)
    {
        i++;
        args[i] = strtok (NULL," ");     /// eih el kalam /// if not NULL resets el pointer DUHHHHH
    }
    return 1;
}


void remove_endOfLine(char line[])
{
    int i=0;
    while (line[i] != '\n')
        i++;
    line[i]='\0';
}

void read_line(char line[])
{
    fgets (line,MAX_CHAR,stdin);
    remove_endOfLine(line);

    if ( strcmp (line,"exit") == 0 )      /// exit :3 or dont i dont care
        exit (0);
}

int parser(char* args[], char line[])
{
    read_line(line);
    process_line(args,line);
    return 1;
}

int main()
{
    char* args[MAX_WORD];
    char  line[MAX_CHAR];
    //int status;

    FILE* fileptr;
    fileptr = fopen("log.txt","w");
    fclose(fileptr);

    while (parser(args,line))
    {
        pid_t pid=fork();

        if (pid == 0)
        {


            execvp(args[0],args);
           // if (args[1] != NULL)
             //   if (strcmp(args[1], "&" == '&'))
               //     execvp(args[1],args);


        }
        else
        {
            signal ( SIGCHLD, fileHandler );
            //wait(&status);
            waitpid (pid,0);
        }
    }

    return 0;
}
