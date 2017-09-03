#include "mainwindow.h"

/*Конструктор главного окна приложения, инициализация кнопок, ползунков и окон транслитерации*/
MainWindow::MainWindow(QWidget* pwgt/*= 0*/): QWidget(pwgt) {
	
    m_pLwnd       = new TranslateWindow;
    m_pRwnd       = new TranslateWindow;
    m_pSpl        = new QSplitter;

    m_pcmdSwap      = new QPushButton;
    m_pcmdSwap->setIcon(style()->standardIcon(QStyle::SP_BrowserReload));
    m_pcmdSwap->setFixedSize(25, 25);
    m_pcmdSwap->setToolTip("Поменять окна местами");

    m_pcmdSaveLtext = new QPushButton;
    m_pcmdSaveLtext->setIcon(style()->standardIcon(QStyle::SP_DialogSaveButton));
    m_pcmdSaveLtext->setFixedSize(20, 20);
    m_pcmdSaveLtext->setToolTip("Сохранить в файл..");

    m_pcmdOpenLtext = new QPushButton;
    m_pcmdOpenLtext->setIcon(style()->standardIcon(QStyle::SP_DirOpenIcon));
    m_pcmdOpenLtext->setFixedSize(20, 20);
    m_pcmdOpenLtext->setToolTip("Загрузить текстовый файл..");

    m_pcmdSaveRtext = new QPushButton;
    m_pcmdSaveRtext->setIcon(style()->standardIcon(QStyle::SP_DialogSaveButton));
    m_pcmdSaveRtext->setFixedSize(20, 20);
    m_pcmdSaveRtext->setToolTip("Сохранить в файл..");

    m_pcmdOpenRtext = new QPushButton;
    m_pcmdOpenRtext->setIcon(style()->standardIcon(QStyle::SP_DirOpenIcon));
    m_pcmdOpenRtext->setFixedSize(20, 20);
    m_pcmdOpenRtext->setToolTip("Загрузить текстовый файл..");

    m_pRwnd->setIndex(2);

    m_pLwnd->bindWindows(m_pRwnd);
    m_pLwnd->activate(0);
    m_pLwnd->setActive(true);

    m_pSpl->addWidget(m_pLwnd);
    m_pSpl->addWidget(m_pRwnd);

    connect(m_pcmdSwap, SIGNAL(clicked(bool)),
            this,     SLOT(slotOnSwapClicked())
            );
    connect(m_pcmdSaveLtext, SIGNAL(clicked(bool)),
            this,          SLOT(slotOnSaveFileClicked())
            );
    connect(m_pcmdSaveRtext, SIGNAL(clicked(bool)),
            this,          SLOT(slotOnSaveFileClicked())
            );
    connect(m_pcmdOpenLtext, SIGNAL(clicked(bool)),
            this,            SLOT(slotOnOpenFileClicked())
            );
    connect(m_pcmdOpenRtext, SIGNAL(clicked(bool)),
            this,            SLOT(slotOnOpenFileClicked())
            );
    connect(m_pSpl, SIGNAL(splitterMoved(int,int)),
            this,       SLOT(slotMoveSwapBtn(int, int))
            );

    // layout setup
    QVBoxLayout* pMainL = new QVBoxLayout;
    QHBoxLayout* phbButtonsL = new QHBoxLayout;
    phbButtonsL->addWidget(m_pcmdSaveLtext, Qt::AlignLeft);
    phbButtonsL->addWidget(m_pcmdOpenLtext, Qt::AlignLeft);
    phbButtonsL->addWidget(m_pcmdSwap, 1 ,Qt::AlignHCenter);
    phbButtonsL->addWidget(m_pcmdOpenRtext, Qt::AlignRight);
    phbButtonsL->addWidget(m_pcmdSaveRtext, Qt::AlignRight);
    pMainL->addWidget(m_pSpl);
    pMainL->addLayout(phbButtonsL);
    setLayout(pMainL);
    resize(840, 480);

}

// двигает кнопку вместе со слайдером
void MainWindow::slotMoveSwapBtn(int w, int) {
   m_pcmdSwap->move(w, m_pcmdSwap->pos().y());
   repaint();
}

/* Слот меняет окна местами */
void MainWindow::slotOnSwapClicked() {
	
    qDebug() << "slotOnSwapClicked";
    if(m_pLwnd->getIndex() == m_pRwnd->getIndex()) {
        return;
    }
    int nTemp = m_pLwnd->getIndex();
    m_pLwnd->setIndex(m_pRwnd->getIndex());
    m_pRwnd->setIndex(nTemp);

    QString strTemp = m_pLwnd->getText();
    m_pLwnd->setText(m_pRwnd->getText());
    m_pRwnd->setText(strTemp);

    int nGostTempRus = m_pLwnd->getGostIndexRus();
    int nGostTempUkr = m_pLwnd->getGostIndexUkr();

    m_pLwnd->setGostIndex(m_pRwnd->getGostIndexRus(),
                          m_pRwnd->getGostIndexUkr()
                          );
    m_pRwnd->setGostIndex(nGostTempRus,
                          nGostTempUkr
                          );

    m_pLwnd->activate(m_pLwnd->getIndex());
    m_pRwnd->activate(m_pRwnd->getIndex());

}

// Чтение из файла
void MainWindow::slotOnOpenFileClicked() {
	
    qDebug() << "slotOnOpenFileClicked";
    // устанавливается указатель на окно, которое запросило чтение из файла:
    TranslateWindow* pWnd = (sender() == m_pcmdOpenLtext ? m_pLwnd : m_pRwnd);
    QString strFileToOpen = QFileDialog::getOpenFileName(this,
                                                         "Открыть файл..",
                                                         qApp->applicationDirPath(),
                                                         "Текстовый файл (*.txt)"
                                                         );
    if(strFileToOpen.isEmpty()) {
        return;
    }
    QFile file(strFileToOpen);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    QTextStream tStream(&file);
    QString str = tStream.readAll();
    pWnd->setText(str);

}

// Сохранение в файл
void MainWindow::slotOnSaveFileClicked() {
	
    qDebug() << "slotOnSaveFileClicked";
     // устанавливается указатель на окно, которое запросило сохранение текста в файл:
    TranslateWindow* pWnd = (sender() == m_pcmdSaveLtext ? m_pLwnd : m_pRwnd);
    QString strFileToSave = QFileDialog::getSaveFileName(this,
                                                         "Сохранить в файл..",
                                                         qApp->applicationDirPath(),
                                                         "Текстовый файл (*.txt)"
                                                         );
    if(strFileToSave.isEmpty()) {
        return;
    }
    QFile file(strFileToSave);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this,
                              "Ошибка",
                              "Не могу открыть файл "
                              + strFileToSave.mid(strFileToSave.lastIndexOf("."))
                              );
        return;
    }
    QTextStream tStream(&file);
    for(int i = 0; i < pWnd->getText().length(); ++i) {
        tStream << pWnd->getText().at(i);
    }
    file.close();

    qDebug() << "file path: " << strFileToSave;
}
