#include "Subscriber.h"
#include "MessageDataReaderListenerImpl.h"
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

Subscriber::Subscriber(int argc, char* argv[]) {
  createParticipant(argc, argv);
  createSubscriber();
  registerTopic();
  createDataReader();
}

Subscriber::~Subscriber() {
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

///////////////////////////////////////////////////////////////////////////////
// PRIVATE SECTION                                                           //
///////////////////////////////////////////////////////////////////////////////

void Subscriber::createParticipant(int argc, char* argv[]) {
  auto m_participantFactory = TheParticipantFactoryWithArgs(argc, argv);

  m_participant = m_participantFactory->create_participant(
    DomainID,
    PARTICIPANT_QOS_DEFAULT,
    DDS::DomainParticipantListener::_nil(),
    ::OpenDDS::DCPS::DEFAULT_STATUS_MASK
  );

  if (CORBA::is_nil (m_participant.in ())) {
      cerr << "Publisher: Failed to create participant..." << endl;
  } else {
    cout << "Publisher: participant created successfully" << endl;
  }
}

void Subscriber::createSubscriber() {
  m_subscriber = m_participant->create_subscriber(
    SUBSCRIBER_QOS_DEFAULT,
    DDS::SubscriberListener::_nil(),
    ::OpenDDS::DCPS::DEFAULT_STATUS_MASK
  );
  if (CORBA::is_nil (m_subscriber.in ())) {
    cerr << "createSubscriber failed." << endl;
  } else {
    cout << "createSubscriber ok." << endl;
  }
}

void Subscriber::registerTopic() {
  m_topicSupport = new TopicSample::MessageTypeSupportImpl();

    if (DDS::RETCODE_OK != m_topicSupport->register_type(
      m_participant.in(),
      MessageType)
    ) {
      cerr << "Cration of register_type for " << MessageType << " failed." << endl;
    }
    DDS::TopicQos defaultQoS;
    m_participant->get_default_topic_qos(defaultQoS);
    m_messageTopic = m_participant->create_topic (
      MessageTopic,
      MessageType,
      defaultQoS,
      DDS::TopicListener::_nil(),
      ::OpenDDS::DCPS::DEFAULT_STATUS_MASK
    );
    if (CORBA::is_nil (m_messageTopic.in ())) {
      cerr << "Creation of create_topic for " << MessageTopic << " failed." << endl;
    }
}

void Subscriber::createDataReader() {
 m_listener = new MessageDataReaderListenerImpl;
 auto listenerServant = dynamic_cast<MessageDataReaderListenerImpl*>(m_listener.in());

  if (CORBA::is_nil (m_listener.in ())) {
    cerr << "ExchangeEvent listener is nil." << endl;
  }
  DDS::DataReaderQos defaultQoS;
  m_subscriber->get_default_datareader_qos (defaultQoS);

  DDS::DataReader_var quote_dr = m_subscriber->create_datareader(
    m_messageTopic.in (),
    defaultQoS,
    m_listener.in (),
    ::OpenDDS::DCPS::DEFAULT_STATUS_MASK
  );
}
