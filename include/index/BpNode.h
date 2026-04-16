#pragma once

#include <iostream>
#include <ostream>
#include <cstring>

struct BpNodeHeader {
    bool is_leaf;
    int num_keys;
    int parent_page_id;
    int next_page_id;
};

struct RID {
    int page_id;
    int slot_id;
};

class BpNode {
protected:
    char* data;
    int page_id;
    static const int MAX_KEYS;

public:
    BpNode(char* page_data, int pid);

    BpNodeHeader* get_header();
    int get_id();

    bool is_leaf();

    int get_size();
    void set_size(int new_size);

    int* key_array();

    int get_key(int index);
    void set_key(int index, int value);

    int find_key_index(int key);
};

class BpLeafNode : public BpNode {
public:
    BpLeafNode(char* page_data, int pid);
    RID* value_array();
    RID get_value(int index);
    void set_value(int index, RID value);
    void shift_right(int index);
    void INSERT(int key, RID value);
};

class BpInternalNode : public BpNode {
public:
    BpInternalNode(char* page_data, int pid);
    int* children_array();
    int get_child(int index);
    void set_child(int index, int value);
};
