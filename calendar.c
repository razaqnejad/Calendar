#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <stdlib.h>

void read_the_file(void);
void goto_sharp(int*);
void home_page(void);
void event_page(void);
void task_page(void);
void edit_events(void);
void edit_tasks(void);
void menu(void);
long* gregorian_to_jalali(long gy,long gm,long gd,long out[]);
int day_of_year(int,int,int);

struct days{
    int NOD; //number of day
    char event[10][100];
    char task[10][100];
}day[365];
int d=0,sd=0;
int FDOY=3;//first day of year
char DOW[10];//day of week;
   
int main()
{
    read_the_file();
    home_page();
    while(1){
    char c=getchar();
    switch(c)
    {
        case 'n':
            d++;
            home_page();
            break;
        case 'p':
            d--;
            home_page();
            break;
        case 'd':
            d=0;
            home_page();
            break;
        case 'e':
            event_page();
            break;
        case 't':
            task_page();
            break;
        case 'E':
            edit_events();
            break;
        case 'm':
            menu();
            home_page();
            break;
        case 'T':
            edit_tasks();
            break;
        case 'c':
            exit(0);
            break;
    }
}}

void read_the_file(void)
{
    int p=0;
    FILE *f;
    f=fopen("calendar.txt","r");
    int i=0,j=0,h=0;
    while (fgetc(f)!=EOF)
    {
        goto_sharp(&p);
        fseek(f,p,SEEK_SET);
        p++;
        day[i].NOD=i;
        while(fgetc(f)!='$' && fgetc(f)!=EOF)
        {
            fgets(day[i].event[j],sizeof(day[i].event[j]),f);
            j++;
        }
        fseek(f,-2,SEEK_CUR);
        while(fgetc(f)!='^' && fgetc(f)!=EOF)
        {
            fgets(day[i].task[h],sizeof(day[i].task[h]),f);
            h++;
        }
        i++;
    }
    fclose(f);
    return;
}

void goto_sharp(int *p)
{
    FILE *f;
    f=fopen("calendar.txt","r");
    fseek(f,*p,SEEK_SET);
    while(fgetc(f)!='#')
        (*p)++;
    fclose(f);
    return;
}

void home_page(void)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_BLUE);
    long out[3];
    if (sd!=0)
        d=(sd*86400)-time(NULL);
    time_t t = time(NULL)+d*86400+86400;
    struct tm tm = *localtime(&t);
    gregorian_to_jalali(tm.tm_year+1900,tm.tm_mon,tm.tm_yday,out);
    int a=day_of_year(tm.tm_mon,tm.tm_yday,tm.tm_year+1900);
    system("cls");
    printf(" __________________________________________________\n");
    printf("|                                                  |\n");
    switch((a+FDOY)%7)
    {
        case 0:
            printf("|  %d/%02d/%02d                           saturday   |\n",tm.tm_year+1900,tm.tm_mon,tm.tm_yday);
            break;
        case 1:
            printf("|  %d/%02d/%02d                             sunday   |\n",tm.tm_year+1900,tm.tm_mon,tm.tm_yday);
            break;
        case 2:
            printf("|  %d/%02d/%02d                             monday   |\n",tm.tm_year+1900,tm.tm_mon,tm.tm_yday);
            break;
        case 3:
            printf("|  %d/%02d/%02d                            tuesday   |\n",tm.tm_year+1900,tm.tm_mon,tm.tm_yday);
            break;
        case 4:
            printf("|  %d/%02d/%02d                          wednesday   |\n",tm.tm_year+1900,tm.tm_mon,tm.tm_yday);
            break;
        case 5:
            printf("|  %d/%02d/%02d                           thursday   |\n",tm.tm_year+1900,tm.tm_mon,tm.tm_yday);
            break;
        case 6:
            printf("|  %d/%02d/%02d                             friday   |\n",tm.tm_year+1900,tm.tm_mon,tm.tm_yday);
            break;
    }
    printf("|  %d/%02d/%02d                                      |\n",out[0],out[1],out[2]);
    printf("|__________________________________________________|\n");
    printf("|                                                  |\n");
    printf("|   %02d:%02d:%02d                                       |\n",tm.tm_hour,tm.tm_min,tm.tm_sec);
    printf("|                                                  |\n");
    printf("|  events                                          |\n");
    printf("| ========                                         |\n");
    printf("|  %-46s  |\n",day[a].event[0]);
    printf("|                                                  |\n");
    printf("|                                                  |\n");
    printf("|                                                  |\n");
    printf("|                                                  |\n");
    printf("|                                                  |\n");
    printf("|                                                  |\n");
    printf("|                                                  |\n");
    printf("|  tasks                                           |\n");
    printf("| =======                                          |\n");
    printf("|  %-46s  |\n",day[a].event[0]);
    printf("|                                                  |\n");
    printf("|                                                  |\n");
    printf("|                                                  |\n");
    printf("|                                                  |\n");
    printf("|                                                  |\n");
    printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
    printf("*press n to go to next day  \n");
    printf("*press p to go to previous day  \n");
    printf("*press d to go to today  \n");
    printf("*press e to see events  \n");
    printf("*press t to see tasks  \n");
    printf("*press E to edit events  \n");
    printf("*press T to edit tasks  \n");
    printf("*press m to menu  \n");
    printf("*press c to exit  \n");
}

