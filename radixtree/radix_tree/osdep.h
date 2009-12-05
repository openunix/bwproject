#ifndef OSDEP_H
#define OSDEP_H
#include "stdio.h"

void initialize_var();
void clean();

// locker functions        
int unlock_write();
int lock_write();
int unlock_read();
int lock_read();

// a little more functions 
int get_waiting_writers();
int get_waiting_readers();
int get_lock_count();


#endif