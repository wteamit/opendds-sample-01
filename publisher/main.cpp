#include "Publisher.h"
#include "MessageCreator.h"
#include <iostream>
#include <thread>
#include <chrono>

int main(int argc, char* argv[]) {

  using namespace std;
  using namespace std::chrono_literals;
  using namespace std::this_thread;

  const auto sleepTime { 1s };

  cout << "=== PUBLISHER ===" << endl;

  Publisher publisher(argc, argv);
  MessageCreator messageCreator;

  while (true) {
    sleep_for(sleepTime);
    const auto& message = messageCreator.getRandomMessage();
    cout << "Sending message: " << message << endl;
    publisher.sendMessage(message);
  }

  return 0;
}
