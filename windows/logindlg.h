#ifndef LOGINDLG_H
#define LOGINDLG_H

#include <QDialog>

class QLineEdit;

class LoginDlg : public QDialog
{
public:
    LoginDlg(QWidget* parent=0);
    
public slots:
    virtual void accept();
    
private:
    QLineEdit* m_usrLineEdit;
    QLineEdit* m_pwdLineEdit;
};

#endif // LOGINDLG_H
