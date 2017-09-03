#include "translatewindow.h"

    TranslateWindow::TranslateWindow(QWidget* pwgt/*=0*/) : QWidget(pwgt),
                                                            m_pTw(nullptr),
                                                            m_bIsActive(false) // второе окно пассивное (правое)
    {
        m_pte = new QTextEdit(this);
        m_pcb = new QComboBox(this);

        m_pcb->addItem("Русский",    0);
        m_pcb->addItem("Украинский", 1);
        m_pcb->addItem("Английский", 2);
        m_pcb->setCurrentIndex(0);

        m_pcbRusStd = new QComboBox(this);
        m_pcbRusStd->addItem("ALA-LC", 0);
        m_pcbRusStd->addItem("ГОСТ 7.79-2000А", 1);
        m_pcbRusStd->addItem("ГОСТ 16876-71-2", 2);
        m_pcbRusStd->setToolTip("Стандарт транслитерации");
        m_pcbRusStd->setVisible(false);

        m_pcbUkrStd = new QComboBox(this);
        m_pcbUkrStd->addItem("КМУ 2010", 0);
        m_pcbUkrStd->addItem("BGN/PCGN 1965", 1);
        m_pcbUkrStd->addItem("УКППТ 1996", 2);
        m_pcbUkrStd->setToolTip("Стандарт транслитерации");
        m_pcbUkrStd->setVisible(false);

        connect(m_pte, SIGNAL(textChanged()),
                this,  SLOT(slotOnTextChanged())
                );
        connect(m_pcb, SIGNAL(activated(int)),
                this , SLOT(slotLangActivated(int))
                );

        //setup layout
        QHBoxLayout* phbl = new QHBoxLayout;
        phbl->addWidget(m_pcb);
        phbl->addWidget(m_pcbRusStd);
        phbl->addWidget(m_pcbUkrStd);
        QVBoxLayout* pVMainLayout = new QVBoxLayout;
        pVMainLayout->addLayout(phbl);
        pVMainLayout->addWidget(m_pte);
        setLayout(pVMainLayout);

        //this->setFocusProxy()
    }

    // активное окно
    void TranslateWindow::setActive(bool b) {  m_bIsActive = b; }

    // связать окна
    bool TranslateWindow::bindWindows(TranslateWindow* pwnd) {
		
        m_pTw = pwnd;
        return true;
		
    }

    // получить текст окна
    QString TranslateWindow::getText() { return m_pte->toPlainText(); }

    // установить текст окна
    void TranslateWindow::setText(const QString& str) { m_pte->setText(str); }

    // rus-eng tr
    QString TranslateWindow::transliterate(const QString& str, QString strGostRus[33]) {
		
        QString result;
        for(int i = 0; i < str.length(); ++i) {
                if(m_pTw->getIndex() != 2) {
                    result.push_back(str.at(i));
                    continue;
                }
                int nIndex = strRusTranslate.indexOf(str.at(i).toLower());
                result.push_back( ( nIndex != -1 ?
                                 strGostRus[nIndex] :
                                 str.at(i) )
                                 );
                if(str.at(i).isUpper()) { // для того, чтобы при заглавных английских не вылетало
                    if(nIndex != -1) {
                    result.chop(strGostRus[nIndex].length());

                    /* Добавил ветвление else, если длина заменяемого символа > 1 */
                    if(strGostRus[nIndex].length() == 1) {
                        result.push_back(strGostRus[nIndex].toUpper());
                        } else {
                        result.push_back(strGostRus[nIndex]);
                        result.replace(result.length() - strGostRus[nIndex].length(),
                                       1,
                                       strGostRus[nIndex].at(0).toUpper()
                                       );//
                        }

                    }
                }
        }
        return result;
    }

    // ukr-eng tr
    QString TranslateWindow::transliterateUkr(const QString& str, QString strUkrGost[34]) {
		
        QString result;
        for(int i = 0; i < str.length(); ++i) {
                if(m_pTw->getIndex() != 2) {
                    result.push_back(str.at(i));
                    continue;
                }
                int nIndex = strUkrTranslate.indexOf(str.at(i).toLower());
                result.push_back( ( nIndex != -1 ?
                                 strUkrGost[nIndex] :
                                 str.at(i) )
                                );

                // заглавные буквы
                if(str.at(i).isUpper() ) {
                    if(nIndex != -1) {
                    result.chop(strUkrGost[nIndex].length());
                        if(strUkrGost[nIndex].length() == 1) {
                            result.push_back(strUkrGost[nIndex].toUpper());
                        } else {
                            result.push_back(strUkrGost[nIndex]);
                            result.replace(result.length() - strUkrGost[nIndex].length(),
                                           1,
                                           strUkrGost[nIndex].at(0).toUpper()
                                           );
                        }

                    }
                }


        }
        return result;
    }

    // eng-rus tr
    QString TranslateWindow::transliterateEngRus(const QString &str, QString strGost[33]) {
		
        if(!str.trimmed().length()) {
            return "";
        }

        QString result = str;
        QString arrGost[33];
        for(int i = 0; i < 33; ++i) {
            arrGost[i] = strGost[i];
            arrGost[i].replace(0,
                               1,
                               arrGost[i].at(0).toUpper()
                               );
        }

        /* Две буквы переводятся вне очереди */
        result.replace(strGost[7], strRusTranslate.at(7));
        result.replace(arrGost[7], strRusTranslate.at(7).toUpper());
        result.replace(strGost[6], strRusTranslate.at(6));
        result.replace(arrGost[6], strRusTranslate.at(6).toUpper());
        /* Метод: поочерёдно заменить все ангийские совпадения на русские*/
        for(int i = 32; i >= 0; --i) {
                result.replace(strGost[i], strRusTranslate.at(i));
                result.replace(arrGost[i], strRusTranslate.at(i).toUpper());
        }

        return result;
    }

    // eng-ua tr
    QString TranslateWindow::transliterateEngUa(const QString &str, QString strGost[34]) {
		
        if(!str.trimmed().length()) {
           return "";
        }

        QString arrGost[34];
        for(int i = 0; i < 34; ++i) {
            arrGost[i] = strGost[i];
            arrGost[i].replace(0,
                               1,
                               arrGost[i].at(0).toUpper()
                               );
        }

        QString result = str;

        /* Данные буквы переводятся вне очереди */

        result.replace(strGost[29], strUkrTranslate.at(29)); //
        result.replace(arrGost[29], strUkrTranslate.at(29).toUpper()); //
        result.replace(strGost[28], strUkrTranslate.at(28)); //
        result.replace(arrGost[28], strUkrTranslate.at(28).toUpper()); //
        result.replace(strGost[27], strUkrTranslate.at(27)); //
        result.replace(arrGost[27], strUkrTranslate.at(27).toUpper()); //

        result.replace(strGost[8], strUkrTranslate.at(8)); //
        result.replace(arrGost[8], strUkrTranslate.at(8).toUpper()); //
        result.replace(strGost[7], strUkrTranslate.at(7)); //
        result.replace(arrGost[7], strUkrTranslate.at(7).toUpper()); //
        result.replace(strGost[3], strUkrTranslate.at(3)); //
        result.replace(arrGost[3], strUkrTranslate.at(3).toUpper()); //
        result.replace(strGost[12], strUkrTranslate.at(12)); //
        result.replace(arrGost[12], strUkrTranslate.at(12).toUpper()); //

        /* Метод: поочерёдно заменить все ангийские совпадения на украинские */
        for(int i = 33; i >= 0; --i) {
            result.replace(strGost[i], strUkrTranslate.at(i));
            result.replace(arrGost[i], strUkrTranslate.at(i).toUpper());
        }

        // Если первая буква - "й", в остальных случаях "и"
        for(int i = 0; i < result.length(); ++i) {
            if(result.at(i) == strUkrTranslate.at(13)) {
                if(result.length() >= 2 && i) {
                    if(result.at(i-1).isLetter() ) {
                        result.replace(i, 1, strUkrTranslate.at(10)) ;
                    }
                }
            }
        }

        return result;
    }

    // установить индекс стандарта транслитерации
    void TranslateWindow::setIndex(int nIndex) { m_pcb->setCurrentIndex(nIndex); }

    // получить индекс стандарта транслитерации
    int TranslateWindow::getIndex() { return m_pcb->currentIndex(); }

    // установить индекс стандартов транслитерации
    void TranslateWindow::setGostIndex(int nRusIndex, int nUkrIndex) {
		
        m_pcbRusStd->setCurrentIndex(nRusIndex);
        m_pcbUkrStd->setCurrentIndex(nUkrIndex);
		
    }

     // получить индекс стандарта русской транслитерации
    int TranslateWindow::getGostIndexRus() { return m_pcbRusStd->currentIndex(); }

    // получить индекс стандарта украинской транслитерации
    int TranslateWindow::getGostIndexUkr() { return m_pcbUkrStd->currentIndex(); }

    // активировать окно
    void TranslateWindow::activate(int nIndex) { m_pcb->activated(nIndex); }

    /* Слот делает видимыми только комбобокс выбранного языка */
    void TranslateWindow::slotLangActivated(int nLang) {
		
        m_pcbRusStd->setVisible(false);
        m_pcbUkrStd->setVisible(false);
        switch(nLang)
        {
        case 0:
            m_pcbRusStd->setVisible(true);
            break;
        case 1:
            m_pcbUkrStd->setVisible(true);
            break;
        case 2:
            m_pcbRusStd->setVisible(false);
            m_pcbUkrStd->setVisible(false);
        default:
            m_pcbRusStd->setVisible(false);
            m_pcbUkrStd->setVisible(false);
            break;
        }
		
    }

    /* Если текст в QTextEdit изменён, вызывает соотв. функцию в зависимости от выбранных языков */
    void TranslateWindow::slotOnTextChanged() {
		
        if(m_pTw == nullptr) {
            return;
        }

        switch(m_pcb->currentIndex())           // индекс комбобокса левого окна
        {
        case 0: // русский
            switch(m_pcbRusStd->currentIndex()) // индекс комбобокса госта русского
            {
            case 0: // ala-lc -> eng
                m_pTw->m_pte->setText(transliterate(m_pte->toPlainText(), strEngTranslate));
                break;
            case 1: // gost 7.79-200a -> eng
                m_pTw->m_pte->setText(transliterate(m_pte->toPlainText(), strEngTranslateGost779));
                break;
            case 2: // gost 16876-71-2 -> eng
                m_pTw->m_pte->setText(transliterate(m_pte->toPlainText(), strEngTranslateGost16878));
                break;
            }
            break;
        case 1: // украинский
            switch(m_pcbUkrStd->currentIndex())  // индекс комбобокса госта украинского
            {
            case 0: // kmu2010 -> eng
                m_pTw->m_pte->setText(transliterateUkr(m_pte->toPlainText(), strUkrEngTranslate));
                break;
            case 1: // bgn/pcgn 1965 -> eng
                m_pTw->m_pte->setText(transliterateUkr(m_pte->toPlainText(), strUkrEngBgnPcgn));
                break;
            case 2: // ukppt 1996 -> eng
                m_pTw->m_pte->setText(transliterateUkr(m_pte->toPlainText(), strUkrEngGeographical));
                break;
            }
            break;
        case 2: // английский
            switch(m_pTw->getIndex())
            {
            case 0:     // rus
                switch(m_pTw->getGostIndexRus())
                {
                case 0: // eng -> ALA-LC
                    m_pTw->m_pte->setText(transliterateEngRus(m_pte->toPlainText(), strEngTranslate));
                    break;
                case 1: // eng -> gost 7.79-2000A
                    m_pTw->m_pte->setText(transliterateEngRus(m_pte->toPlainText(), strEngTranslateGost779));
                    break;
                case 2: // eng -> gost 16876-71-2
                    m_pTw->m_pte->setText(transliterateEngRus(m_pte->toPlainText(), strEngTranslateGost16878));
                    break;
                }
                break;
            case 1:     // ukr
                switch(m_pTw->getGostIndexUkr())
                {
                case 0: // eng -> kmu2010
                    m_pTw->m_pte->setText(transliterateEngUa(m_pte->toPlainText(), strUkrEngTranslate));
                    break;
                case 1: // eng -> bgn/pcgn 1965
                    m_pTw->m_pte->setText(transliterateEngUa(m_pte->toPlainText(), strUkrEngBgnPcgn));
                    break;
                case 2: // eng -> ukppt 1996
                    m_pTw->m_pte->setText(transliterateEngUa(m_pte->toPlainText(), strUkrEngGeographical));
                    break;
                }

                break;
            case 2:
                break;
            }
            break;
        }

    }


