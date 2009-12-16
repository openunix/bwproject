/* 
 * Copyright (c) 2009 Tianjin Zhongke Blue Whale 
 *               Information Technologies Co., Ltd
 * 
 * main.c - This file run some rbtree test cases
 * 
 * 
 * 
 * Dependencies:
 * bwoss_iface.h
 * mynode.h
 * ChangeLog: 2009-12-2 Initial Created
 * 
 * ToDo:
 *  None
 */

 /* 
  * Copyright (c) 2009 Institute of Computing Technology,
  *                    Chinese Academy of Sciences
  * 
  * Author:  
  */
#include "..\..\..\bwoss\bwoss_iface.h"

#include "mynode.h"

/* thread functions*/
#define NUMBER 50*128

struct threadpara
{
    bwlib_rb_root_t* root;
	int            start;
}; 

void insert_50k_nodes(void* tp)
{
   
	struct nodetype  *testnode;
    int i ;
	bwoss_lock_write();
	for(i = ((struct threadpara*)tp)->start; i < ((struct threadpara*)tp)->start + NUMBER; i++)
	{
	    testnode = (struct nodetype*)bwoss_malloc(sizeof(struct nodetype));
		testnode->key = i;
		bwosl_node_insert(((struct threadpara*)tp)->root,testnode);
		//printf("insert node %d\n.", i);	
	}
	
	printf("thread funtion insert nodes from  %d exit\n",((struct threadpara*)tp)->start);
	bwoss_unlock_write();	
}


int search_250k_nodes(void* lp)
{   
	int i;
	bwoss_lock_read();
	printf("go in search 250K function\n");
    for(i= 0; i < 5*NUMBER; i++)
	{
		if(!bwosl_node_search((bwlib_rb_root_t*)lp, i))
		{
            printf("go out search 250 k function loss nodes\n"); 
			bwoss_unlock_read();
			return 0;
		}
	}
    printf("go out search 250K function\n");
    bwoss_unlock_read();
	return 1;
}

int search_50k_nodes(void* lp)
{   
	
	int i;
	bwoss_unlock_read();
	printf("go in search 50 k function\n");
    for(i= 0; i < NUMBER; i++)
	{
		if(!bwosl_node_search((bwlib_rb_root_t*)lp, i))
		{
			printf("go out search 50 k function lost nodes\n");
			bwoss_unlock_read();
			return 0;
		}
	}

	printf("go out search 50 k function\n");
    bwoss_unlock_read();
	
	return 1;
}

int delete_50k_nodes(void* lp)
{
	
	int i;
	bwoss_lock_write();
	printf("go in delete 50 k function\n");
    for(i= 0; i < NUMBER; i++)
	{
		if(!bwosl_node_delete((bwlib_rb_root_t*)lp, i))
		{
			printf("go out delete 50 k function\n");
			unlock_write();
			return 0;
		}
	}
	printf("go out delete 50 k function\n");
    bwoss_unlock_write();	
	return 1;
}

