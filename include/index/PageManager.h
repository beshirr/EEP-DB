#pragma once

#include <iostream>
#include <ostream>
#include <cstring>

class PageManager {
private:
    static const int MAX_PAGES = 100;
    char pages[MAX_PAGES][4096];
    int next_page_id;
public:
    PageManager();
    int allocate_page();
    char* get_page(int page_id);
};