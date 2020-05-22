#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>                     // TODO A approfondir

#include <linux/types.h>
#include <linux/input.h>

#include "dualshock.h"

void default_callback( int A, int B ) {
    return ;
}


dualshock_t* dualshock_new( const char* joystick,
                            const char* touchpad,
                            const char* accelero ) {


    dualshock_t* shock ;
    shock = ( dualshock_t * ) malloc ( sizeof(dualshock_t) ) ;
    if ( shock == NULL ) {
        fprintf(stderr, "Erreur allocation memoire\n") ;
        return NULL ;
    }

    shock->fd_touchpad = open( touchpad, O_RDONLY ) ;
    if ( shock->fd_touchpad == -1 ) {
        fprintf(stderr,"Erreur d'accès au touchpad : %s\n", touchpad ) ;
        return NULL ;
    }

    shock->fd_accelero = open( accelero, O_RDONLY ) ;
    if ( shock->fd_accelero == -1 ) {
        fprintf(stderr,"Erreur d'accès a l'accelero : %s\n", accelero ) ;
        return NULL ;
    }
    
    shock->fd_joystick = open( joystick, O_RDONLY ) ;
    if ( shock->fd_joystick == -1 ) {
        fprintf(stderr,"Erreur d'accès au joystick : %s\n", joystick ) ;
        return NULL ;
    }

    shock->joystick_key_fct = default_callback ;
    shock->joystick_axis_fct = default_callback ;
    shock->touchpad_key_fct = default_callback ;
    shock->touchpad_axis_fct = default_callback ;
    shock->accelero_axis_fct = default_callback ;
    
    return shock ;

}


void dualshock_free( dualshock_t* shock ) {

    close( shock->fd_touchpad ) ;
    close( shock->fd_accelero ) ;
    close( shock->fd_joystick ) ;

    free ( shock ) ;
}

void dualshock_process_events( dualshock_t* shock ) {


    struct input_event e1 ;
    struct input_event e2 ;
    struct input_event e3 ;

    read (shock->fd_joystick, &e1, sizeof(e1)) ;
            switch( e1.type ) {
                case EV_SYN:
                        break ;
                case EV_ABS:
                        shock->joystick_axis_fct( e1.code, e1.value ) ;
			            break ;
                case EV_KEY:
                        shock->joystick_key_fct( e1.code, e1.value ) ;
                        break ;
            }

}








/*
    struct input_event e ;
    int fd ;

    fd = open( "/dev/input/event22", O_RDONLY ) ;

    while(1) {

        while (read (fd, &e, sizeof(e)) > 0) {
           
            switch( e.type ) {
            
                case EV_SYN:
                        break ;
                case EV_ABS:
                        if ( e.code == 3 ) 
                            printf("Axe %hi : %d \n", e.code, e.value ) ;
			break ;
                case EV_KEY:
                        printf("Bouton %hi : %d \n", e.code, e.value ) ;
                        
                        break ;

            }

        }    

        if (errno != EAGAIN ) {
            printf("Error\n") ;
        }

    }
    */
