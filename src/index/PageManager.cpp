#include "../../include/index/PageManager.h"


PageManager::PageManager() {
    next_page_id = 0;
}

int PageManager::allocate_page() {
   return  next_page_id++;
}

char* PageManager::get_page(int page_id) {
    if (page_id < 0 || page_id >= MAX_PAGES) {
        std::cerr << "Invalid page ID" << std::endl;
        return nullptr;
    }
    return pages[page_id];
}
