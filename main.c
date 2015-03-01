/* 
 * File:   main.c
 * Author: vulsi_000
 *
 * Created on 28 февраля 2015 г., 14:11
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "commandthread.h" 

int main(int argc, char** argv) {
    
    if (argc == 0) {
        printf("Error: Required arguments are not specified\n");
        printf("Usage: scmd 0.0.0.0 3600\n");        
        return EXIT_FAILURE;
    }
    
    if (command_thread_create() == 0) {
        command_thread_join();
    } else {
        printf("Error: Cannot create CommandThread\n");
        return EXIT_FAILURE;
    }
    
    return (EXIT_SUCCESS);
}

