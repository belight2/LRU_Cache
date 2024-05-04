#ifndef TASK_H
#define TASK_H

#include <fstream>
#include <string>

// 태스크의 종류
enum TaskType { MULTIPLY, PALINDROME };

// 태스크에 대한 설명을 담는 구조체
struct Task {
  TaskType type;
  std::string filename;
};

// 태스크를 읽어오기 위한 클래스
class TaskSet {
private:
  std::ifstream file_;

public:
  TaskSet(std::string filename) { file_.open(filename); }
  ~TaskSet() { file_.close(); }

  // 다음 태스크를 읽어 task 객체에 저장하고 true를 반환한다
  // 태스크가 없는 경우 false를 반환한다
  bool getNext(Task &task) {
    if (file_.eof())
      return false;

    std::string typeText;
    file_ >> typeText;

    if (typeText == "multiply") {
      task.type = MULTIPLY;
    } else if (typeText == "palindrome") {
      task.type = PALINDROME;
    } else {
      return getNext(task);
    }

    file_ >> task.filename;
    return true;
  }
};

#endif