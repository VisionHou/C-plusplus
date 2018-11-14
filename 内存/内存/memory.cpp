#include<iostream>
using namespace std;


//class HeapOnly
//{
//public:
//	static HeapOnly* GetHeapObj()
//	{
//		return new HeapOnly;
//	}
//private:
//	HeapOnly()
//	{}
//	//私有拷贝构造，只声明不实现
//	HeapOnly(const HeapOnly& hp);
////  private:
//	//
//};
//HeapOnly p3;
//
//int main()
//{
//	HeapOnly *p1 = HeapOnly::GetHeapObj();
////	HeapOnly p2 (*p1);
//	
//	return 0;
//}

//class StackOnly
//{
//public:
//	static StackOnly GetStackObj()
//	{
//		return StackOnly();
//	}
//	void Print()
//	{
//		cout << "StackOnly::print()" << endl;
//	}
//private:
//	StackOnly()
//	{}
//};
//
////StackOnly p3;
//int main()
//{
//	StackOnly p1 = StackOnly::GetStackObj();
//	p1.Print();
//	StackOnly* p2= new StackOnly;
//	return 0;
//}


//class StackOnly
//{
//public:
//	StackOnly()
//	{}
//		void Print()
//	{
//		cout << "StackType::Print()" << endl;
//	}
//private:
//	void* operator new(size_t n) = delete;
//	void operator delete(void* p) = delete;
//};
//StackOnly Obj3;//
//int main()
//{
//	StackOnly Obj1;
//	static StackOnly Obj2;
//	Obj1.Print();
//	Obj2.Print();
//	Obj3.Print();
//
//	return 0;
//}


////单例模式
////饿汉模式 简单启动慢
//class Singleton
//{
//public:
//	static Singleton* Getinstance()
//	{
//		return &_instance;
//	}
//	/*static Singleton& Getinstance()
//	{
//		return _instance;
//	}*/
//			void Print()
//	{
//		cout << "StackType::Print()" << endl;
//	}
//
//private:
//	Singleton()
//	{}
//	//赋值运算符重载 防拷贝
//	Singleton(const Singleton&) = delete;
//	Singleton& operator=(const Singleton&) = delete;
//
//	static Singleton _instance;
//};
//Singleton Singleton::_instance;
//int main()
//{
//	//Singleton& singleton1 =Singleton::Getinstance();
//	Singleton* singleton2 = Singleton::Getinstance();
//
//	//singleton1.Print();
//	singleton2->Print();
//
//	return 0;
//}

//原子 指令级原子  ++i不是原子（源代码可能执行到一半，++i可能执行到一半）

#include <mutex>
class Singleton
{
public:
	static Singleton* GetInstance()
	{
		// 优先级加时间片 t1  t2
       //单核 t1执行 t2来执行指针不为空 就不是单例所以加互斥锁（二元信号量） 
		//lock();互斥量 静态

		// double check为了创建好以后不用锁的消耗
		if (_spInstance == nullptr)//其他线程并发来时还要串行
		{
			//t1 t2
			_smtx.lock();

			if (_spInstance == nullptr)
			{
				_spInstance = new Singleton;//再main函数结束以后delete
			}

			_smtx.unlock();


		}

		return _spInstance;
	}

	//内部类是外部类的友元垃圾回收
	class CGarbo {
	public:
		~CGarbo() {
			if (_spInstance)
			{
				delete _spInstance;
			}
		}
	};

private:
	Singleton()
	{
		cout << "Singleton()" << endl;
	}

	~Singleton()
	{
		// close
		cout << "~Singleton()" << endl;
	}

	//// 防拷贝 C++98
	//Singleton(const Singleton&);
	//Singleton& operator=(const Singleton&);

	// 防拷贝 C++11
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

	static Singleton* _spInstance;
	static mutex _smtx;
	static CGarbo _sgc;
};

mutex Singleton::_smtx;
Singleton::CGarbo Singleton::_sgc;
Singleton* Singleton::_spInstance = nullptr;



#include <thread>

void func(int n)
{
	cout << Singleton::GetInstance() << endl;
}

// t t1 t2 两个线程不是可重入 线程安全
int main()
{
	thread t1(func, 10);
	thread t2(func, 10);

	t1.join();
	t2.join();

	cout << Singleton::GetInstance() << endl;
	cout << Singleton::GetInstance() << endl;

	//void* p = new char[0xfffffffful];
	//cout << "new:" << p << endl;

	return 0;
}

