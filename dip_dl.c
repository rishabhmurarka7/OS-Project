#include<stdio.h>
#include<unistd.h> 
#define n 9
 
int all_phil = 0;
static int c=0;

struct fork
{
    int taken;
}ForkAvil[n];
 
struct philosp
{
    int left;
    int right;
}Philostatus[n];


//philosopher is checking for forks
void phil_hungry(int philID)
 {
  /* if(philID==(n-1))
     {
        if(ForkAvil[philID-1].taken==0)
          { 
            ForkAvil[philID-1].taken = Philostatus[philID].left = 1;
             printf("Fork %d taken by philosopher %d\n",philID,philID+1);
          }
         else
           printf("Philosopher %d is waiting for fork %d\n",philID+1,philID);
      }
    else
      { */
      
       if(ForkAvil[philID].taken == 0)
         {
           ForkAvil[philID].taken = Philostatus[philID].left = 1;
           printf("Fork %d taken by Philosopher %d\n",philID+1,philID+1);
         }
       else
         printf("Philosopher %d is waiting for Fork %d\n",philID+1,philID+1);
         
     //}
 }


 //philosopher has aquiried both the forks
 void phil_left_fork(int philID)
  {
    /* if(philID==(n-1))
      {
       if(ForkAvil[philID].taken==0)
         { 
           ForkAvil[philID].taken = Philostatus[philID].right = 1;
           printf("Fork %d taken by philosopher %d\n",philID+1,philID+1);
         }
         else
             printf("Philosopher %d is waiting for fork %d\n",philID+1,philID+1);
       }
      else
       { */
        int dupphilID = philID;
         philID-=1;
 
        if(philID== -1)
        philID=(n-1);
      
        if(ForkAvil[philID].taken == 0)
          {
            ForkAvil[philID].taken = Philostatus[dupphilID].right = 1;
             printf("Fork %d taken by Philosopher %d\n",philID+1,dupphilID+1);
          }
        else
         printf("Philosopher %d is waiting for Fork %d\n",dupphilID+1,philID+1);
         
      // }
       
   }
   
   //philosopher has finished eating 
 void phil_eating(int philID)
    {
            printf("Philosopher %d completed his dinner\n",philID+1);
 
            Philostatus[philID].left = Philostatus[philID].right = 10; 
            int otherFork = philID-1;
 
            if(otherFork== -1)
                otherFork=(n-1);
 
            ForkAvil[philID].taken = ForkAvil[otherFork].taken = 0;
            printf("Philosopher %d released fork %d and fork %d\n",philID+1,philID+1,otherFork+1);
            all_phil++;
    }

void have_noodle(int philID)
{ 
    c++;

    if(Philostatus[philID].left==10 && Philostatus[philID].right==10)   // philosopher is full
        printf("Philosopher %d completed his dinner\n",philID+1);
    
    else if(Philostatus[philID].left==1 && Philostatus[philID].right==1)  //philosopher is eating
            phil_eating(philID);
            
    else if(Philostatus[philID].left==1 && Philostatus[philID].right==0)   //philosopher is aquiring fork
            phil_left_fork(philID);
            
    else if(Philostatus[philID].left==0)                                   // philosopher is hungry
       phil_hungry(philID);
    else
       printf("philosopher are busy\n");
}
 
int main()
{
 int i=0;
 while(i<n)
  { ForkAvil[i].taken=0;
    Philostatus[i].left=0;
    Philostatus[i].right=0;
    i++;
  } 
    while(all_phil<n)
    {
        for(i=0;i<n;i++)
            have_noodle(i);
        printf("\nTill now num of philosophers completed dinner are %d\n\n",all_phil);

          printf("\nDeadlock!!\n");
          sleep(5);

    }
    
   printf("\nTime complexity: n^2 + 3*n  :\t %d\n",c);
 
    return 0;
}
