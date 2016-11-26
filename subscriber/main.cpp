#include "Subscriber.h"
#include <iostream>
#include <chrono>
#include <thread>

int main(int argv, char* argc[]) {

  using namespace std::chrono_literals;

  const auto sleepTime { 1s };
  std::cout << "=== SUBSCRIBER ===" << std::endl;

  Subscriber subscriber(argv, argc);

  std::cout << "Subscriber: waiting for events" << std::endl;

  while (true) {
    std::this_thread::sleep_for(sleepTime);
  }

  return 0;
}
