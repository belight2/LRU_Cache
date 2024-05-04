#ifndef TASK_RUNNER_H
#define TASK_RUNNER_H

#include <fstream>
#include <iostream>
#include <string>

// 작업을 수행하기 위해 사용하는 클래스
class TaskRunner {
private:
  // 문자열이 팰린드롬인지 검사한다
  static bool isPalindrome(std::string str) {
    for (int i = 0; i < str.size() / 2; i++) {
      if (str[i] != str[str.size() - i - 1]) {
        return false;
      }
    }
    return true;
  }

public:
  // 파일의 숫자를 전부 곱하여 반환한다
  static double multiply(std::string filename) {
    std::ifstream file(filename);
    double result = 1;
    double number;
    while (file >> number) {
      result *= number;
    }
    return result;
  }

  // 파일에서 가장 긴 팰린드롬을 찾아 인덱스를 반환한다
  static int palindrome(std::string filename) {
    std::ifstream file(filename);
    std::string fullText;
    std::string line;
    while (std::getline(file, line)) {
      fullText += line;
    }

    int maxLength = 0;
    int maxIndex = 0;
    std::string maxPalindrome;

    for (int i = 0; i < fullText.size(); i++) {
      for (int j = i + 1; j < fullText.size(); j++) {
        std::string sub = fullText.substr(i, j - i + 1);
        if (isPalindrome(sub) && sub.size() > maxLength) {
          maxLength = sub.size();
          maxIndex = i;
          maxPalindrome = sub;
        }
      }
    }

    return maxIndex;
  }
};

#endif