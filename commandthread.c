
#include "commandthread.h"
#include "utils.h"
#include <unistd.h>
#include <stdlib.h>

command_thread_desc_struct *cmDesc = NULL;

void *command_thread_func(void *arg) {
    
    cmDesc->s_socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (cmDesc->s_socket_desc == -1) {
        cmDesc->thread_state = TERMINATED;
        printf("Error: Could not create socket");
    }
    
    cmDesc->s_addr.sin_family = AF_INET;
    cmDesc->s_addr.sin_addr.s_addr = INADDR_ANY;
    cmDesc->s_addr.sin_port = htons(3150);
    
    if (bind(cmDesc->s_socket_desc, (struct sockaddr *)&cmDesc->s_addr, sizeof(sockaddr_in)) < 0) {
        perror("Error: Socket BIND failed");
        return 1;
    }
    
    listen(cmDesc->s_socket_desc, 1);    
    printf("Waiting for incoming connections...");
    
    while (is_alive()) {
        int addr_len = sizeof(struct sockaddr_in);
        cmDesc->c_socket_desc = accept(cmDesc->s_socket_desc, (struct sockaddr *)&cmDesc->c_addr, (socklen_t*)&addr_len);
        
        printf("Connection accepted!\n");
        
        while (is_alive()) {
            char *msg = "Hello!";
            write(cmDesc->c_socket_desc, msg, strlen(msg));
            usleep(1000000);
        }        
    }
    
    pthread_exit(0); 
}

int command_thread_create() {
    
    if (cmDesc == NULL) {
        return -2;
    }
    
    cmDesc = malloc(sizeof(command_thread_desc_struct));
    zero_memory(cmDesc, sizeof(command_thread_desc_struct));
    
    printf("Staring CommandThread...");    
    cmDesc->thread_state = STARTED;
    
    if (pthread_create(&cmDesc->thread, NULL, command_thread_func, NULL) != 0) {
        printf("FAILED\n");        
        command_thread_cleanup();
        return -1;
    }
    
    printf("OK\n");
    
    return 0;
}

void command_thread_free() {
    
    if (!is_alive()) {
        return;
    }
    
    cmDesc->thread_state = TERMINATED;    
    command_thread_cleanup();
}

void command_thread_join() {
    
    if (!is_alive()) {
        return;
    }
    
    pthread_join(cmDesc->thread, NULL);
}

void command_thread_cleanup() {    
    if (cmDesc != NULL) {
        cmDesc->thread = 0;
        cmDesc->thread_state = NOT_INITIALIZED;
    }
}

int is_alive() {
    return (cmDesc != NULL && cmDesc->thread != 0 && cmDesc->thread_state == STARTED);
}

