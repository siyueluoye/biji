#include<stdio.h>
#include<unistd.h>
void progress_bar()
{
    int i;
    for(i=0;i<=100;i++)
        {
            printf("[%-50s] %d%%\r","###################################"+(50-i),i);
            fflush(stdout);
            usleep(100000);
        }
        printf("\n");
}
int main()
{
    progress_bar();
    return 0;
}
