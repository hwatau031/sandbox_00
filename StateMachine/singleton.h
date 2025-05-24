#pragma once

// singletonクラス
// 各状態はsingletonクラスを継承します。
template < typename T >
class singleton
{
protected:
    singleton(){}
    singleton( singleton const& );
    ~singleton(){}

    singleton& operator=( singleton const& );

public:
    static T* get_instance()
    {
        static T instance;
        return &instance;
    }
};

