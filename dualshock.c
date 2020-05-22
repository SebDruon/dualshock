#include <linux/types.h>
#include <linux/input.h>


dualshock_t* dualshock_new( const char* joystick,
                            const char* touchpad,
                            const char* accelero ) {


    dualshock_t* shock ;
    shock = ( dualshock_t * ) malloc ( sizeof(dualshock_t) ) ;
    if ( shock == NULL ) {
        fprintf(stderr, "Erreur allocation memoire\n") ;
        return NULL ;
    }

    fd_touchpad = open( touchpad, O_RDONLY ) ;
    if ( fd_touchpad == -1 ) {
        fprintf("Erreur d'accès au touchpad : %s\n", touchpad ) ;
        return NULL ;
    }

    fd_accelero = open( accelero, O_RDONLY ) ;
    
    fd_joystick = open( joystick, O_RDONLY ) ;





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
