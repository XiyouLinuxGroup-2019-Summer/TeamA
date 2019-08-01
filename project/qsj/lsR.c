#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/limits.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <errno.h>

#define PARAM_NONE 0  
#define PARAM_A    1  
#define PARAM_L    2  
#define PARAM_R    4  
#define MAXROWLEN  80 
 
int g_leave_len = MAXROWLEN;  
int g_maxlen;                 

typedef struct nam{
    char name[PATH_MAX];
    struct nam *next;
}file;

void my_err(const char *err_string, int line);
void display(int flag, file *p);
void display_attribute(struct stat buf, char *name);
void display_single(struct stat buf, char *name);
void display_dir(int flag_param, file *p);
int setc(struct stat buf, char *name);
int canc();
void fre ( file *head );
void add ( file **head, char path[PATH_MAX] );


int main(int argc , char ** argv)
{
    int i,j,k,num;
    char path[PATH_MAX];
    char param[32];       
    int  flag_param = PARAM_NONE ;
    struct stat buf;
    file *head = NULL;

    j = 0;
    num = 0;
    for( i = 1; i < argc; i++ ) {
        if( argv[i][0] == '-' ) {
            for( k=1; k < strlen(argv[i]); k++,j++ )
                param[j]=argv[i][k]; 
            num++;
        }
    }
 
    for( i=0; i<j; i++ )
    {
        if( param[i] == 'a' ){
            flag_param |= PARAM_A;
            continue;
        }else if( param[i] == 'l' ){
            flag_param |= PARAM_L;
            continue;
        }else if( param[i]=='R' ){
            flag_param |= PARAM_R;
            continue;
		}else{
            printf("error:invalid option -%c\n", param[i]);
            exit(1);
        }
    }
    param[j] = '\0';
 
    if( (num+1) == argc ){
        strcpy(path,"./");
        path[2]='\0';
        add(&head, path);
        display_dir(flag_param,head);
        return 0;
    }
 
    i = 1;
    do {

        if( argv[i][0] == '-' ){
            i++;
            continue;
        }
        else{
            strcpy(path,argv[i]);
        
        if( stat(path,&buf)== -1 )
            my_err("stat",__LINE__);
 
        if( S_ISDIR(buf.st_mode) ) 
        {
            if( path[strlen(argv[i])-1] != '/' ){
                path[strlen(argv[i])] = '/';
                path[strlen(argv[i])+1] = '\0';
            }
            else
                path[ strlen(argv[i]) ] = '\0';
            
            add(&head, path);
            display_dir(flag_param,head);
            i++;
        }
        else {
            add(&head, path);
            display(flag_param,head);
            i++;
        }
        }
    }while ( i < argc );

    free(head);
    return 0;
}

int setc(struct stat buf, char *name)
{
    if ( S_ISDIR(buf.st_mode) )
        return printf("\033[36m%-s\033[0m", name);
    if ( S_ISLNK(buf.st_mode) )
        return printf("\033[33;35m%-s\033[0m", name);
    if ( (buf.st_mode & S_IXUSR) || (buf.st_mode & S_IXOTH) || (buf.st_mode & S_IXGRP) )
        return printf("\033[32m%-s\033[0m", name);
    return printf("\033[0m%-s\033[0m", name);
}

int canc()
{
    return printf("\033[0m");
}

void my_err(const char *err_string, int line)
{
    fprintf(stderr,"line:%d ",line);
	perror(err_string);
	exit(1);
}
 
void display_attribute(struct stat buf, char *name)
{
    char   buf_time[32];
  	struct passwd *psd; 
	struct group  *grp;

    if( S_ISLNK(buf.st_mode) ) 
        printf("l");
    else if( S_ISREG(buf.st_mode) )
        printf("-");
    else if( S_ISDIR(buf.st_mode) )
        printf("d");
    else if( S_ISCHR(buf.st_mode) )
        printf("c");
    else if( S_ISBLK(buf.st_mode ) )
        printf("b");
    else if( S_ISFIFO(buf.st_mode) )
        printf("f");
    else if( S_ISSOCK(buf.st_mode) )
        printf("s");
    
    
    if( buf.st_mode&S_IRUSR )
        printf("r");
    else
        printf("-");
    if( buf.st_mode&S_IWUSR )
        printf("w");
    else
        printf("-");
    if( buf.st_mode&S_IXUSR )
        printf("x");
    else
        printf("-");

    
    if( buf.st_mode&S_IRGRP )
        printf("r");
    else
        printf("-");
    if( buf.st_mode&S_IWGRP )
        printf("w");
    else
        printf("-");
    if( buf.st_mode&S_IXGRP )
        printf("x");
    else
        printf("-");

    
    if( buf.st_mode&S_IROTH )
        printf("r");
    else
        printf("-");
    if( buf.st_mode&S_IWOTH )
        printf("w");
    else
        printf("-");
    if( buf.st_mode&S_IXOTH )
        printf("x");
    else
        printf("-");

    printf("  ");    
	psd = getpwuid(buf.st_uid);
	grp = getgrgid(buf.st_gid);
    printf("%4ld ", buf.st_nlink);
    printf("%-8s%-8s%6ld", psd->pw_name, grp->gr_name, buf.st_size);
    
    strcpy(buf_time,ctime(&buf.st_mtime));
	buf_time[strlen(buf_time)-1] = '\0';
    printf(" %s ", buf_time);
    setc(buf, name);
    canc();
    printf("\n");
}

