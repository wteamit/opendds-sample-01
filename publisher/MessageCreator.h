#ifndef MESSAGECREATOR_H_
#define MESSAGECREATOR_H_

#include <vector>
#include <string>

class MessageCreator {
public:

  MessageCreator();
  const std::string& getRandomMessage() const;

private:

  std::vector<std::string> m_messages;
};
#endif // !MESSAGECREATOR_H_
