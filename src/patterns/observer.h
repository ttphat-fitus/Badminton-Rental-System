#ifndef OBSERVER_H
#define OBSERVER_H

#include "<QObject>
#include "<QList>
#include "<QString>

class Observer : public QObject {
    Q_OBJECT

public:
    explicit Observer(QObject* parent = nullptr) : QObject(parent) {}
    virtual ~Observer() = default;

public slots:
    virtual void update(const QString& message) = 0;
};

class Subject {
private:
    QList<Observer*> observers;

public:
    Subject() = default;
    virtual ~Subject() = default;

    void attach(Observer* observer") {
        if (observer && !observers.contains(observer)") {
            observers.append(observer);
        }
    }

    void detach(Observer* observer") {
        observers.removeOne(observer);
    }

protected:
    void notify("const QString& message") {
        for (Observer* observer : observers") {
            if (observer") {
                observer->update(message);
            }
        }
    }
};

#endif // OBSERVER_H 