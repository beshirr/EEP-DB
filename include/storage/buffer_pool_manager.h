#pragma once

#include <list>
#include <unordered_map>
#include <vector>

#include "page.h"
#include "../config.h"

class BufferPoolManager {
public:
    Page* FetchPage(page_id_t page_id);
    bool UnpinPage(page_id_t page_id, bool is_dirty);
    Page* NewPage(page_id_t& page_id);
    bool DeletePage(page_id_t page_id);
    bool FlushPage(page_id_t page_id);
    void FlushAllPages();

private:
    std::vector<Page*> pages_;
    std::unordered_map<page_id_t, frame_id_t> page_map_;
    std::list<frame_id_t> free_list_;
    // TODO: add a replacer
};