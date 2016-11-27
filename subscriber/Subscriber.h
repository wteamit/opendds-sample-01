#ifndef SUBSCRIBER_H_
#define SUBSCRIBER_H_

#include "idl/TopicsTypeSupportImpl.h"
#include <dds/DCPS/Service_Participant.h>
#include <functional>

class Subscriber {
public:

  Subscriber(int argc, char* argv[]);
  ~Subscriber();
  void setReceivedTopicFunction(std::function<void (const TopicSample::Message&)> tf);

private:

  void createParticipant(int argc, char* argv[]);
  void createSubscriber();
  void registerTopic();
  void createDataReader();

private:

  DDS::DomainParticipantFactory_var m_participantFactory;
  DDS::DomainParticipant_var m_participant;
  DDS::Subscriber_var m_subscriber;
  TopicSample::MessageTypeSupport_var m_topicSupport;
  DDS::Topic_var m_messageTopic;
  DDS::DataReaderListener_var m_listener;
  DDS::TopicQos m_defaultQoS;
};

#endif // !SUBSCRIBER_H_
