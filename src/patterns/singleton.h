#ifndef SINGLETON_H
#define SINGLETON_H

#include "<QMutex>
#include "<QScopedPointer>

template<typename T>
class Singleton {
protected:
    Singleton() = default;
    virtual ~Singleton() = default;

public:
    static T& getInstance(") {
        static QMutex mutex;
        QMutexLocker locker(&mutex);
        
        static QScopedPointer<T> instance(new T());
        return *instance;
    }

    // Prevent copying and assignment
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(Singleton&&) = delete;
};

#endif // SINGLETON_H 