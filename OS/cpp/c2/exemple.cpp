/** @file main.cpp
 *  @brief Exemple de passages d'arguments à 2 threads
 *
 *  Cet exemple illustre le lancement de 2 threads et le passage d'arguments
 *  via le constructeur. Les threads s'exécutent de manière séquentielle.
 *
 *  @date 17.02.2017
 *  @bug Pas de bug connu
 */

#include <QThread>
#include <iostream>

/**
 * @brief Structure simple
 */
typedef struct {
    int a;
    int b;
} struct_t;

/**
 * @brief Thread avec une variable membre struct
 * Attention ici au fait que la structure doit rester en mémoire durant
 * toutes l'exécution du thread, sinon il y aura corruption mémoire.
 */
class MyThread1 : public QThread {
private:

    struct_t *var;

    void run() Q_DECL_OVERRIDE {
        std::cout << "Task 1: a = " << var->a
                  << ", b = " << var->b << std::endl;
    }

public:
    //! Constructeur avec passage d'arguments
    MyThread1(struct_t *arg) : QThread(),
                               var(arg) {}
};

/**
 * @brief Thread avec une variable membre de type int
 */
class MyThread2 : public QThread {
private:

    int aValue;

    void run() Q_DECL_OVERRIDE {
        std::cout << "Task 2: value = "
                  << aValue << std::endl;
    }

public:

    //! Constructeur avec passage d'arguments
    MyThread2(int value) : QThread(),
                           aValue(value) {}
};

/**
 * @brief main
 * @return 0
 */
int main(int /*argc*/,char */*argv*/[])
{
    // La structure existe en mémoire durant toute l'exécution de thread1: ok
    struct_t v;
    v.a = 1; v.b = 2;

    // Création et lancement d'un thread, puis attente de terminaison
    MyThread1 thread1(&v);
    thread1.start();
    thread1.wait();

    // Création et lancement d'un thread, puis attente de terminaison
    MyThread2 thread2(3);
    thread2.start();
    thread2.wait();


    return EXIT_SUCCESS;
}