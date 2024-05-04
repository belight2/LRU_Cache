#include "cached_runner.h"
// TODO: 필요한 함수 구현
CachedRunner::CachedRunner(Cache &cache){
  this->cache = &cache;
  this->hit_count = 0;
  this->miss_count = 0;
}

bool CachedRunner::is_palindrome(std::string str){
  for(int i = 0; i < str.size() / 2; i++){
    if(str[i] != str[str.size() - i - 1]) return false;
  }
  return true;
}

double CachedRunner::multiply(std::string filename){
  std::string key = "multiply(" + filename +")";
  double value = 1;
  if(cache->get(key, value)){
     hit_count++;
     return value;
  }
  miss_count++;
  std::ifstream file(filename);
  double number;
  while(file >> number) value *= number;
  cache->add(key, value);
  return value;
}

int CachedRunner::palindrome(std::string filename){
  std::string key = "palindrome(" + filename + ")";
  int value = 0;
  if(cache->get(key, value)){
    hit_count++;
    return value;
  }
  miss_count++;
  std::ifstream file(filename);
  std::string full_text;
  std::string line;
  while(std::getline(file, line)) full_text += line;
  int max_len = 0;
  int max_idx = 0;
  std::string max_palindrome;

  for(int i = 0; i < full_text.size(); i++){
    for(int j = i + 1; j < full_text.size(); j++){
      std::string sub = full_text.substr(i, j - i + 1);
      if(is_palindrome(sub) && sub.size() > max_len){
        max_len = sub.size();
        max_idx = i;
        max_palindrome = sub;
      }
    }
  }
  cache->add(key, max_idx);
  return max_idx;
}

int CachedRunner::hits(){ return hit_count; }
int CachedRunner::misses(){ return miss_count; }