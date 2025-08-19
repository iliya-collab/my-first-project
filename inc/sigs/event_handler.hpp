#ifndef _KEYBRD_
#define _KEYBRD_

#include "handler.hpp"
#include "app_state.hpp"

#include <thread>
#include <mutex>
#include <queue>
#include <ncurses.h>
#include <unistd.h>

class EventHandler {
public:
    int init(AppState* ptr_app);
    void init_table_sigs();

    void start() {
        auto lamb = [this](){
            while (!user_data->ex)
            {
                usleep(sleep_time);
                if (q_sig.empty())
                {
                    locker.lock();
                    regular_sig();
                    keyboard_sig();
                    /*if (!q_sig.empty())
                        save_log("Send : " + std::to_string(q_sig.front()));*/
                    locker.unlock();
                }
            }
	    };
	
        std::thread th(lamb);
        th.detach();
    }
    void regular_sig();
    void keyboard_sig();
    void extract_sig();

    void send_sig(int sig) { 
        locker.lock();
        if (q_sig.empty() || q_sig.back() != sig)
            q_sig.push(sig);
        locker.unlock(); 
    }

    void send_queue_sigs(int* sig) { 
        locker.lock();
        int i = 0;
        for (int isig = sig[i]; isig != SIGNAL::END; isig = sig[i])
        {
            if (q_sig.empty() || q_sig.back() != isig)
                q_sig.push(isig);
            i++;
        }
        locker.unlock(); 
    }

    std::queue<int>& get_queue_sigs() { return q_sig; }

    void set_sleep_time(__useconds_t _time) { sleep_time = _time; }

    ~EventHandler() {
        free(table_proc);
    }

private:

    __useconds_t sleep_time;
    AppState* user_data;
    std::queue<int> q_sig;
    _proc_sig_* table_proc;
    std::mutex locker;
};

#endif
