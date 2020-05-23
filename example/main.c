#include <stdio.h>
#include "dualshock/dualshock.h"

void btn_callback  ( int code, int value ) ;
void joystick_axis_callback ( int axis, int value ) ;
void touchpad_axis_callback  ( int axis, int value ) ;
void accelero_axis_callback  ( int axis, int value ) ;

void btn_callback  ( int code, int value ) {
    char bouton[50] ;
    dualshock_get_button_name( bouton, code ) ;
    if ( value == 0 )
       printf("Bouton %s relaché \n", bouton ) ;
    else
        printf("Bouton %s pressé  \n", bouton ) ;

    return ;
}   

void joystick_axis_callback ( int axis, int value ) {
    printf("[Joystick] Axis : %d - %d \n", axis, value ) ;
    return ;
}

void touchpad_axis_callback  ( int axis, int value ) {
    char name[50] ;
    dualshock_get_button_name( name, axis );
    printf("[Mouse] Axis : %s - %d \n", name, value ) ;
    return ;
}

void accelero_axis_callback  ( int axis, int value ) {
    char name[50] ;
    dualshock_get_button_name( name, axis );
    printf("[Accelero] Axis : %s - %d \n", name, value ) ;
    return ;
}




int main( int argc, char** argv, char** envv ) {

    int done ;

    dualshock_t* manette ;

    manette = dualshock_new( "/dev/input/event23",        // joystick
                             "/dev/input/event21",        // touchpad
                             "/dev/input/event22"  ) ;    // accelero

//    manette->joystick_key_fct = btn_callback ;
//    manette->touchpad_key_fct = btn_callback ;
//    manette->joystick_axis_fct = joystick_axis_callback ;
//    manette->touchpad_axis_fct = touchpad_axis_callback ;
    manette->accelero_axis_fct = accelero_axis_callback ;

    done = 0 ;
    while (!done ) {

        dualshock_process_events( manette ) ;

    }

    dualshock_free( manette ) ;

    return 0 ;

}
