//
//  LRU.h
//  cppLeetCode
//
//  Created by xcoderliu on 4/23/22.
//

#include<iostream>
#include<map>
using namespace std;

/**
 * Definition of cache list node, it's double linked list node.
 */
struct CacheNode {
    int key;
    int value;
    CacheNode *pre, *next;
    CacheNode(int k, int v) : key(k), value(v), pre(nullptr), next(nullptr) {}
};

class LRUCache {
    int size; //max size
    CacheNode *head, *tail;
    map<int, CacheNode*> table;
    
    LRUCache(int capacity) {
        size = capacity;
        head = nullptr;
        tail = nullptr;
    }
    
    int get(int key) {
        map<int, CacheNode*>::iterator it = table.find(key);
        if (it != table.end()) {
            CacheNode *cache = it->second;
            // net remove the push to head
            remove(cache);
            move2Head(cache);
            return cache->value;
        } else {
            return -1;
        }
    }
    
    void set(int key, int value) {
        map<int, CacheNode*>::iterator it = table.find(key);
        if (it != table.end()) { //finded
            CacheNode *cache = it->second;
            cache->value = value;
            remove(cache);
            move2Head(cache);
        } else {
            if (table.size() >= size) { //remove last
                map<int, CacheNode *>::iterator it = table.find(tail->key);
                remove(tail);
                table.erase(it);
            } else {
                CacheNode *newCache = new CacheNode(key, value);
                move2Head(newCache);
                table[key] = newCache;
            }
        }
    }
    
    void remove(CacheNode *node) {
        if (node->pre != NULL) {
            node->pre->next = node->next;
        } else {
            head = node->next;
        }
        if (node->next != nullptr) {
            node->next->pre = node->pre;
        } else {
            tail = node->pre;
        }
    }
    
    void move2Head(CacheNode *node) {
        node->next = head;
        node->pre = nullptr;
        if (head != nullptr) {
            head->pre = node;
        }
        head = node;
        if (tail == nullptr) {
            tail = head;
        }
    }
};
