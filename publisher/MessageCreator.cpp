#include "MessageCreator.h"
#include <random>

///////////////////////////////////////////////////////////////////////////////
// USING SECTION                                                             //
///////////////////////////////////////////////////////////////////////////////

using std::string;
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;

///////////////////////////////////////////////////////////////////////////////
// CONSTANTS SECTION                                                         //
///////////////////////////////////////////////////////////////////////////////

const string s1{ "Hello" };
const string s2{ "I'm a nice message" };
const string s3{ "Good Morning!!!" };

///////////////////////////////////////////////////////////////////////////////
// PUBLIC SECTION                                                            //
///////////////////////////////////////////////////////////////////////////////

MessageCreator::MessageCreator() :
  m_messages{ s1, s2, s3 } {

}

const string& MessageCreator::getRandomMessage() const {
  random_device randomDevice;
  mt19937 generator(randomDevice());
  uniform_int_distribution<size_t> distribution(0, m_messages.size() - 1);

  return m_messages.at(distribution(generator));
}