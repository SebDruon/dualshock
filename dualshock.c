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

    read (shock->fd_touchpad, &e2, sizeof(e2)) ;
            switch( e2.type ) {
                case EV_SYN:
                        break ;
                case EV_ABS:
                        shock->touchpad_axis_fct( e2.code, e2.value ) ;
                        break ;
                case EV_KEY:
                        shock->touchpad_key_fct( e2.code, e2.value ) ;
                        break ;
            }
}


void dualshock_get_button_name( char* name, int code ) {
    switch (code) {
        case PS4_BTN_CROIX:             
            sprintf( name, "Croix" ) ;
            break ;
        case PS4_BTN_CARRE:             
            sprintf( name, "Carré" ) ;
            break ;
        case PS4_BTN_TRIANGLE:          
            sprintf( name, "Triangle" ) ;
            break ;
        case PS4_BTN_ROND:              
            sprintf( name, "Rond" ) ;
            break ;
        case PS4_BTN_L1:                
            sprintf( name, "L1" ) ;
            break ;
        case PS4_BTN_L2:                
            sprintf( name, "L2" ) ;
            break ;
        case PS4_BTN_R1:                
            sprintf( name, "R1" ) ;
            break ;
        case PS4_BTN_R2:                
            sprintf( name, "R2" ) ;
            break ;
        case PS4_BTN_PLAYSTATION:       
            sprintf( name, "Playstation" ) ;
            break ;
        case PS4_BTN_SHARE:             
            sprintf( name, "Share" ) ;
            break ;
        case PS4_BTN_OPTION:            
            sprintf( name, "Option" ) ;
            break ;
        case PS4_BTN_ANALOG_L:          
            sprintf( name, "Joytick Analgique Gauche" ) ;
            break ;
        case PS4_BTN_ANALOG_R:
            sprintf( name, "Joystick Analogique Droite" ) ;
            break ;
        case PS4_TOUCHPAD_BTN_FINGER:
            sprintf( name, "Contact 1 doigt" ) ;
            break ;
        case PS4_TOUCHPAD_BTN_2FINGERS:
            sprintf( name, "Contact 2 doigts" ) ;
            break ;
        case PS4_TOUCHPAD_BTN_CONTACT:
            sprintf( name, "Contact" ) ;
            break ;
        case PS4_TOUCHPAD_BTN_PRESS:
            sprintf( name, "Click" ) ;
            break ;
        default:
            sprintf( name, "Bouton inconnu !!!!!!!" ) ;
            break ;

    }

}
