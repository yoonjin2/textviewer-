#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct _line
{
    char *buf;
    struct _line *prev;
    struct _line *next;
};
typedef struct _line line;
line *head, *tail;
int total,now;
char filename[256];
void init_line(void)
{
    head=(line *)malloc(sizeof(line));
    tail=(line *)malloc(sizeof(line));
    head->next=tail;
    head->prev=head;
    tail->next=tail;
    tail->prev=head;
}
void load_file(void)
{
    FILE *fp;
    char buf[256];
    line *t;
    if((fp=fopen(filename,"rt"))==NULL)
    {
        puts("\nCANNOT READ");
        exit(1);
    }
    total=0;
    while(!feof(fp))
    {
        fgets(buf,255,fp);
        if((char *)(t=(line *)malloc(sizeof(line)))==NULL)
        {
            puts("\nOUT OF MEMORY");
            exit(1);
        }
    if((t->buf=(char *)malloc(strlen(buf)))==NULL)
        {
            puts("\nOUT OF MEMORY");
            exit(1);
        }
    strcpy(t->buf,buf);
    t->prev=tail->prev;
    t->next=tail;
    t->next=tail;
    tail->prev->next=t;
    tail->prev=t;
    total++;
    }
    fclose(fp);
}
void show_page(line *t)
{
    int i=0;
    system("clear");
    while((i++<23)&(t!=tail))
    {
        printf("%-50s\n",t->buf);
        t=t->next;
    }
}
void move_line(int d, line **t)
{
    if(d<0)
        while(d++!=0&&(*t)->prev!=head)
        {
                *t=(*t)->prev;
                now--;
        }
    else
        while(d--!=0&&(*t)->next!=tail)
        {
            *t=(*t)->next;
            now++;
        }
}
void key_proc(void)
{
    char a;
    line *t;
    t=head->next;
    now=1;
    system("stty cooked");
    show_page(t);
    while(1)
    {
        system("stty raw");
        a=getchar();
        system("stty cooked");
        switch(a)
        {
            case 65:
                move_line(-23,&t);
                break;
            case 66:
                move_line(23,&t);
                break;
            case ' ':
                exit(0);
                break;
            default:
                break;
        }
        system("clear");
        show_page(t);
    }
}
int main(int argc, char **argv)
{
    if(argc<2)
    {
        printf("\nUSAGE : txtv <filename>");
       system("stty cooked");
        exit(0);
    }
    strcpy(filename,argv[1]);
    init_line();
    load_file();
    key_proc();
}
