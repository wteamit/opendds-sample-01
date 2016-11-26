#include "Publisher.h"
#include <dds/DCPS/Marked_Default_Qos.h>
#include <iostream>

///////////////////////////////////////////////////////////////////////////////
// USING SECTION                                                             //
///////////////////////////////////////////////////////////////////////////////

using std::cerr;
using std::cout;
using std::endl;

///////////////////////////////////////////////////////////////////////////////
// CONSTANTS SECTION                                                         //
///////////////////////////////////////////////////////////////////////////////

DDS::DomainId_t DomainID{ 1066 };
const char* MessageType{ "Message type" };
const char* MessageTopic{ "Message topic" };

///////////////////////////////////////////////////////////////////////////////
// PUBLIC SECTION                                                            //
///////////////////////////////////////////////////////////////////////////////

Publisher::Publisher(int argc, char* argv[]) {
  createParticipant(argc, argv);
  createPublisher();
  registerTopic();
  createDataWriter();
}

Publisher::~Publisher() {
  try {
    if (!CORBA::is_nil (m_participant.in ())) {
      m_participant->delete_contained_entities();
    }
    if (!CORBA::is_nil (m_participantFactory.in ())) {
      m_participantFactory->delete_participant(m_participant.in ());
    }
  } catch (CORBA::Exception& e) {
    cerr << "Exception caught in cleanup." << endl << e << endl;
  }
  TheServiceParticipant->shutdown();
}

bool Publisher::connectToDDS() {
  return true;
}

void Publisher::sendMessage(const std::string& message) {
  TopicSample::Message topic;
  topic.counter = m_counter++;
  topic.m = message.c_str();
  int success = m_dataWriter->write(topic, m_topicHandler);
  if (success != DDS::RETCODE_OK) {
    ACE_ERROR ((LM_ERROR, ACE_TEXT("(%P|%t) ERROR: Publisher::sendMessage write returned %d.\n"), success));
  }
}

///////////////////////////////////////////////////////////////////////////////
// PRIVATE SECTION                                                           //
///////////////////////////////////////////////////////////////////////////////

void Publisher::createParticipant(int argc, char* argv[]) {
  auto m_participantFactory = TheParticipantFactoryWithArgs(argc, argv);

  m_participant = m_participantFactory->create_participant(
      DomainID,
      PARTICIPANT_QOS_DEFAULT,
      DDS::DomainParticipantListener::_nil(),
      ::OpenDDS::DCPS::DEFAULT_STATUS_MASK);

  if (CORBA::is_nil (m_participant.in ())) {
      cerr << "Publisher: Failed to create participant..." << endl;
  } else {
    cout << "Publisher: participant created successfully" << endl;
  }
}

void Publisher::createPublisher() {
  m_publisher = m_participant->create_publisher(
    PUBLISHER_QOS_DEFAULT,
    DDS::PublisherListener::_nil(),
    ::OpenDDS::DCPS::DEFAULT_STATUS_MASK
  );
  if (CORBA::is_nil(m_publisher.in())) {
    cerr << "create_publisher failed." << endl;
  } else {
    cout << "Publisher: publisher created correctly" << endl;
  }
}

void Publisher::registerTopic() {
  m_topicSupport = new TopicSample::MessageTypeSupportImpl();
  if (DDS::RETCODE_OK != m_topicSupport->register_type(
    m_participant.in(),
    MessageType)
  ) {
    cerr << "register_type for " << MessageType << " failed." << endl;
  }
  DDS::TopicQos default_topic_qos;
  m_participant->get_default_topic_qos(default_topic_qos);
  m_messageTopic = m_participant->create_topic (
    MessageTopic,
    MessageType,
    default_topic_qos,
    DDS::TopicListener::_nil(),
    ::OpenDDS::DCPS::DEFAULT_STATUS_MASK);
  if (CORBA::is_nil (m_messageTopic.in ())) {
    cerr << "create_topic for " << MessageTopic << " failed." << endl;
  }
}

void Publisher::createDataWriter() {
  DDS::DataWriterQos dw_default_qos;
  m_publisher->get_default_datawriter_qos (dw_default_qos);
  DDS::DataWriter_var quote_base_dw =
  m_publisher->create_datawriter(
    m_messageTopic.in (),
    dw_default_qos,
    DDS::DataWriterListener::_nil(),
    ::OpenDDS::DCPS::DEFAULT_STATUS_MASK
  );
  if (CORBA::is_nil (quote_base_dw.in ())) {
    cerr << "create_datawriter for " << MessageTopic << " failed." << endl;
  }
  m_dataWriter = TopicSample::MessageDataWriter::_narrow(quote_base_dw.in());
  if (CORBA::is_nil (m_dataWriter.in ())) {
    cerr << "MessageDataWriter could not be narrowed"<< endl;
  }
  TopicSample::Message spy;
  spy.counter = 0;
  spy.m = CORBA::string_dup("SPY");
  m_topicHandler = m_dataWriter->register_instance(spy);
}
