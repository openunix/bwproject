#include <stdlib.h>
#include <stdio.h>
#include "radix-tree.h"
#include <time.h>
#include <windows.h>
#include "osdep.h"

#define NUM 50 * 1024

typedef struct radix_tree_item
{
	uint32_t index; 
}radix_tree_item;

typedef struct Para
{
	radix_tree_root* root;
	uint32_t start;
}Para;

void insert_50k_nodes(void* tp)
{
	/*lock_write();*/
	uint32_t i = 0 ;
	for(i = ((Para *)tp)->start; i < ((Para *)tp)->start + NUM; ++i)
	{
		struct radix_tree_item* leaf = (radix_tree_item*)malloc(sizeof(radix_tree_item));
		leaf->index = i;
		if(1 == bwlib_radix_tree_insert(((Para *)tp)->root,i,(void*)leaf))
		{
			printf("index为%d时，insert函数发生错误\n",i);
			unlock_write();
			ExitThread(-1);
		}
	}

	unlock_write();	
	printf("thread that adds Nodes indexed from %d to %d has been exit!\n",((Para *)tp)->start, ((Para *)tp)->start + NUM -1);
}


uint32_t search_250k_nodes(void* lp)
{   
	/*lock_read();*/

	uint32_t i = 0;

    for( i = ((Para *)lp)->start; i < ((Para *)lp)->start + 5 * NUM; ++i)
	{
		radix_tree_item *leaf1 = (radix_tree_item*)bwlib_radix_tree_lookup(((Para *)lp)->root,i);
		if(leaf1)
			;//printf("index为%d\n",leaf1->index);
		else
		{
			printf("查找的节点不存在！\n");
			unlock_read();
			ExitThread(-1);
		}
	}

    unlock_read();
	return 1;
}


uint32_t main()
{
	uint32_t j = 0 , i =0;
	HANDLE hThread[6];
	DWORD  threadID[6];
	Para para[6];
	DWORD Code;
	clock_t start, after_tree_creates, after_lookups, after_deletes;
	uint32_t node_count[8] = {        1024, 
									 	 4*1024,
									    64*1024,
									   256*1024, 
									  1024*1024,
								    4*1024*1024,
								   64*1024*1024,
								  256*1024*1024};

	struct radix_tree_root* root = NULL;
	root =(radix_tree_root*) malloc(sizeof(radix_tree_root));
	bwlib_radix_tree_init(root);
	printf("Performance test:\n");
	for(j = 0; j < 6; ++j)
	{
		start = clock();
		//test bwlib_radix_tree_insert
		for(i = 0 ; i < node_count[j]; i++)
		{
			struct radix_tree_item* leaf = (radix_tree_item*)malloc(sizeof(radix_tree_item));
			leaf->index = i;
			if(1 == bwlib_radix_tree_insert(root,i,(void*)leaf))
			{
				//printf("index为%d时，insert funcion error\n",i);

				system("pause");
				return -1;
			}
		}
		after_tree_creates = clock();
		//test bwlib_radix_tree_lookup
		for(i = 0; i < node_count[j]; ++i)
		{
			radix_tree_item *leaf1 = (radix_tree_item*)bwlib_radix_tree_lookup(root,i);
			if(leaf1)
				;//printf("index为%d\n",leaf1->index);
			else
			{
				printf("the node does not exist!\n");
			}
		}
		after_lookups = clock();
		//test bwlib_radix_tree_delete
		for(i = 0; i < node_count[j]; ++i)
		{
			radix_tree_node* node = (radix_tree_node*)bwlib_radix_tree_delete(root,i);
			radix_tree_item *leaf2 = (radix_tree_item*)bwlib_radix_tree_lookup(root,i);
			if(leaf2)
				printf("index为%d\n",leaf2->index);
			else
			{
			//	printf("the node does not exist!\n");
			}
		}
		after_deletes = clock();

		printf("Test case : Nodes Total\t%u\n	Time consumed for tree creation: %f\n	Time consumed for lookups: %f\n	Time consumed for deletes: %f\n", node_count[j], (double)(after_tree_creates - start)/CLOCKS_PER_SEC, (double)(after_lookups - after_tree_creates)/CLOCKS_PER_SEC, (double)(after_deletes - after_lookups)/CLOCKS_PER_SEC);
	}//for loop ends
	
	//to create six threads to manipulate the tree in parallel 
	//using the header file: osdep.cpp for the compatibility and convinience.

	
	initialize_var();

	
	for(i = 0; i < 5; i++ )
	{
		para[i].root  = root;
		para[i].start = i * NUM + 1;
		hThread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)insert_50k_nodes, &(para[i]), 0, &(threadID[i]));
	}
   
	para[5].root = root;
	para[5].start = 1;
    hThread[5]=CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)search_250k_nodes, &(para[5]), 0, &(threadID[5]));

	WaitForMultipleObjects(6,hThread,TRUE,INFINITE);
    
	
	GetExitCodeThread(hThread[6], &Code);
	if(Code == -1)
        printf("Find all the nodes\n"); //there are some problems that are confusing me.
										//The checking thread are running simutaniously with the five add-nodes threads,
										//so it's seems quite normal that it quits before all nodes are created, so it cannot find all the nodes in most of the time.

	for(i = 0; i < 6; ++i)
		CloseHandle(hThread[i]);

    clean();

	system("pause");
	
	return 0;
}