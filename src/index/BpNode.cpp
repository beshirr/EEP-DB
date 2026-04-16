#include "../../include/index/BpNode.h"

const int BpNode::MAX_KEYS =
    (4096 - sizeof(BpNodeHeader)) / (sizeof(int) + sizeof(RID));

BpNode::BpNode(char* page_data, int pid) {
    data = page_data;
    page_id = pid;
}

BpNodeHeader* BpNode::get_header() {
    return reinterpret_cast<BpNodeHeader*>(data);
}

int BpNode::get_id() {
    return page_id;
}

bool BpNode::is_leaf() {
    return get_header()->is_leaf;
}

int BpNode::get_size() {
    return get_header()->num_keys;
}

void BpNode::set_size(int new_size) {
    get_header()->num_keys = new_size;
}

int* BpNode::key_array() {
    return reinterpret_cast<int*>(data + sizeof(BpNodeHeader));
}

int BpNode::get_key(int index) {
    if (index < 0 || index >= get_size()) {
        std::cerr << "index out of bounds\n";
        return -1;
    }
    return key_array()[index];
}

void BpNode::set_key(int index, int value) {
    if (index < 0 || index >= get_size()) {
        std::cerr << "index out of bounds\n";
        return;
    }
    key_array()[index] = value;
}

int BpNode::find_key_index(int key) {
    int left = 0;
    int right = get_size() - 1;

    while (left <= right) {
        int mid = (left + right) / 2;

        if (get_key(mid) == key)
            return mid;
        else if (get_key(mid) < key)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return left;
}

BpLeafNode::BpLeafNode(char *page_data, int pid) : BpNode(page_data, pid) {}

RID* BpLeafNode::value_array() {
    return reinterpret_cast<RID*>(data + sizeof(BpNodeHeader) + MAX_KEYS * sizeof(int));
}

RID BpLeafNode::get_value(int index) {
    if (index < 0 || index >= get_size()) {
        std::cerr << "index out of bounds\n";
        return RID();
    }
    return value_array()[index];
}

void BpLeafNode::set_value(int index, RID value) {
    if (index < 0 || index >= get_size()) {
        std::cerr << "index out of bounds\n";
        return;
    }
    value_array()[index] = value;
}

void BpLeafNode::shift_right(int index) {
    for (int i = get_size(); i > index; i--) {
        key_array()[i] = key_array()[i - 1];
        value_array()[i] = value_array()[i - 1];
    }
}

void BpLeafNode::INSERT(int key, RID value) {
    int index = find_key_index(key);
    shift_right(index);
    key_array()[index] = key;
    value_array()[index] = value;
    set_size(get_size() + 1);
}


BpInternalNode::BpInternalNode(char *page_data, int pid) : BpNode(page_data, pid) {}

int* BpInternalNode::children_array() {
    return reinterpret_cast<int*>(data + sizeof(BpNodeHeader) + MAX_KEYS * sizeof(int));
}

int BpInternalNode::get_child(int index) {
    if (index < 0 || index >= get_size()) {
        std::cerr << "index out of bounds\n";
        return -1;
    }
    return children_array()[index];
}

void BpInternalNode::set_child(int index, int value) {
    if (index < 0 || index >= get_size()) {
        std::cerr << "index out of bounds\n";
        return;
    }
    children_array()[index] = value;
}
