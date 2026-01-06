#include "Serialization/Serializer.h"

namespace MEngine
{

namespace Core
{

MSerializerErrorState::MSerializerErrorState()
  : m_errorMsg{}
  , m_bIsError{false}
{ }

MSerializerErrorState::MSerializerErrorState(const MSerializerErrorState& Other) = default;
MSerializerErrorState& MSerializerErrorState::operator=(const MSerializerErrorState& Other) = default;

MSerializerErrorState::~MSerializerErrorState()
{
  Reset();
}

void MSerializerErrorState::Reset()
{
  m_errorMsg.clear();
  m_bIsError = false;
}

void MSerializerErrorState::SetError(IN const std::string& ErrorMsg)
{
  m_errorMsg = ErrorMsg;
  m_bIsError = true;
}

} // namespace MEngine::Core

} // namespace MEngine