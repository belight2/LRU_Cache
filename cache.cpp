#include "cache.h"
#include <sstream>
// TODO: 필요한 함수 구현
Cache::Cache(){ 
  void *data = new char;
  *(char*)data = '\0';
  tail = new node("-", "-", data);

  cache_size = 0;

  head = tail;

  for(int i = 0; i < HASH_SIZE; i++) bucket[i] = nullptr;
}

Cache::~Cache(){
  node* cur = head;
  while(cur != nullptr){
    node *tmp = cur;
    cur = cur->next;
    delete tmp;
  }
}
std::string Cache::get_node_info(node *cur){
  std::string info{};
  info = "[" + cur->key + ": ";
  if(cur->type == "int") info += std::to_string(*(int*)(cur->data));
  else if(cur->type == "double"){
    std::ostringstream ss;
    ss << *(double*)(cur->data);
    info += ss.str();
  }
  info += "]";
  return info;
}
void Cache::list_add(node *new_node){
  cache_size++;

  new_node->next = head;
  head->prev = new_node;
  head = new_node;
}
std::string Cache::list_erase(){
  if(cache_size == 0) return "";
  cache_size--;
  node* erase_node = tail->prev;

  std::string key = erase_node->key;

  if(cache_size == 0){
    head = tail;
    return key;
  }

  tail->prev = erase_node->prev;
  erase_node->prev->next = tail;

  return key;
}
void Cache::move_to_head(node *cur){
  if(cur == head) return;
  cur->next->prev = cur->prev;
  cur->prev->next = cur->next;

  cur->prev = nullptr;
  cur->next = head;
  head->prev = cur;
  head = cur;
}
std::string Cache::list_toString(){
  node *cur = head;
  int sep = cache_size - 1;
  std::string info{};
  while(cur->next != nullptr){
    info += get_node_info(cur);
    cur = cur->next;
    if(sep--) info += "->";
  }
  return info;
}
/*--------------------------------------------------------------*/
/*-------------------------해시 구현부----------------------------*/
int Cache::hashing(std::string key){
  int index = 0;
  for(int i = 0; i < key.length(); i++) index += key[i];
  return index % HASH_SIZE;
}

void Cache::hash_add(node* new_node){
  int index = hashing(new_node->key);
  if(bucket[index] == nullptr){
    bucket[index] = new_node;
    return;
  }
  node *cur = bucket[index];
  while(cur->hash_next != nullptr) cur = cur->hash_next;
  cur->hash_next = new_node;
}

Cache::node* Cache::hash_find(std::string key){
  int index = hashing(key);
  node *cur = bucket[index];
  if(cur == nullptr) return nullptr;
  while(cur != nullptr){
    if(cur->key == key) return cur;
    cur = cur->hash_next;
  }
  return nullptr;
}

void Cache::hash_erase(){
  std::string key = list_erase();
  int index = hashing(key);
  node *cur = bucket[index];
  if(cur->key == key){
    node *tmp = cur->hash_next;
    bucket[index] = tmp;
    delete cur;
    return;
  }
  while(cur->hash_next->key != key) cur = cur->hash_next;
  node *tmp = cur->hash_next;
  cur->hash_next = tmp->hash_next;
  delete tmp;
}
/*---------------------------------------------------------------*/

void Cache::add(std::string key, int value){
  void *data = new int;
  *(int*)data = value;
  node* new_node = new node(key, "int", data);
  if(cache_size == CACHE_SIZE) hash_erase();
  list_add(new_node);
  hash_add(new_node);
}

void Cache::add(std::string key, double value){
  void *data = new double;
  *(double*)data = value;
  node* new_node = new node(key, "double", data);
  if(cache_size == CACHE_SIZE) hash_erase();
  list_add(new_node);
  hash_add(new_node);
}

bool Cache::get(std::string key, int &value){
  node *find_node = hash_find(key);
  if(find_node == nullptr) return 0;
  value = *(int*)(find_node->data);
  move_to_head(find_node);
  return 1;
}

bool Cache::get(std::string key, double &value){
  node *find_node = hash_find(key);
  if(find_node == nullptr) return 0;
  value = *(double*)(find_node->data);
  move_to_head(find_node);
  return 1;
}

std::string Cache::toString(){ return list_toString(); }