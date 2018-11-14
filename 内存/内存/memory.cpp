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
//	//˽�п������죬ֻ������ʵ��
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


////����ģʽ
////����ģʽ ��������
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
//	//��ֵ��������� ������
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

//ԭ�� ָ�ԭ��  ++i����ԭ�ӣ�Դ�������ִ�е�һ�룬++i����ִ�е�һ�룩

#include <mutex>
class Singleton
{
public:
	static Singleton* GetInstance()
	{
		// ���ȼ���ʱ��Ƭ t1  t2
       //���� t1ִ�� t2��ִ��ָ�벻Ϊ�� �Ͳ��ǵ������Լӻ���������Ԫ�ź����� 
		//lock();������ ��̬

		// double checkΪ�˴������Ժ�����������
		if (_spInstance == nullptr)//�����̲߳�����ʱ��Ҫ����
		{
			//t1 t2
			_smtx.lock();

			if (_spInstance == nullptr)
			{
				_spInstance = new Singleton;//��main���������Ժ�delete
			}

			_smtx.unlock();


		}

		return _spInstance;
	}

	//�ڲ������ⲿ�����Ԫ��������
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

	//// ������ C++98
	//Singleton(const Singleton&);
	//Singleton& operator=(const Singleton&);

	// ������ C++11
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

// t t1 t2 �����̲߳��ǿ����� �̰߳�ȫ
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