void display_dir(int flag_param, file *p)
{
    DIR *dir;
    struct dirent *ptr;
    struct stat buf;
    int count = 0, i, j, len = strlen(p->name);
    char nam[PATH_MAX+1], name[PATH_MAX+1], filename[PATH_MAX];
    file temp;
    file *q = p, *r, *m, *n;
    r = m = n = NULL;

    dir = opendir(q->name);
    if ( dir == NULL )        
        my_err("opendir", __LINE__);
    
    g_maxlen = 0; 
    while ( (ptr = readdir(dir)) != NULL ) {
        if ( g_maxlen < strlen(ptr->d_name) )
            g_maxlen = strlen(ptr->d_name);
        count++;
    }
    closedir(dir);

//    char (*file)[PATH_MAX+1]=(char(*)[PATH_MAX+1])malloc(sizeof(char)*count*(PATH_MAX+1));    

    dir = opendir(q->name);
    for ( i = 0; i < count; i++ ) {
        ptr = readdir(dir);
        if ( ptr == NULL ) 
            my_err("readdir", __LINE__);
        strncpy( filename, q->name, len );
        filename[len] = '\0';
        strcat(filename, ptr->d_name);
        filename[len+strlen(ptr->d_name)] = '\0';
        add(&q, filename);
    }

   
    if ( (flag_param & PARAM_R) != 0 )
        printf("%s:\n", p->name);
    
/*    q = p->next;
    while ( q != r ) {
        while ( q->next != r ) {
            if ( strcmp(q->name, q->next->name) > 0 ) {
                m = q->next;
                temp = *q;
                *q = *m;
                *m = temp;
                n = q->next;
                q->next = m->next;
                m->next = n;
            }
            q = q->next;
        }
        r = q;
        q = p->next;
    }
*/
    q = p->next;
    while ( q ) {
        display(flag_param, q);
        q = q->next;
    }

    closedir(dir);

    if ( (flag_param & PARAM_L) == 0 )
        printf("\n");

    if ( (flag_param & PARAM_R) != 0 ) {
        q = p->next;
        while ( q ) {
            strcpy(name,q->name);
            strcpy(nam, q->name+len);
            j = strlen(name);
        
            if ( !(strcmp(nam, ".")) || !(strcmp(nam, "..")) )
                continue;

            if ( (flag_param & PARAM_A) == 0 ) {
                if ( nam[0] == '.' )
                    continue;
            }


            if ( lstat(name, &buf) == -1 ) {
                if ( errno == 13 ) {
                    printf("没有权限访问\n");  
                    return;     //没有权限访问
                }
                my_err("stat", __LINE__);
            }

            if ( S_ISDIR(buf.st_mode) ) {
                name[j] = '/';
                name[j+1] = '\0';
                strcpy(q->name, name);
                display_dir(flag_param, q);
            }
            q = q->next;
        }
    }

    fre(p);
}


void display_single(struct stat buf, char *name)
{
    int i, len;
	
    if( g_leave_len < g_maxlen ){
	    printf("\n");
		g_leave_len = MAXROWLEN;
	}
 
	len = strlen(name);
    len = g_maxlen -len;
    setc(buf, name);
    canc();

    for( i=0; i<len; i++ ){
	    printf(" ");
	}
	printf(" ");
	
    g_leave_len -= (g_maxlen + 2);
}

void display(int flag, file *p)
{
    int i, j;
    struct stat buf;
    char name[NAME_MAX+1], pathname[PATH_MAX+1];

    strcpy(pathname, p->name);

    for ( i = 0, j = 0; i < strlen(pathname); i++ ) {
        if ( pathname[i] == '/' ) {
            j = 0;
            continue;
        }
        name[j++] = pathname[i];
    }
    name[j] = '\0';

    if ( lstat(pathname, &buf) == -1 ) {
        my_err("stat", __LINE__);
    }


    switch(flag) {
    case PARAM_NONE :
    case PARAM_R :
        if ( name[0] != '.' )
            display_single(buf, name);
        break;
    case PARAM_A :
    case PARAM_A + PARAM_R :
        display_single(buf, name);
        break;
    case PARAM_L :
    case PARAM_L + PARAM_R :
        if ( name[0] != '.' )
            display_attribute(buf, name);
        break;
    case PARAM_A + PARAM_L :
    case PARAM_A + PARAM_L + PARAM_R:
        display_attribute(buf, name);
    default:
        break;
    }
}

void add ( file **head, char path[PATH_MAX] )
{
    file *p = (file*)malloc(sizeof(file));
    file *last = *head;

    strcpy(p->name, path);
    p->next = NULL;

    if ( last ) {
        while ( last->next ) {
            last = last->next;
        }
        last->next = p;
    }

    else {
        *head = p;
    }
}
void fre ( file *head )
{
    file *p = head, *q;
    
    while ( p ) {
        q = p;
        p = p->next;
        free(q);
    }
}
