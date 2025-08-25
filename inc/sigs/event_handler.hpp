#ifndef _KEYBRD_
#define _KEYBRD_

#include "handler.hpp"
#include "app_state.hpp"

#include <mutex>
#include <queue>

class EventHandler {
public:
    int init(AppState* ptr_app);
    void init_table_sigs();

    void start();
    void regular_sig();
    void keyboard_sig();
    void extract_sig();

    void send_sig(int sig);

    void send_queue_sigs(int* sig);

    std::queue<int>& get_queue_sigs() { return q_sig; }

    void set_sleep_time(__useconds_t _time) { sleep_time = _time; }

    ~EventHandler();

private:

    void process_alt_combination(int first_char);

    __useconds_t sleep_time;
    AppState* user_data;
    std::queue<int> q_sig;
    _proc_sig_* table_proc;
    std::mutex locker;
};

#endif
