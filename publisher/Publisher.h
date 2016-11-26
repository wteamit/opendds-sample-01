#ifndef PUBLISHER_H_
#define PUBLISHER_H_

#include "idl/TopicsTypeSupportImpl.h"
#include <dds/DCPS/Service_Participant.h>
#include <string>

class Publisher {
public:

  Publisher(int argc, char* argv[]);
  ~Publisher();

  bool connectToDDS();
  void sendMessage(const std::string& message);

private:

  void createParticipant(int argc, char* argv[]);
  void createPublisher();
  void registerTopic();
  void createDataWriter();

private:

  DDS::DomainParticipantFactory_var m_participantFactory;
  DDS::DomainParticipant_var m_participant;
  DDS::Publisher_var m_publisher;
  TopicSample::MessageTypeSupport_var m_topicSupport;
  DDS::Topic_var m_messageTopic;
  TopicSample::MessageDataWriter_var m_dataWriter;
  DDS::InstanceHandle_t m_topicHandler;
  int m_counter = 1;
};

#endif // !PUBLISHER_H_
