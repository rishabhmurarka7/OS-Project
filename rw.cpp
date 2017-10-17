#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <stdbool.h>
#include<queue>
using namespace std;

struct semaphore

{

	int mutex; // main semaphore variable to keep track of no. of processes inside critical section

	int rcount; //to keep count of no. of readers inside critical section

	int rwait;  //to keep count of no. of readers waiting to get entry inside critical section

	bool wrt; //to check if writer is present or not inside critical section

};


static int gw;

struct writer

{
    
    int wid;
    
    string writer_name;
    
};

queue<struct writer> q;

void addReader(struct semaphore *s)
{

	if (s->mutex == 0 && s->rcount == 0) //a writer is already inside critical section

	{

		printf("\nSorry, File open in Write mode.\nNew Reader added to queue.\n");

		s->rwait++;

	}

	else //no writer is present inside critical section. So, reader can be added

	{

		printf("\nReader Process added.\n");

		s->rcount++;

		s->mutex--;

	}

	return ;

}

void addWriter(struct semaphore *s, struct writer w)

{

	if(s->mutex==1)  //no one is inside critical section

	{

		s->mutex--;

		s->wrt=1;

		printf("\nWriter Process added.\n");

	}

	else if(s->wrt)    // a writer is already inside critical section
    
    {
        
        q.push(w);
        
        
        printf("\nWriter%d is blocked\n",w.wid);
        
    }

	else  //a reader is inside critical section
    
    {
        
        q.push(w);
        
		 printf("\nWriter%d is blocked\n",w.wid);
        
    }

	return;

}

void removeReader(struct semaphore *s)

{

	if(s->rcount == 0)  //no reader is inside critical section
		printf("\nNo readers to remove.\n");

	else  // atleast one reader is inside critical section

	{	

		printf("\nReader Removed.\n");

		s->rcount--;

		s->mutex++;

	}
    
    if(s->mutex==1)
    
    {
    
        if(!q.empty())
        
        {
        
            struct writer w1=q.front();
            
            q.pop();
            
            cout << w1.writer_name<<" is up!"<<endl;
            
            s->wrt=1;
           
            s->mutex=0;
        }
        
    }

	return;

}

void removeWriter(struct semaphore *s)

{

	if(s->wrt==0)  // no writer is inside critical section
		
    printf("\nNo Writer to Remove");

	else // atleast one writer is inside critical section

	{

        printf("\ncurrent Writer Removed\n");
        
        if(q.empty())
       
        {

            s->mutex++;

            s->wrt=0;

            if(s->rwait!=0) //condition to give entry to all waiting readers inside critical section as soon as writer exits

            {

                s->mutex-=s->rwait;

                s->rcount=s->rwait;

                s->rwait=0;

                printf("%d Waiting Readers Added.",s->rcount);

            }
            
        }
            
        else
            
        {
            struct writer w1=q.front();
            q.pop();
            cout << w1.writer_name<<" is up!"<<endl;
            
            
        }
        
    }
    
}

int main()

{

	struct semaphore S1={1,0,0};

	while(1)

	{

	printf("Options :-\n1.Add Reader.\n2.Add Writer.\n3.Remove Reader.\n4.Remove Writer.\n5.Exit.\n\n\tChoice : ");

	int ch;

	scanf("%d",&ch);

	switch(ch)

	{

		case 1: addReader(&S1); break;

		case 2:
        {
           
            struct writer w1;
            
            w1.wid = ++gw;
            
            w1.writer_name = "writer_" + to_string(gw);
            
            addWriter(&S1, w1); break;
        }
		case 3: removeReader(&S1); break;

		case 4: removeWriter(&S1); break;

		case 5: printf("\n\tGoodBye!"); 
				
                getchar();
		 	
                return 0;

		default: printf("\nInvalid Entry!"); 
		
                continue;

	}

	printf("\n\n<<<<<< Current Status >>>>>>\n\n\tMutex\t\t:\t%d\n\tActive Readers\t:\t%d\n\tWaiting Readers\t:\t%d\n\tWriter Active\t:\t%s\n\n", S1.mutex, S1.rcount, S1.rwait, (S1.mutex==0 && S1.rcount==0) ? "YES" : "NO");

	}

}
