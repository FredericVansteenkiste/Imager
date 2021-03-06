#include "CExceptionMessagerie.h"

CExceptionMessagerie::CExceptionMessagerie(const QIcon& qIcone,
                                           const QString& qstrMsg,
                                           const char* pcNameFile,
                                           const int& iLine):
                                                m_qIcone(qIcone),
                                                m_qstrExceptionMessage(qstrMsg),
                                                m_strWhatMsg()
{
   m_strWhatMsg =   qstrMsg.toStdString() + " : " + pcNameFile + " at line "
                  + std::to_string(iLine);
}

CExceptionMessagerie::~CExceptionMessagerie()
{
}

const char* CExceptionMessagerie::what() const noexcept
{
   return m_strWhatMsg.c_str();
}

const QString& CExceptionMessagerie::qstrExceptionMessage(void) const noexcept
{
   return m_qstrExceptionMessage;
}

const QIcon& CExceptionMessagerie::qIcone(void) const noexcept
{
   return m_qIcone;
}
