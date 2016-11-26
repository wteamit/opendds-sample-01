#include "MessageDataReaderListenerImpl.h"
#include "idl/TopicsTypeSupportC.h"
#include "idl/TopicsTypeSupportImpl.h"
#include <dds/DCPS/Service_Participant.h>
#include <ace/streams.h>

///////////////////////////////////////////////////////////////////////////////
// PUBLIC SECTION                                                            //
///////////////////////////////////////////////////////////////////////////////

void MessageDataReaderListenerImpl::on_data_available(DDS::DataReader_ptr reader) {
  try {
    TopicSample::MessageDataReader_var Message_dr
      = TopicSample::MessageDataReader::_narrow(reader);
    if (CORBA::is_nil (Message_dr.in ())) {
      cerr << "MessageDataReaderListenerImpl::on_data_available: _narrow failed." << endl;
      ACE_OS::exit(1);
    }

    int count = 0;
    while(true) {
      TopicSample::Message Message;
      DDS::SampleInfo si ;
      DDS::ReturnCode_t status = Message_dr->take_next_sample(Message, si) ;

      if (status == DDS::RETCODE_OK && si.valid_data) {
        ++count;
        cout << "Message: counter = " << Message.counter    << endl
             << "         message = " << Message.m.in()  << endl;;
      } else if (status == DDS::RETCODE_NO_DATA) {
        cerr << "INFO: reading complete after " << count << " samples." << endl;
        break;
      } else {
        cerr << "ERROR: read Message: Error: " <<  status << endl;
      }
    }

  } catch (CORBA::Exception& e) {
    cerr << "Exception caught in read:" << endl << e << endl;
    ACE_OS::exit(1);
  }
}

void MessageDataReaderListenerImpl::on_requested_deadline_missed (
    DDS::DataReader_ptr,
    const DDS::RequestedDeadlineMissedStatus &)
  throw (CORBA::SystemException)
{
  cerr << "MessageDataReaderListenerImpl::on_requested_deadline_missed" << endl;
}

void MessageDataReaderListenerImpl::on_requested_incompatible_qos (
    DDS::DataReader_ptr,
    const DDS::RequestedIncompatibleQosStatus &)
  throw (CORBA::SystemException)
{
  cerr << "MessageDataReaderListenerImpl::on_requested_incompatible_qos" << endl;
}

void MessageDataReaderListenerImpl::on_liveliness_changed (
    DDS::DataReader_ptr,
    const DDS::LivelinessChangedStatus &)
  throw (CORBA::SystemException)
{
  cerr << "MessageDataReaderListenerImpl::on_liveliness_changed" << endl;
}

void MessageDataReaderListenerImpl::on_subscription_matched (
    DDS::DataReader_ptr,
    const DDS::SubscriptionMatchedStatus &)
  throw (CORBA::SystemException)
{
  cerr << "MessageDataReaderListenerImpl::on_subscription_matched" << endl;
}

void MessageDataReaderListenerImpl::on_sample_rejected(
    DDS::DataReader_ptr,
    const DDS::SampleRejectedStatus&)
  throw (CORBA::SystemException)
{
  cerr << "MessageDataReaderListenerImpl::on_sample_rejected" << endl;
}

void MessageDataReaderListenerImpl::on_sample_lost(
  DDS::DataReader_ptr,
  const DDS::SampleLostStatus&)
  throw (CORBA::SystemException)
{
  cerr << "MessageDataReaderListenerImpl::on_sample_lost" << endl;
}
