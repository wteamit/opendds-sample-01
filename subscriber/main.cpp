#include "Subscriber.h"
#include "idl/TopicsC.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <functional>

void printTopic(const TopicSample::Message& message) {
  static int counter = 0;
  std::cout << "Message: counter = " << message.counter << std::endl
            << "         message = " << message.m.in()  << std::endl;
}

int main(int argv, char* argc[]) {

  using namespace std::chrono_literals;
  using namespace std;

  std::function<void (const TopicSample::Message&)> topicFunction = printTopic;
  const auto sleepTime { 1s };
  cout << "=== SUBSCRIBER ===" << endl;

  Subscriber subscriber(argv, argc);
  subscriber.setReceivedTopicFunction(topicFunction);

  cout << "Subscriber: waiting for events" << endl;

  while (true) {
    this_thread::sleep_for(sleepTime);
  }

  return 0;
}
