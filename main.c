#include <stdio.h>
#include "dualshock.h"

void joystick_key_callback  ( int code, int value ) ;
void joystick_axis_callback ( int axis, int value ) ;
void touchpad_key_callback   ( int code, int value ) ;
void touchpad_axis_callback  ( int axis, int value ) ;
void accelero_axis_callback  ( int axis, int value ) ;

void joystick_key_callback  ( int code, int value ) {
    printf("Bouton \n") ;
    return ;
}   

void joystick_axis_callback ( int axis, int value ) {
    return ;
}

void touchpad_key_callback   ( int code, int value ) {
    return ;
}

void touchpad_axis_callback  ( int axis, int value ) {
    return ;
}

void accelero_axis_callback  ( int axis, int value ) {
    return ;
}




int main( int argc, char** argv, char** envv ) {

    int done ;

    dualshock_t* manette ;

    manette = dualshock_new( ) ;

    manette->joystick_key_fct = joystick_key_callback ;
    manette->joystick_axis_fct = joystick_axis_callback ;
    manette->touchpad_key_fct = touchpad_key_callback ;
    manette->touchpad_axis_fct = joystick_axis_callback ;
    manette->accelero_axis_fct = accelero_axis_callback ;


    done = 0 ;
    while (!done ) {

        dualshock_process_events( manette ) ;

    }


    dualshock_delete( manette ) ;

    return 0 ;

}
