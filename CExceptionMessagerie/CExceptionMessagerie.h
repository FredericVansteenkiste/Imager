#ifndef CEXCEPTIONMESSAGERIE_H
#define CEXCEPTIONMESSAGERIE_H

#include <exception>
#include <QtWidgets>

class CExceptionMessagerie : public std::exception
{
public:
   explicit CExceptionMessagerie(const QIcon& qIcone,
                                 const QString& qstrMsg,
                                 const char* pcNameFile,
                                 const int& iLine);
   virtual ~CExceptionMessagerie();

   virtual const char* what(void) const noexcept;

   const QString& qstrExceptionMessage(void) const noexcept;
   const QIcon&   qIcone(void) const noexcept;

private:
   QIcon       m_qIcone;
   QString     m_qstrExceptionMessage;
   std::string m_strWhatMsg;
};

#endif // CEXCEPTIONMESSAGERIE_H
