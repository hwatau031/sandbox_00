#pragma once

#include <iostream>
#include "state_machine.h"

#if defined(UNICODE) || defined(_UNICODE)
#define _tcout std::wcout
#else
#define _tcout std::cout
#endif

class hfsm
    : public state_machine< hfsm >
{
    //
    //イベント
    //
public:
    enum event_id
    { event_0, event_1, event_2 };

    //
    //ステート
    //
public:
    class state_0
        : public state_t
        , public singleton< state_0 >
    {
        friend class singleton< state_0 >;
        state_0() : state_t( _T( "state_0" ) ){}
    public:
        void entry(){ _tcout << _T( "state_0::entry\n" ); }
        void exit(){ _tcout << _T( "state_0::exit\n" ); }
    };
    class state_1
        : public state_t
        , public singleton< state_1 >
    {
        friend class singleton< state_1 >;
        state_1() : state_t( _T( "state_1" ) ){}
    public:
        void entry(){ _tcout << _T( "state_1::entry\n" ); }
        void exit(){ _tcout << _T( "state_1::exit\n" ); }
    };
	class state_2
        : public state_t
        , public singleton< state_2 >
    {
        friend class singleton< state_2 >;
        state_2() : state_t( _T( "state_2" ) ){}
    public:
        void entry(){ _tcout << _T( "state_2::entry\n" ); }
        void exit(){ _tcout << _T( "state_2::exit\n" ); }
    };
	class state_3
        : public state_t
        , public singleton< state_3 >
    {
        friend class singleton< state_3 >;
        state_3() : state_t( _T( "state_3" ) ){}
    public:
        void entry(){ _tcout << _T( "state_3::entry\n" ); }
        void exit(){ _tcout << _T( "state_3::exit\n" ); }
    };
    class state_4
        : public state_t
        , public singleton< state_4 >
    {
        friend class singleton< state_4 >;
        state_4() : state_t( _T( "state_4" ) ){}
    public:
        void entry(){ _tcout << _T( "state_4::entry\n" ); }
        void exit(){ _tcout << _T( "state_4::exit\n" ); }
    };

    //
    //アクション
    //
public:
    class action_0
        : public action_t
        , public singleton< action_0 >
    {
    public:
        void exe( context_t* /*context*/ ){ _tcout << _T( "action_0\n" ); }
    };

    //
    //hfsm
    //
public:
    hfsm()
    {
        //
        //ステート階層
        //
        state_4::get_instance()->set_parent( 0, this );
            state_0::get_instance()->set_parent( state_4::get_instance(), this );
            state_1::get_instance()->set_parent( state_4::get_instance(), this );
                state_2::get_instance()->set_parent( state_1::get_instance(), this );
                    state_3::get_instance()->set_parent( state_2::get_instance(), this );

        //
        //状態遷移テーブル
        //
        add_transition( state_0::get_instance(), event( event_0 ), state_3::get_instance(), action_0::get_instance() );
        add_transition( state_1::get_instance(), event( event_1 ), state_0::get_instance(), 0 );
        add_transition( state_0::get_instance(), event( event_2 ), end::get_instance(), 0 );

        change_state( state_0::get_instance() );
    }
};

