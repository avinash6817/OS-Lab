#include<iostream>
#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

using namespace std;

pthread_t employee;	//Initialize Pthread for employee.
pthread_t hacker;	//Initialize Pthread for hacker.
pthread_mutex_t lock;	//Initialize pthread lock.
pthread_cond_t cond_hck;	//Initialize pthread condition variable for employee.
pthread_cond_t cond_emp;	//Initialize pthread condition variable for hacker.
sem_t emp;		//Declare Semaphore for Employee.
sem_t hck;		//Declare Semaphore for hacker.

int count=0;		//Count No of Boat rides.

int empcount,hckcount;	//Variables to fetch values of semaphore.

void *wind_emp(void *);
void *hackr(void *);

void boatride()
{
   cout<<"Boat ride "<<count++<<endl;	//Print the no of Rides.
}
int main()
{
   sem_init(&emp,0,0);		//Initialize Employee semaphore with 0.
   sem_init(&hck,0,0);		//Initialize hacker semaphore with 0.

   for(int k=0;k<20;k++){	//Call Employee thread 20 times.
      if(pthread_create(&employee,NULL,wind_emp,NULL))
         cout<<"Error while creating Employee thread"<<endl;
   }
   for(int k=0;k<20;k++){	//Call Hacker thread 20 times.
      if(pthread_create(&hacker,NULL,hackr,NULL))
         cout<<"Error while creating Hacker thread"<<endl;
   }
   pthread_join(employee,NULL);  //join Employee thread.
   pthread_join(hacker,NULL);  //join Hacker thread.
   return 0;
}

void *wind_emp(void *i)
{
   pthread_mutex_lock(&lock);
   sem_post(&emp);		//Increment semaphore count of employee.
   if(sem_getvalue(&emp,&empcount))
      cout<<"Error while fetching semaphoe value of employee"<<endl;
   if(sem_getvalue(&hck,&hckcount))
      cout<<"Error while fetching semaphoe value of hacker"<<endl;
   if(empcount>=2 && hckcount >=2)
   {
      sem_wait(&emp);		//Decrement Employee count by 2.
      sem_wait(&emp);
      sem_wait(&hck);		//Decrement Hacker count by 2.
      sem_wait(&hck);
      pthread_cond_signal(&cond_emp);  //Wake up 2 Employee.
      pthread_cond_signal(&cond_emp);
      pthread_cond_signal(&cond_hck);  //Wake up 2 Hacker.
      pthread_cond_signal(&cond_hck);
      boatride();			//Ride a boat.
   }
   else if(empcount==4)
   {
      boatride();
      sem_wait(&emp);
      sem_wait(&emp);
      sem_wait(&emp);
      sem_wait(&emp);
      pthread_cond_signal(&cond_emp);
      pthread_cond_signal(&cond_emp);
      pthread_cond_signal(&cond_emp);
      pthread_cond_signal(&cond_emp);
   }
   else
   {
      pthread_cond_wait(&cond_emp,&lock);
   }
   pthread_mutex_unlock(&lock);
   pthread_exit(0);
}

void *hackr(void *i)
{
   pthread_mutex_lock(&lock);
   sem_post(&hck);		//Increment semaphore count of employee.
   if(sem_getvalue(&emp,&empcount))
      cout<<"Error while fetching semaphoe value of employee"<<endl;
   if(sem_getvalue(&hck,&hckcount))
      cout<<"Error while fetching semaphoe value of hacker"<<endl;
   if(empcount>=2 && hckcount >=2)
   {
      boatride();
      sem_wait(&emp);
      sem_wait(&emp);
      sem_wait(&hck);
      sem_wait(&hck);
      pthread_cond_signal(&cond_emp);  //Wake up 2 Employee.
      pthread_cond_signal(&cond_emp);
      pthread_cond_signal(&cond_hck);  //Wake up 2 Hacker.
      pthread_cond_signal(&cond_hck);
   }
   else if(hckcount==4)
   {
      boatride();
      sem_wait(&hck);
      sem_wait(&hck);
      sem_wait(&hck);
      sem_wait(&hck);
      pthread_cond_signal(&cond_hck);  //Wake up 2 Hacker.
      pthread_cond_signal(&cond_hck);  //Wake up 2 Hacker.
      pthread_cond_signal(&cond_hck);
      pthread_cond_signal(&cond_hck);
   }
   else
   {
      pthread_cond_wait(&cond_hck,&lock);
   }
   pthread_mutex_unlock(&lock);
   pthread_exit(0);
}