#include "myshell.h"

int count =  0;
char *cmdlist[10] = {"","","","","","","","","",""};

char *_strdup(char *s)
{
	char *p;
	p = (char *)malloc(strlen(s)+1);
	if(p != NULL)
	{
		strcpy(p,s);
	}
	return p;
}

int compareString(char *a, char *b)
{
    if(strncmp(a,b,strlen(a)) == 0)
    {
	    return 0;
    }
    else
    {
	    return 1;
    }

}


int getTokenNum(char *tmp, char *token[])
{
    char *tok;
    int cnt = 0;
    tok = strtok(tmp," ");

    while(tok != NULL)
    {
	 token[cnt] = tok;
	 cnt++;
	 tok = strtok(NULL," ");
    }

    token[cnt] = NULL;
    return cnt;
}



void background(char *token[])
{
   

     pid_t pid = fork();

   if(pid == 0)
   {
      if(compareString(token[0],"help") == 0 || compareString(token[0],"history") == 0)
      {
         innerCmd(token);
         exit(0);	 
      }
      else
      {      
         execvp(token[0],token);
         exit(0);
      }
   }

}

void innerCmd(char *token[])
{
   if(compareString(token[0],"help") == 0)
   {
        printf("DESCRIPTION\n");
	printf("           myshell은 간단한 기능을 구현하는 shell 로써 오퍼레이팅 시스템 과제를 위해 제작되었습니다.\n\n");
	printf("COMMANDS\n");
	printf("        quit\n");
	printf("            shell을 종료합니다.\n");
	printf("        history\n");
	printf("               최근 입력된 10개의 명령어를 출력합니다.\n");
	printf("        help\n");
	printf("            메뉴얼을 출력합니다.\n");
	printf("        [command] &\n");
	printf("                   명령어 끝에 & 입력시 백그라운드로 실행합니다.\n\n");
	printf("AUTHORS\n");
	printf("       12171597 김영기\n");
   }
   else if(compareString(token[0],"history") == 0)
   {
        for(int i = 0; i < 10; i++)
	{
		if(cmdlist[i] == "")
		{
			break;
		}
		else
		{
			printf("%s\n",cmdlist[i]);
		}
	}
   }
}

bool doCmd(char *cmd)
{
   int tokenNum = 0;
   int i = 0;
   char * token[128];
   pid_t pid;
   int flag = 0;

   tokenNum = getTokenNum(cmd,token);

   
   
       if(strcmp(token[tokenNum-1],"&") == 0)
       {
	    token[tokenNum-1] = NULL;
	    flag++;
	    background(token);
       }

      
  if(flag == 0)
  {
      if(compareString(token[0],"help") == 0 || compareString(token[0],"history") == 0)
      {
	  innerCmd(token);
	  wait(NULL);
      }
      else
      {

      
      
         pid = fork();

         if(pid == 0)
         {
		if(compareString(token[0],"help") == 0 || compareString(token[0],"history") == 0)
		{
			innerCmd(token);
			exit(0);
			wait(NULL);
		}
		else
		{
		
	       	 execvp(token[0],token);
		  exit(0);
		}
         }
         else if(pid < 0)
         {
		  perror("fork error\n");
		  return -1;
         }
         else
         {
	 	 wait(NULL);
      	 }

     	 	 wait(NULL);
      
      }
   }
}


int main(int argc, char *argv[])
{
	    char input[128];
	    pid_t pid;
	    
	    

         while(1)
	 {        
		  

		  printf("12171597_shell$ ");
		  memset(input,0,sizeof(input));
		  fgets(input,sizeof(input)-1,stdin);
                  input[strlen(input)-1] = '\0';	          

		  if(count ==  10)
		  {
	              for(int i = 1; i < 10; i++)
		      {
			  cmdlist[i-1] = _strdup(cmdlist[i]);
		      }
		      cmdlist[9] = _strdup(input);
		  }
		  else
		  {
	  	      cmdlist[count] = _strdup(input);
		      count++;
		  }
						            
	         

		  if(strncmp(input, "quit", strlen(input)) == 0) 
		  {
			  printf("myshell developed by 김영기(12171597)\n");
											           
			  return -1;
		  }
		  
			

		  doCmd(input);

		 
	 }


}



