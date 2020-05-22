#ifndef DUALSHOCK_H
#define DUALSHOCK_H

typedef struct {

    int fd_touchpad ;
    int fd_accelero ;
    int fd_joystick ;

    void (*joystick_key_fct)   ( int code, int value ) ;
    void (*joystick_axis_fct) ( int axis, int value ) ;
    void (*touchpad_key_fct)   ( int code, int value ) ;
    void (*touchpad_axis_fct)  ( int axis, int value ) ;
    void (*accelero_axis_fct)  ( int axis, int value ) ;

    // int touchpad_nb_axis ;
    // double* touchpad_axis ;
    // int touchpad_nb_keys ;
    // double* touchpad_keys ;
    // 
    // int joystick_nb_axis ;
    // double* joystick_axis ;
    // int joystick_nb_keys ;
    // double* joystick_keys ;
    // 
    // int accelerometer_nb_axis ;
    // double* accelerometer_axis ;

} dualshock_t ;

dualshock_t* dualshock_new ( const char* joystick, const char* touchpad, const char* accelero ) ;
void dualshock_free ( dualshock_t* ) ;
void dualshock_process_events( dualshock_t*) ;

#endif
