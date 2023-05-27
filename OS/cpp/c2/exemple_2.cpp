//
// Created by infini on 12/05/22.
//
#include <QThread>
#include <QMutex>
#include <iostream>

static QMutex mutex;
static int global = 0;
static int increment = 1000000;

class MyThread : public QThread {
private:
    virtual void run(){
        for (int i = 0; i < increment; ++i) {
            mutex.lock();
            global = global + 1;
            mutex.unlock();
        }
    }
public:
    MyThread() : QThread(){

    }
};


int main(){
    MyThread t1, t2;

    t1.start();
    t2.start();

    t1.wait();
    t2.wait();

    std::cout<< " Global :  " << global <<std::endl;
    return EXIT_SUCCESS;
}
