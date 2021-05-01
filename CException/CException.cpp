#include "CException.h"

CException::CException(const QString& qstrMsg,
                       const char* pcNameFile,
                       const int& iLine):m_qstrExceptionMessage(qstrMsg),
                                         m_strWhatMsg()
{
   m_strWhatMsg =   qstrMsg.toStdString() + " : " + pcNameFile + " at line "
                  + std::to_string(iLine);
}

CException::~CException()
{
}

const char* CException::what() const noexcept
{
   return m_strWhatMsg.c_str();
}

const QString& CException::qstrExceptionMessage(void) const noexcept
{
   return m_qstrExceptionMessage;
}
