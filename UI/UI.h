#pragma once

#include <crtdbg.h>
#include "../services/services.h"

class UI {
private:
    Services controller;

    void add_event();
    void remove_event();
    void update_event();

    void get_events_from_month();
    void delete_user_event();

public:
    explicit UI();

    static int get_first_option();
    static int get_admin_option();
    static int get_user_option();

    void admin_actions();
    void user_actions();

    void run();
};