void main()
{
    
/* test1*/
 /*  bwlib_rb_root_t root;
	
	HANDLE hThread[7];
	DWORD  ThreadID[7];
    struct threadpara tp[5];
	int i;
	unsigned long  Code;

	bwlib_rb_init(&root);

	bwoss_initialize_lock();
	for(i=0; i < 5; i++ )
	{
		tp[i].root =&root;
		tp[i].start = i * NUMBER;
		hThread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)insert_50k_nodes, &(tp[i]), 0, &(ThreadID[i]));
	}
	//Sleep(100);
   
	WaitForMultipleObjects(5,hThread,TRUE,INFINITE);


	//Sleep(100);
	 
     hThread[5]=CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE )delete_50k_nodes, &root, 0, &(ThreadID[6]));
	  WaitForSingleObject(hThread[5],INFINITE);
	// WaitForMultipleObjects(6,hThread,TRUE,INFINITE);
	 hThread[6]=CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)search_250k_nodes, &root, 0, &(ThreadID[5]));
//	 
//    WaitForSingleObject(hThread[6],INFINITE);
	WaitForMultipleObjects(7,hThread,TRUE,INFINITE);
	GetExitCodeThread(hThread[6], &Code);
	if(Code == 1)
        printf("Find all the nodes %d\n",Code);
	else
        printf("can not find all the nodes\n");
	for(i=0; i<7; i++)
		CloseHandle(hThread[i]);

      bwoss_clean_lock();
*/
/////////////////////////////////////////////////////////////////////////
    #define DF 1024*1024
    bwlib_rb_root_t root;
	struct nodetype* testnode;

	unsigned long  i=0, j=0;
	unsigned long  n =64;

	LARGE_INTEGER BegainTime;       // variables for time
	LARGE_INTEGER  EndTime ; 
	LARGE_INTEGER Frequency ;
    double durtime[3][8];
	root.rb_node = NULL;


    

   QueryPerformanceFrequency(&Frequency);  
	QueryPerformanceCounter(&BegainTime) ;
	for(i = 0 ; i < n * DF; i++)
	{
		testnode = (struct nodetype*)bwoss_malloc(sizeof(struct nodetype));
		testnode->key = i;
		bwosl_node_insert(&root,testnode);      
	}
	
	QueryPerformanceCounter(&EndTime) ;
	
	durtime[0][0] = (double)(EndTime.QuadPart - BegainTime.QuadPart)/Frequency.QuadPart;
	
	 QueryPerformanceFrequency(&Frequency);
	QueryPerformanceCounter(&BegainTime) ;
	
	for(i = 0; i < n * DF; i++)
	{
		bwosl_node_search(&root, i);  
	}
	QueryPerformanceCounter(&EndTime) ;
	durtime[1][0] = (double)(EndTime.QuadPart - BegainTime.QuadPart)/Frequency.QuadPart;

	QueryPerformanceFrequency(&Frequency);  
	QueryPerformanceCounter(&BegainTime) ;
	
	for(i = 0; i < n * DF; i++)
	{
		bwosl_node_delete(&root, i);      
	}
	
	QueryPerformanceCounter(&EndTime) ;
		   durtime[2][0] = (double)(EndTime.QuadPart - BegainTime.QuadPart)/Frequency.QuadPart;
		   printf("insert , delete , search  %10d  K nodes, cost time(s), %f , %f ,%f\n", n, durtime[0][0],durtime[1][0],durtime[2][0]);

  /*	QueryPerformanceCounter(&BegainTime) ;
	
	for(i = 0 ; i < 256 * DF; i++)
	{
		testnode = (struct nodetype*)bwoss_malloc(sizeof(struct nodetype));
		testnode->key = i;
		bwosl_node_insert(&root,testnode);      
	}
	
	

	QueryPerformanceCounter(&EndTime) ;

   
	durtime[0][0] = (double)(EndTime.QuadPart - BegainTime.QuadPart)/(double)Frequency.QuadPart;
    printf("%lf",durtime[0][0]);

*/
  
  /*
	for (j = 0; j <9; j++)
	{
           QueryPerformanceFrequency(&Frequency[0]);  
		   QueryPerformanceCounter(&BegainTime[0]) ;

		   for(i = 0 ; i < n * DF; i++)
		   {
			   testnode = (struct nodetype*)bwoss_malloc(sizeof(struct nodetype));
			   testnode->key = i;
		        bwosl_node_insert(&root,testnode);      
		   }

		   QueryPerformanceCounter(&EndTime[0]) ;

		   durtime[0][j] = (double)(EndTime[0].QuadPart - BegainTime[0].QuadPart)/Frequency[0].QuadPart;

		  QueryPerformanceFrequency(&Frequency[1]);
		   QueryPerformanceCounter(&BegainTime[1]) ;

		   for(i = 0; i < n * DF; i++)
		   {
			  bwosl_node_search(&root, i);  
		   }
		   QueryPerformanceCounter(&EndTime[1]) ;
		   durtime[1][j] = (double)(EndTime[1].QuadPart - BegainTime[1].QuadPart)/Frequency[1].QuadPart;
           
		   QueryPerformanceFrequency(&Frequency[2]);  
		   QueryPerformanceCounter(&BegainTime[2]) ;

		   for(i = 0; i < n * DF; i++)
		   {
			   bwosl_node_delete(&root, i);      
		   }

		   QueryPerformanceCounter(&EndTime[2]) ;
		   durtime[2][j] = (double)(EndTime[2].QuadPart - BegainTime[2].QuadPart)/Frequency[2].QuadPart;

		   n = n* 2;
	}
 
     n = 1; 
   for (i = 0 ;i < j ; i ++)
   {
	   printf("insert , delete , search  %10d  K nodes, cost time(s), %lf , %lf ,%lf\n", n, durtime[0][i],durtime[1][i],durtime[2][i]);
        n  = n * 2;
   }
  */
//////////////////////////////////////////////////////////////////////////////////////////////
//	printf("%x  %x  %x",&testnode,&(testnode.node), container_of((&testnode), struct nodetype, node));
   
/*  struct rb_root root;
	root.rb_node = NULL;
	struct nodetype* testnode;
   int i;
   for( i = 0; i < NUMBER1 ; i++)
	{
        testnode = (struct nodetype*)malloc(sizeof(struct nodetype));
		testnode->key = i;
		node_insert(&root,testnode);
	}
  for(i= 0 ; i< NUMBER1; i++)
	{
	if(node_search(&root, i))
	    printf("find the key %d\n",i);
	else 
		printf("can't find key %d\n",i);
	}

 	for(i= 0 ; i< NUMBER1; i++)
	{
		if(node_delete(&root, i))
			printf("delete the key %d\n",i);
		else 
			printf("can't delete key %d\n",i);
	}

	for(i= 0 ; i< NUMBER1; i=i*10+1)
	{
		if(node_search(&root, i))
			printf("find the key %d\n",i);
		else 
			printf("can't find key %d\n",i);
	}

	
    */
}