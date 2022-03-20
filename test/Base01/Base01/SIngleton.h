#pragma once
template <typename T>

//인스턴스 공유
class Singleton
{
public:
	static T* getInstance() {
		static T instance;
		return &instance;
	}
};

//class Singleton
//{
//private:
//    static Singleton instance;
//    Singleton(){}
//
//public:
//    static Singleton* getInstance() {
//        return &instance;
//    }
//
//};
//
//Singleton Singleton::instance;


//class Singleton
//{
//private:
//    Singleton() {}
//
//public:
//    static Singleton* getInstance() {
//        static Singleton instance;
//        return &instance;
//    }
//
//};

//class Singleton
//{
//private:
//    static Singleton* instance;
//    Singleton();
//
//public:
//    static Singleton* getInstance()
//    {
//        if (instance == nullptr) instance = new Singleton;
//        return instance;
//    }
//
//    static void release()
//    {
//        if (instance) delete instance;
//        instance = nullptr;
//    }
//};
//static Singleton* instance = nullptr;
