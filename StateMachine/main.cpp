/*
	ŠK‘wŒ^—LŒÀó‘Ô‹@ŠBiHierarchical Finite State Machinej
*/

#include <conio.h>
#include <tchar.h>
#include <iostream>

#include "singleton.h"
#include "state_machine.h"
#include "hfsm.h"
#include "event.h"


int main()
{
    hfsm state;

    while( !state.is_end() )
    {
        _TCHAR a = 0;

        state.update();
        if( a == _T( 'z' ) )state.process_event( event( hfsm::event_0 ) );
        if( a == _T( 'x' ) )state.process_event( event( hfsm::event_1 ) );
        if( a == _T( 'c' ) )state.process_event( event( hfsm::event_2 ) );
    }
    return 0;
}