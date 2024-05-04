#include "cached_runner.h"
#include "task.h"
#include <iostream>
#include <sstream>
#include <string>

const bool DEBUG = true;

// 디버그 용 출력 함수
void print(const std::string &message) {
  if (DEBUG) {
    std::cout << message << std::endl;
  }
}

// double 값을 문자열로 변환한다
std::string doubleToString(double value) {
  std::ostringstream ss;
  ss << value;
  return ss.str();
}

int main() {
  Cache cache;
  CachedRunner runner(cache);
  Task task;

  TaskSet taskSet("resources/task_set.txt");
  int index = 0;

  // 태스크를 계속 읽어 수행한다
  while (taskSet.getNext(task)) {
    print("[TASK #" + std::to_string(index++) + "]");
    switch (task.type) {
    case MULTIPLY: {
      double result = runner.multiply(task.filename);
      print("multiply(" + task.filename + ") = " + doubleToString(result));
    } break;
    case PALINDROME: {
      int result = runner.palindrome(task.filename);
      print("palindrome(" + task.filename + ") = " + std::to_string(result));
    } break;
    }

    print("\n[CACHE]");
    print(cache.toString());
  }

  print("Hits: " + std::to_string(runner.hits()));
  print("Misses: " + std::to_string(runner.misses()));
  print("Hit ratio: " + doubleToString((double)runner.hits() /
                                       (runner.hits() + runner.misses())));
}