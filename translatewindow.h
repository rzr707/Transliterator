/**
  Класс окна транслитерации
*/

#ifndef TRANSLATEWINDOW_H
#define TRANSLATEWINDOW_H

#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QTextEdit>
#include <QBoxLayout>
#include <QChar>
#include <QFocusEvent>
#include <QDebug>
#include <QSplitter>
#include <QPushButton>
#include <QStyle>
#include <QIcon>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QByteArray>
#include <QMessageBox>
#include "transliterations.h"

class TranslateWindow : public QWidget {
    Q_OBJECT
private:
    QTextEdit*       m_pte;
    QComboBox*       m_pcb;
    QComboBox*       m_pcbRusStd;
    QComboBox*       m_pcbUkrStd;
    TranslateWindow* m_pTw;  //указатель на второе окно
    bool             m_bIsActive;

public:
    TranslateWindow(QWidget* pwgt = 0);
    void    setActive(bool b);
    bool    bindWindows(TranslateWindow* pwnd);
    QString getText();
    void    setText(const QString& str);
    QString transliterate(const QString& str, QString strGostRus[33]);
    QString transliterateUkr(const QString& str, QString strUkrGost[34]);
    QString transliterateEngRus(const QString &str, QString strGost[33]);
    QString transliterateEngUa(const QString &str, QString strGost[34]);
    void    setIndex(int nIndex);
    int     getIndex();
    void    setGostIndex(int nRusIndex, int nUkrIndex);
    int     getGostIndexRus();
    int     getGostIndexUkr();
    void    activate(int nIndex);

public slots:
    void    slotLangActivated(int nLang);
    void    slotOnTextChanged();
};



#endif // TRANSLATEWINDOW_H

