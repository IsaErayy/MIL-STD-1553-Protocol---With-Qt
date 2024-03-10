#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
QT_BEGIN_NAMESPACE

class QWidget;
class QVBoxlayout;
class QHBoxlayout;
class QFormLayout;
class QSpinBox;
class QPushbuton;
class QGridLayout;
class QComboBox;
class QLabel;
class QGroupBox;

QT_END_NAMESPACE

union commandWordFrame{

    struct Fields{
        unsigned int remoteTerminal_label_bit : 5;
        unsigned int Tx_Rx_label_bit : 1;
        unsigned int subAddress_label_bit : 5;
        unsigned int dataWordCount_label_bit : 5;

    }fields;

    unsigned int commandWord_label_value;

};



class Window : public QWidget {

    Q_OBJECT

public:
    Window(QWidget *parent = nullptr);

signals:
    void commandFrameValueChanged(unsigned int value);

public slots:
    void updateCommandWordValue();

private:
    void communicationType();
    void commandWordLabel();
    void dataWordLabel();
    void remoteTerminals();


    //Communcation Type variables
    QGroupBox* Group1;
    QLabel* communication_type_label;
    QComboBox* communcation_type_label_combobox;

    //Command Word Label
    QGroupBox* Group2;
    QLabel* command_word_label1;
    QLabel* command_word_label2;
    QLabel* command_word_label3;
    QLabel* command_word_label4;
    QLabel* command_word_label5;


    QSpinBox* command_word_spinbox1;
    QSpinBox* command_word_spinbox2;
    QSpinBox* command_word_spinbox3;
    QComboBox* command_word_combobox1;

    //Data word label
    QGroupBox* Group3 ;
    QSpinBox* data_word_spinbox1;
    QLabel* data_word_label;

    //Remote terminal address gösterme
    QGroupBox* Group4;

};

#endif // WINDOW_H
