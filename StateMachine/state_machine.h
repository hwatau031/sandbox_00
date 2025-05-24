#pragma once
#include <list>
#include "singleton.h"
#include "interface.h"

template < typename ContextType >
class state_machine
{
protected:
    typedef ContextType context_t;
    typedef state_interface< context_t > state_t;
    typedef action_interface< context_t > action_t;
    typedef std::list< state_t* > state_list;

protected:
    //開始状態
    class start : public state_t, public singleton< start >
    {
        friend class singleton< start >;
        start() : state_t( _T( "start" ) ){}
    };
    //終了状態
    class end : public state_t, public singleton< end >
    {
        friend class singleton< end >;
        end() : state_t( _T( "end" ) ){}
    };

private:
    state_t* current;

public:
    state_machine()
        : current( start::get_instance() )
    {}

public:
    void update()
    {
        current->exe();
    }

    void change_state( state_t* dest_state, state_t* src_state = 0 )
    {
        if( src_state == 0 )src_state = current;

        //自己遷移
        if( src_state == dest_state )
        {
            src_state->exit();
            dest_state->entry();
            return;
        }

        //src_stateからrootまでの経路
        state_list src_top;
        for( state_t* s = src_state; s != 0; s = s->get_parent() )
            src_top.push_front( s );
        //dest_stateからrootまでの経路
        state_list dest_top;
        for( state_t* s = dest_state; s != 0; s = s->get_parent() )
            dest_top.push_front( s );

        //最も近い共通の親をrootから検索する
        state_t* parent = 0;
        typename state_list::iterator it_src = src_top.begin();
        typename state_list::iterator it_dest = dest_top.begin();

        while( it_src != src_top.end() && it_dest != dest_top.end() )
        {
            if( *it_src != *it_dest )break;
            ++ it_src;
            ++ it_dest;
        }
        //it_srcが先頭でない時の--it_srcが共通の親
        if( it_src != src_top.begin() )
        {
            -- it_src;
            parent = *it_src;
        }

        //退場動作
        for( state_t* s = current; s != parent; s = s->get_parent() )
            s->exit();

        //入場動作
        for( ; it_dest != dest_top.end(); ++ it_dest )
            ( *it_dest )->entry();

        current = dest_state;
    }

    context_t* derived()
    { return static_cast< context_t* >( this ); }

    void process_event( event const& e )
    {
        //イベントによるtransition
        //自分で処理できない場合は親に渡す
        state_t* s = current;
        while( s != 0 && !s->transit( e ) )
            s = s->get_parent();
    }

    void add_transition( state_t* current, event const& e, state_t* next, action_t* action )
    {
        current->add_transition( e, next );
        if( action )current->add_action( e, action );
    }

public:
    bool is_end()const
    { return current == end::get_instance(); }
};

