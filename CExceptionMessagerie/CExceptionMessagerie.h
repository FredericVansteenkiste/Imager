#ifndef CEXCEPTIONMESSAGERIE_H
#define CEXCEPTIONMESSAGERIE_H

#include <exception>
#include <QtWidgets>

class CExceptionMessagerie : public std::exception
{
public:
   CExceptionMessagerie(const QIcon& qIcone,
                        const QString& qstrMsg,
                        const char* pcNameFile,
                        const int& iLine);
   virtual ~CExceptionMessagerie();

   virtual const char* what(void) const throw();

   const QString& qstrExceptionMessage(void) const throw();
   const QIcon&   qIcone(void) const throw();

private:
   QIcon       m_qIcone;
   QString     m_qstrExceptionMessage;
   std::string m_strWhatMsg;
};

#endif // CEXCEPTIONMESSAGERIE_H
