//======================================================================================
//	file  CSingletonBase.h
//	brief CSingletonBase
//	date  2014/06/13
// 
//======================================================================================

#ifndef __CSINGLETONBASE_H__
#define __CSINGLETONBASE_H__

#include <memory>

template <class T>
class CSingletonBase
{
public:
	static std::shared_ptr<T> GetInstance()
	{
		if( !m_pInstance ){ m_pInstance = CreateInstance(); }
		return m_pInstance;
	}

	static void DeleteInstance()
	{
//		if(m_pInstance){ delete m_pInstance; m_pInstance = 0; }
	}

private:
	static std::shared_ptr<T> CreateInstance(){
		return std::make_shared<T>();
	}

protected:
	CSingletonBase(){}
	virtual ~CSingletonBase(){}

	CSingletonBase(const CSingletonBase&);
	CSingletonBase& operator=(const CSingletonBase &);
	CSingletonBase(CSingletonBase &&);
	CSingletonBase& operator=(CSingletonBase &&);

private:
	static std::shared_ptr<T> m_pInstance;
};

template <class T>
std::shared_ptr<T> CSingletonBase<T>::m_pInstance;

#endif // __CSINGLETONBASE_H__

