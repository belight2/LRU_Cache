#ifndef CACHE_H
#define CACHE_H

#include <string>
#include <cstdlib>
#define CACHE_SIZE 10

#include <iostream>

class Cache {
private:
  // TODO: private inner struct/class 선언 가능
  // TODO: private 멤버 변수와 함수 추가 가능
  
  // 연결리스트 요소
  typedef struct node{
    // 노드의 키값
    std::string key;

    // 노드의 데이터 타입 정보
    std::string type;

    // 노드의 데이터 
    void *data;

    // 노드의 다음 데이터 정보
    struct node *next;

    // 노드의 이전 데이터 정보
    struct node *prev;

    // 해시에서 사용하는 다음 데이터 정보
    struct node *hash_next;

    // 노드의 constructor
    node(std::string key, std::string type, void *data)
    : data(data), key(key), type(type), next(nullptr), prev(nullptr), hash_next(nullptr) {}

    // 노드의 destructor
    ~node(){
      if(type == "int") delete static_cast<int*>(data);
      else if(type == "double") delete static_cast<double*>(data);
      else if(type == "-") delete static_cast<char*>(data); // tail 삭제
    }
  } node;
  
  node *head;
  node *tail;
  int cache_size = 0;

  std::string get_node_info(node *cur);

  void list_add(node *new_node);

  std::string list_erase();

  void move_to_head(node *cur);

  std::string list_toString();

  const int HASH_SIZE = 10;
  node *bucket[10];

  int hashing(std::string key);
  
  void hash_add(node *new_node);
  
  node* hash_find(std::string key);
  
  void hash_erase();

public:
  Cache();
  ~Cache();
  // int를 cache에 추가한다
  void add(std::string key, int value);
  // double을 cache에 추가한다
  void add(std::string key, double value);
  // key에 해당하는 value를 cache에서 가져온다
  // 타입과 key가 동일한 원소가 없다면 false를 반환한다.
  bool get(std::string key, int &value);
  // key에 해당하는 value를 cache에서 가져온다.
  // 타입과 key가 동일한 원소가 없다면 false를 반환한다.
  bool get(std::string key, double &value);

  // 디버그 및 채점 용: 연결 리스트를 문자열로 표현하여 반환한다
  // 다음과 같이 표현된 문자열을 반환한다
  // [key1: value1] -> [key2: value2] -> ... -> [keyN: valueN]
  std::string toString();
};

#endif