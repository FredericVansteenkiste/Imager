#ifndef CEXCEPTION_H
#define CEXCEPTION_H

#include <exception>
#include <QtWidgets>

class CException : public std::exception
{
public:
   explicit CException(const QString& qstrMsg,
                       const char* pcNameFile,
                       const int& iLine);
   virtual ~CException();

   virtual const char* what(void) const noexcept;

private:
   std::string m_strWhatMsg;
};

#endif // CEXCEPTIONMESSAGERIE_H
