/* 
 * File:   commandthread.h
 * Author: vulsi_000
 *
 * Created on 28 февраля 2015 г., 17:34
 */

#ifndef COMMANDTHREAD_H
#define	COMMANDTHREAD_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>

typedef enum {
    STARTED = 1,
    TERMINATED = -1,
    NOT_INITIALIZED = 0
} command_thread_state;

typedef struct {
    command_thread_state thread_state;
    pthread_t thread;
    
    int s_socket_desc;
    int c_socket_desc;
    
    struct sockaddr_in s_addr;
    struct sockaddr_in c_addr;
    
} command_thread_desc_struct;

int command_thread_create();
void command_thread_free();
void command_thread_join();

#ifdef	__cplusplus
}
#endif

#endif	/* COMMANDTHREAD_H */

