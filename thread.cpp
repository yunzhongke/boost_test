#include <iostream>
#include <boost/thread.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/scoped_thread.hpp>



void print_hello()
{
    std::cout << "hello thread" << std::endl;
}

void thread_test1()
{
    boost::thread t(print_hello);
    t.join();
}

void thread_test2()
{
    boost::thread *t = new boost::thread(print_hello);

    std::cout << t->get_id() << std::endl;
    std::cout << "physical number :" << t->physical_concurrency() << std::endl;

    t->join();
    delete t;
}

void thread_test3()
{
    boost::thread *t1 = new boost::thread(print_hello);
    boost::thread *t2 = new boost::thread(print_hello);

    std::cout << "swap before : t1.id = " << t1->get_id() << " , t2.id = " << t2->get_id() << '\n';
    t1->swap(*t2);

    std::cout << "swap after : t1.id = " << t1->get_id() << " , t2.id = " << t2->get_id() << '\n';
    t1->join();
    t2->join();
    delete  t1;
    delete  t2;
}

void thread_test4()
{
    boost::thread_group *g = new boost::thread_group();
    std::cout << "thread_group number :" << g->size() << std::endl;

    g->create_thread(print_hello);
    std::cout << "thread_group number :" << g->size() << std::endl;

    boost::thread *t = new boost::thread(print_hello);
    boost::thread *t2 = new boost::thread();
    g->add_thread(t);
    std::cout << "thread_group number :" << g->size() << std::endl;

    std::cout << "thread_t is in thread_grop :" << g->is_thread_in(t) << std::endl;

    std::cout << "thread_t2 is in thread_grop : " << g->is_thread_in(t2) << std::endl;

    g->remove_thread(t);
    std::cout << "thread_group remove_thread after number :" << g->size() << std::endl;
    g->join_all();
    delete g;
}

void thread_test5()
{
    
}

int main(int argc , char *argv)
{
    //thread_test1();
    //thread_test2();
    //thread_test3();
    thread_test4();

    std::cout << "hello!\n";
    return 0;
}
