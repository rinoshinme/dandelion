#include "logindlg.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

LoginDlg::LoginDlg(QWidget* parent)
    :QDialog(parent)
{
    QLabel* usrLabel = new QLabel("User: ", this);
    QLabel* pwdLabel = new QLabel("password: ", this);
    m_usrLineEdit = new QLineEdit(this);
    m_pwdLineEdit = new QLineEdit(this);
    m_pwdLineEdit->setEchoMode(QLineEdit::NoEcho);
    QGridLayout* gLayout = new QGridLayout;
    gLayout->addWidget(usrLabel, 0, 0, 1, 1);
    gLayout->addWidget(pwdLabel, 1, 0, 1, 1);
    gLayout->addWidget(m_usrLineEdit, 0, 1, 1, 3);
    gLayout->addWidget(m_pwdLineEdit, 1, 1, 1, 3);
    
    QPushButton* okBtn = new QPushButton("OK", this);
    QPushButton* cancelBtn = new QPushButton("Cancel", this);
    QHBoxLayout* hLayout = new QHBoxLayout;
    hLayout->setSpacing(60);
    hLayout->addWidget(okBtn);
    hLayout->addWidget(cancelBtn);
    
    QVBoxLayout* vLayout = new QVBoxLayout;
    vLayout->setMargin(40);
    vLayout->addLayout(gLayout);
    vLayout->addStretch(40);
    vLayout->addLayout(hLayout);
    setLayout(vLayout);
    
    connect(okBtn, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancelBtn, SIGNAL(clicked()), this, SLOT(reject()));
    
    setWindowTitle("Login");
    resize(300, 200);
}

void LoginDlg::accept()
{
    if ((m_usrLineEdit->text().trimmed() == QObject::tr("admin")) &&
            (m_pwdLineEdit->text() == QObject::tr("123456")))
    {
        QDialog::accept();
    }
    else
    {
        QMessageBox::warning(this, "Warning", "Invalid input",
                             QMessageBox::Yes);
        m_usrLineEdit->setFocus();
    }
}