long* gregorian_to_jalali(long gy,long gm,long gd,long out[]){
 long gy2,days,jy,jm,jd, g_d_m[12]={0,31,59,90,120,151,181,212,243,273,304,334};
 if(gy>1600){
  jy=979;
  gy-=1600;
 }else{
  jy=0;
  gy-=621;
 }
 gy2=(gm>2)?(gy+1):gy;
 days=(365*gy) +((int)((gy2+3)/4)) -((int)((gy2+99)/100)) +((int)((gy2+399)/400)) -80 +gd +g_d_m[gm-1];
 jy+=33*((int)(days/12053)); 
 days%=12053;
 jy+=4*((int)(days/1461));
 days%=1461;
 if(days > 365){
  jy+=(int)((days-1)/365);
  days=(days-1)%365;
 }
 jm=(days < 186)?1+(int)(days/31):7+(int)((days-186)/30);
 jd=1+((days < 186)?(days%31):((days-186)%30));
 out[0]=jy;
 out[1]=jm;
 out[2]=jd;
 return out;
}


long* jalali_to_gregorian(long jy,long jm,long jd,long out[]){
 long days,gy,gm,gd, sal_a[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
 if(jy>979){
  gy=1600;
  jy-=979;
 }else{
  gy=621;
 }
 days=(365*jy) +(((int)(jy/33))*8) +((int)(((jy%33)+3)/4)) +78 +jd +((jm<7)?(jm-1)*31:((jm-7)*30)+186);
 gy+=400*((int)(days/146097));
 days%=146097;
 if(days > 36524){
  gy+=100*((int)(--days/36524));
  days%=36524;
  if(days >= 365)days++;
 }
 gy+=4*((int)(days/1461));
 days%=1461;
 if(days > 365){
  gy+=(int)((days-1)/365);
  days=(days-1)%365;
 }
 gd=days+1;
 if((gy%4==0 && gy%100!=0) || (gy%400==0))sal_a[2]=29;
 for(gm=0;gm<13;gm++){
  long v=sal_a[gm];
  if(gd <= v)break;
  gd-=v;
 }
 out[0]=gy;
 out[1]=gm;
 out[2]=gd;
 return out;
}

int day_of_year(int a, int b, int c)//month,day,year
{
	int i=0, daymon=0, dayday=0;
	int mth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; 

	dayday = b;
	
	for (i = 0; i < a; i++)
	{
		daymon += mth[i];
	}


return (daymon + dayday);
}

void event_page(void)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_BLUE);
    long out[3];
    time_t t = time(NULL)+d*86400+86400;
    struct tm tm = *localtime(&t);
    gregorian_to_jalali(tm.tm_year+1900,tm.tm_mon,tm.tm_yday,out);
    int a=day_of_year(tm.tm_mon,tm.tm_yday,tm.tm_year+1900);
    system("cls");
    printf(" __________________________________________________\n");
    printf("|                                                  |\n");
    switch((a+FDOY)%7)
    {
        case 0:
            printf("|  %d/%02d/%02d                           \033[;33msaturday\033[0m   |\n",tm.tm_year+1900,tm.tm_mon,tm.tm_yday);
            break;
        case 1:
            printf("|  %d/%02d/%02d                             sunday   |\n",tm.tm_year+1900,tm.tm_mon,tm.tm_yday);
            break;
        case 2:
            printf("|  %d/%02d/%02d                             monday   |\n",tm.tm_year+1900,tm.tm_mon,tm.tm_yday);
            break;
        case 3:
            printf("|  %d/%02d/%02d                            tuesday   |\n",tm.tm_year+1900,tm.tm_mon,tm.tm_yday);
            break;
        case 4:
            printf("|  %d/%02d/%02d                          wednesday   |\n",tm.tm_year+1900,tm.tm_mon,tm.tm_yday);
            break;
        case 5:
            printf("|  %d/%02d/%02d                           thursday   |\n",tm.tm_year+1900,tm.tm_mon,tm.tm_yday);
            break;
        case 6:
            printf("|  %d/%02d/%02d                             friday   |\n",tm.tm_year+1900,tm.tm_mon,tm.tm_yday);
            break;
    }
    printf("|  %d/%02d/%02d                             EVENTS   |\n",out[0],out[1],out[2]);
    printf("|__________________________________________________|\n");
    printf("|                                                  |\n");
    printf("|   %02d:%02d:%02d                                       |\n",tm.tm_hour,tm.tm_min,tm.tm_sec);
    printf("|                                                  |\n");
    printf("|  title                                           |\n");
    printf("| =======                                          |\n");
    printf("|  %-46s  |\n",day[a].event[0]);
    printf("|                                                  |\n");
    printf("|  %-46s  |\n",day[a].event[1]);
    printf("|  %-46s  |\n",day[a].event[2]);
    printf("|  %-46s  |\n",day[a].event[3]);
    printf("|  %-46s  |\n",day[a].event[4]);
    printf("|  %-46s  |\n",day[a].event[5]);
    printf("|  %-46s  |\n",day[a].event[6]);
    printf("|  %-46s  |\n",day[a].event[7]);
    printf("|  %-46s  |\n",day[a].event[8]);
    printf("|  %-46s  |\n",day[a].event[9]);
    printf("|                                                  |\n");
    printf("|                                                  |\n");
    printf("|                                                  |\n");
    printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
    printf("*press d to go back today  \n");
    printf("*press m to menu  \n");
    printf("*press c to exit  \n");
}

