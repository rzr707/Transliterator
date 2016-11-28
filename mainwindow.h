/**
  Класс главного окна приложения
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "translatewindow.h"

class MainWindow : public QWidget {
    Q_OBJECT
private:
    QSplitter*       m_pSpl;          //разделитель
    TranslateWindow* m_pLwnd;         //левое окно
    TranslateWindow* m_pRwnd;         //правое окно
    QPushButton*     m_pcmdSwap;      //кнопка обмена окон
    QPushButton*     m_pcmdSaveLtext; //сохранить левая кн
    QPushButton*     m_pcmdOpenLtext; //открыть левая кн
    QPushButton*     m_pcmdSaveRtext; //сохранить правая кн
    QPushButton*     m_pcmdOpenRtext; //открыть правая кн

public:
    MainWindow(QWidget* pwgt = 0);

public slots:
    void slotMoveSwapBtn(int w, int h);
    void slotOnSwapClicked();
    void slotOnOpenFileClicked();
    void slotOnSaveFileClicked();

};


#endif // MAINWINDOW_H

