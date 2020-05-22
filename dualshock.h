#ifndef DUALSHOCK_H
#define DUALSHOCK_H

#define PS4_BTN_CROIX               304
#define PS4_BTN_CARRE               308
#define PS4_BTN_TRIANGLE            307
#define PS4_BTN_ROND                305
#define PS4_BTN_L1                  310
#define PS4_BTN_L2                  312
#define PS4_BTN_R1                  311
#define PS4_BTN_R2                  313
#define PS4_BTN_PLAYSTATION         316
#define PS4_BTN_SHARE               314     
#define PS4_BTN_OPTION              315
#define PS4_BTN_ANALOG_L            317
#define PS4_BTN_ANALOG_R            318
#define PS4_TOUCHPAD_BTN_FINGER     325
#define PS4_TOUCHPAD_BTN_2FINGERS   333
#define PS4_TOUCHPAD_BTN_CONTACT    330
#define PS4_TOUCHPAD_BTN_PRESS      272

typedef struct {

    int fd_touchpad ;
    int fd_accelero ;
    int fd_joystick ;

    void (*joystick_key_fct)   ( int code, int value ) ;
    void (*joystick_axis_fct)  ( int axis, int value ) ;
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

void dualshock_get_button_name( char* name, int code )  ;



#endif