void task_page(void)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_BLUE);
    long out[3];
    time_t t = time(NULL)+d*86400+86400;
    struct tm tm = *localtime(&t);
    gregorian_to_jalali(tm.tm_year+1900,tm.tm_mon,tm.tm_yday,out);
    int a=day_of_year(tm.tm_mon,tm.tm_yday,tm.tm_year+1900);
    system("cls");
    printf(" __________________________________________________\n");
    printf("|                                                  |\n");
    switch((a+FDOY)%7)
    {
        case 0:
            printf("|  %d/%02d/%02d                           saturday   |\n",tm.tm_year+1900,tm.tm_mon,tm.tm_yday);
            break;
        case 1:
            printf("|  %d/%02d/%02d                             sunday   |\n",tm.tm_year+1900,tm.tm_mon,tm.tm_yday);
            break;
        case 2:
            printf("|  %d/%02d/%02d                             monday   |\n",tm.tm_year+1900,tm.tm_mon,tm.tm_yday);
            break;
        case 3:
            printf("|  %d/%02d/%02d                            tuesday   |\n",tm.tm_year+1900,tm.tm_mon,tm.tm_yday);
            break;
        case 4:
            printf("|  %d/%02d/%02d                          wednesday   |\n",tm.tm_year+1900,tm.tm_mon,tm.tm_yday);
            break;
        case 5:
            printf("|  %d/%02d/%02d                           thursday   |\n",tm.tm_year+1900,tm.tm_mon,tm.tm_yday);
            break;
        case 6:
            printf("|  %d/%02d/%02d                             friday   |\n",tm.tm_year+1900,tm.tm_mon,tm.tm_yday);
            break;
    }
    printf("|  %d/%02d/%02d                              TASKS   |\n",out[0],out[1],out[2]);
    printf("|__________________________________________________|\n");
    printf("|                                                  |\n");
    printf("|   %02d:%02d:%02d                                       |\n",tm.tm_hour,tm.tm_min,tm.tm_sec);
    printf("|                                                  |\n");
    printf("|  title                                           |\n");
    printf("| =======                                          |\n");
    printf("|  %-46s  |\n",day[a].task[0]);
    printf("|                                                  |\n");
    printf("|  %-46s  |\n",day[a].task[1]);
    printf("|  %-46s  |\n",day[a].task[2]);
    printf("|  %-46s  |\n",day[a].task[3]);
    printf("|  %-46s  |\n",day[a].task[4]);
    printf("|  %-46s  |\n",day[a].task[5]);
    printf("|  %-46s  |\n",day[a].task[6]);
    printf("|  %-46s  |\n",day[a].task[7]);
    printf("|  %-46s  |\n",day[a].task[8]);
    printf("|  %-46s  |\n",day[a].task[9]);
    printf("|                                                  |\n");
    printf("|                                                  |\n");
    printf("|                                                  |\n");
    printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
    printf("*press d to go back home page  \n");
    printf("*press m to menu  \n");
    printf("*press c to exit  \n");
}
void edit_events(void)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_BLUE);
    long out[3];
    time_t t = time(NULL)+d*86400+86400;
    struct tm tm = *localtime(&t);
    gregorian_to_jalali(tm.tm_year+1900,tm.tm_mon,tm.tm_yday,out);
    int a=day_of_year(tm.tm_mon,tm.tm_yday,tm.tm_year+1900);
    system("cls");
    printf(" __________________________________________________\n");
    printf("|                                                  |\n");
    switch((a+FDOY)%7)
    {
        case 0:
            printf("|  %d/%02d/%02d                           saturday   |\n",tm.tm_year+1900,tm.tm_mon,tm.tm_yday);
            break;
        case 1:
            printf("|  %d/%02d/%02d                             sunday   |\n",tm.tm_year+1900,tm.tm_mon,tm.tm_yday);
            break;
        case 2:
            printf("|  %d/%02d/%02d                             monday   |\n",tm.tm_year+1900,tm.tm_mon,tm.tm_yday);
            break;
        case 3:
            printf("|  %d/%02d/%02d                            tuesday   |\n",tm.tm_year+1900,tm.tm_mon,tm.tm_yday);
            break;
        case 4:
            printf("|  %d/%02d/%02d                          wednesday   |\n",tm.tm_year+1900,tm.tm_mon,tm.tm_yday);
            break;
        case 5:
            printf("|  %d/%02d/%02d                           thursday   |\n",tm.tm_year+1900,tm.tm_mon,tm.tm_yday);
            break;
        case 6:
            printf("|  %d/%02d/%02d                             friday   |\n",tm.tm_year+1900,tm.tm_mon,tm.tm_yday);
            break;
    }
    printf("|  %d/%02d/%02d                         edit event   |\n",out[0],out[1],out[2]);
    printf("|__________________________________________________|\n");
    printf("*press a to add a new event\n");
    printf("*press r to remove an event  \n");
    printf("*press d to go to today  \n");
    printf("*press m to menu  \n");
    printf("*press c to exit  \n");
    char ch=getchar();
    int y=0;
    if (ch=='a')
    {
        FILE *f;
        f=fopen("calendar.txt","w+");
        while(fgetc(f)!=EOF)
        {
            while(fgetc(f)=='^')
            {
                if (fgetc(f)==a)
                {
                    while(fgetc(f)!='$');
                    fseek(f,-1,SEEK_CUR);
                    char txt[100];
                    gets(txt);
                    fprintf(f,"%s\n",txt);
                    y=1;
                    break;
                }
                if (y==1)
                break;
            }
            if (y==1)
            break;
        }
        fclose(f);
    }
}
void edit_tasks(void)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_BLUE);
    long out[3];
    time_t t = time(NULL)+d*86400+86400;
    struct tm tm = *localtime(&t);
    gregorian_to_jalali(tm.tm_year+1900,tm.tm_mon,tm.tm_yday,out);
    int a=day_of_year(tm.tm_mon,tm.tm_yday,tm.tm_year+1900);
    system("cls");
    printf(" __________________________________________________\n");
    printf("|                                                  |\n");
    switch((a+FDOY)%7)
    {
        case 0:
            printf("|  %d/%02d/%02d                           saturday   |\n",tm.tm_year+1900,tm.tm_mon,tm.tm_yday);
            break;
        case 1:
            printf("|  %d/%02d/%02d                             sunday   |\n",tm.tm_year+1900,tm.tm_mon,tm.tm_yday);
            break;
        case 2:
            printf("|  %d/%02d/%02d                             monday   |\n",tm.tm_year+1900,tm.tm_mon,tm.tm_yday);
            break;
        case 3:
            printf("|  %d/%02d/%02d                            tuesday   |\n",tm.tm_year+1900,tm.tm_mon,tm.tm_yday);
            break;
        case 4:
            printf("|  %d/%02d/%02d                          wednesday   |\n",tm.tm_year+1900,tm.tm_mon,tm.tm_yday);
            break;
        case 5:
            printf("|  %d/%02d/%02d                           thursday   |\n",tm.tm_year+1900,tm.tm_mon,tm.tm_yday);
            break;
        case 6:
            printf("|  %d/%02d/%02d                             friday   |\n",tm.tm_year+1900,tm.tm_mon,tm.tm_yday);
            break;
    }
    printf("|  %d/%02d/%02d                         edit tasks   |\n",out[0],out[1],out[2]);
    printf("|__________________________________________________|\n");
    printf("*press a to add a new event\n");
    printf("*press r to remove an event  \n");
    printf("*press d to go to today  \n");
    printf("*press m to menu  \n");
    printf("*press c to exit  \n");
    char ch=getchar();
    int y=0;
    if (ch=='a')
    {
        FILE *f;
        f=fopen("calendar.txt","w+");
        while(fgetc(f)!=EOF)
        {
            while(fgetc(f)=='^')
            {
                if (fgetc(f)==a)
                {
                    while(fgetc(f)!='^');
                    fseek(f,-1,SEEK_CUR);
                    char txt[100];
                    gets(txt);
                    fprintf(f,"%s\n",txt);
                    y=1;
                    break;
                }
                if (y==1)
                break;
            }
            if (y==1)
            break;
        }
        fclose(f);
    }
}

void menu(void)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_BLUE);
    long out[3];
    time_t t = time(NULL)+d*86400+86400;
    struct tm tm = *localtime(&t);
    gregorian_to_jalali(tm.tm_year+1900,tm.tm_mon,tm.tm_yday,out);
    int a=day_of_year(tm.tm_mon,tm.tm_yday,tm.tm_year+1900);

    system("cls");
    printf(" __________________________________________________\n");
    printf("|                                                  |\n");
    switch((a+FDOY)%7)
    {
        case 0:
            printf("|  %d/%02d/%02d                           saturday   |\n",tm.tm_year+1900,tm.tm_mon,tm.tm_yday);
            break;
        case 1:
            printf("|  %d/%02d/%02d                             sunday   |\n",tm.tm_year+1900,tm.tm_mon,tm.tm_yday);
            break;
        case 2:
            printf("|  %d/%02d/%02d                             monday   |\n",tm.tm_year+1900,tm.tm_mon,tm.tm_yday);
            break;
        case 3:
            printf("|  %d/%02d/%02d                            tuesday   |\n",tm.tm_year+1900,tm.tm_mon,tm.tm_yday);
            break;
        case 4:
            printf("|  %d/%02d/%02d                          wednesday   |\n",tm.tm_year+1900,tm.tm_mon,tm.tm_yday);
            break;
        case 5:
            printf("|  %d/%02d/%02d                           thursday   |\n",tm.tm_year+1900,tm.tm_mon,tm.tm_yday);
            break;
        case 6:
            printf("|  %d/%02d/%02d                             friday   |\n",tm.tm_year+1900,tm.tm_mon,tm.tm_yday);
            break;
    }
    printf("|  %d/%02d/%02d                               MENU   |\n",out[0],out[1],out[2]);
    printf("|__________________________________________________|\n");
    printf("|                                                  |\n");
    printf("|   %02d:%02d:%02d                                       |\n",tm.tm_hour,tm.tm_min,tm.tm_sec);
    printf("|                                                  |\n");
    printf("|   *press d to go to today page                   |\n");
    printf("|   *press s to go to search a day                 |\n");
    printf("|   *press c to exit                               |\n");
    printf("|                                                  |\n");
    printf("|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n");
}

void search(void)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_BLUE);
    long out[3];
    time_t t = time(NULL)+d*86400+86400;
    struct tm tm = *localtime(&t);
    gregorian_to_jalali(tm.tm_year+1900,tm.tm_mon,tm.tm_yday,out);
    int a=day_of_year(tm.tm_mon,tm.tm_yday,tm.tm_year+1900);

    system("cls");
    printf(" __________________________________________________\n");
    printf("|                                                  |\n");
    switch((a+FDOY)%7)
    {
        case 0:
            printf("|  %d/%02d/%02d                           saturday   |\n",tm.tm_year+1900,tm.tm_mon,tm.tm_yday);
            break;
        case 1:
            printf("|  %d/%02d/%02d                             sunday   |\n",tm.tm_year+1900,tm.tm_mon,tm.tm_yday);
            break;
        case 2:
            printf("|  %d/%02d/%02d                             monday   |\n",tm.tm_year+1900,tm.tm_mon,tm.tm_yday);
            break;
        case 3:
            printf("|  %d/%02d/%02d                            tuesday   |\n",tm.tm_year+1900,tm.tm_mon,tm.tm_yday);
            break;
        case 4:
            printf("|  %d/%02d/%02d                          wednesday   |\n",tm.tm_year+1900,tm.tm_mon,tm.tm_yday);
            break;
        case 5:
            printf("|  %d/%02d/%02d                           thursday   |\n",tm.tm_year+1900,tm.tm_mon,tm.tm_yday);
            break;
        case 6:
            printf("|  %d/%02d/%02d                             friday   |\n",tm.tm_year+1900,tm.tm_mon,tm.tm_yday);
            break;
    }
    printf("|  %d/%02d/%02d                             SEARCH   |\n",out[0],out[1],out[2]);
    printf("|__________________________________________________|\n");
    printf("*write the day number(day of year)\n");
    scanf("%d",&sd);
    return;
}