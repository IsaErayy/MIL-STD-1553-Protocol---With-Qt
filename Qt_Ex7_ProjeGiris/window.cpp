#include "window.h"

#include <QWidget>
#include <QFormLayout>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QString>
#include <QComboBox>
#include <QGroupBox>
#include <QPalette>
#include <QLineEdit>

commandWordFrame frame;


Window::Window(QWidget *parent)
    : QWidget(parent)
{

    //Functions
    communicationType();
    commandWordLabel();
    dataWordLabel();
    remoteTerminals();

    QGridLayout* gridLayout = new QGridLayout;

    gridLayout->addWidget(Group1,0,0);
    gridLayout->addWidget(Group2,0,1);
    gridLayout->addWidget(Group3,1,0);
    gridLayout->addWidget(Group4,1,1);

    setLayout(gridLayout);
    setFixedSize(1000,600);
    setWindowTitle("MIL-STD-1553 Protocol");

}


void Window::updateCommandWordValue() {



    frame.commandWord_label_value = (command_word_spinbox1->value())  |
                                    (command_word_combobox1->currentIndex() << 5) |
                                    (command_word_spinbox2->value() << 6) |
                                    (command_word_spinbox3->value() << 11);

    // Emit the signal to notify the change
    emit commandFrameValueChanged(frame.commandWord_label_value);
}

void Window::communicationType(){

    Group1 = new QGroupBox(tr("Communication Types"));
    QPalette palette1 = QPalette();

    communication_type_label = new QLabel(tr("Choose session type :"));
    communcation_type_label_combobox = new QComboBox;
    communcation_type_label_combobox->addItem("1.BC to RT");
    communcation_type_label_combobox->addItem("2.RT to BC");
    communcation_type_label_combobox->addItem("3.RT to RT");

    palette1.setColor(QPalette::Window,QColor(255,255,0));
    communcation_type_label_combobox->setAutoFillBackground(true);
    communcation_type_label_combobox->setPalette(palette1);
    communcation_type_label_combobox->setStyleSheet("background-color :yellow;");

    QFormLayout* formLayout1 = new QFormLayout;
    formLayout1->addRow(communication_type_label, communcation_type_label_combobox);

    Group1->setLayout(formLayout1);

    QPalette palette2 = QPalette();
    //Change the background color of the group box
    palette2.setColor(QPalette::Window, QColor(173,216,230));
    Group1->setAutoFillBackground(true);
    Group1->setPalette(palette2);

    //Set the border style


}

void Window::commandWordLabel()
{
    Group2 = new QGroupBox(tr("Command Word Label"));


    command_word_label1 = new QLabel(tr("Terminal Adress Value :"));
    command_word_spinbox1 = new QSpinBox;
    command_word_spinbox1->setRange(0,31);
    command_word_spinbox1->setValue(0);

    command_word_label2 = new QLabel(tr("Tx/Rx Label: "));
    command_word_combobox1 = new QComboBox;
    command_word_combobox1->addItem("0");
    command_word_combobox1->addItem("1");

    command_word_label3 = new QLabel(tr("Subaddress Mode Value :"));
    command_word_spinbox2 = new QSpinBox;
    command_word_spinbox2->setRange(0,31);
    command_word_spinbox2->setValue(0);

    command_word_label4 = new QLabel(tr("Data Word Count Value :"));
    command_word_spinbox3 = new QSpinBox;
    command_word_spinbox3->setRange(0,31);
    command_word_spinbox3->setValue(0);

    // Connect spin box and combo box signals to update commandWord_label_value
    connect(command_word_spinbox1, QOverload<int>::of(&QSpinBox::valueChanged),
            this, [=](int value) { updateCommandWordValue(); });

    connect(command_word_combobox1, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, [=](int index) { updateCommandWordValue(); });

    connect(command_word_spinbox2, QOverload<int>::of(&QSpinBox::valueChanged),
            this, [=](int value) { updateCommandWordValue(); });

    connect(command_word_spinbox3, QOverload<int>::of(&QSpinBox::valueChanged),
            this, [=](int value) { updateCommandWordValue(); });

    command_word_label5 = new QLabel(tr("Command Word Value :"));
    QLineEdit* command_word_line = new QLineEdit;

    connect(this, &Window::commandFrameValueChanged,
            this, [=](unsigned int value) { command_word_line->setText(QString::number(value)); });

    QFormLayout* formLayout2 = new QFormLayout;
    formLayout2->addRow(command_word_label1, command_word_spinbox1);
    formLayout2->addRow(command_word_label2, command_word_combobox1);
    formLayout2->addRow(command_word_label3, command_word_spinbox2);
    formLayout2->addRow(command_word_label4, command_word_spinbox3);
    formLayout2->addRow(command_word_label5, command_word_line);

    Group2->setLayout(formLayout2);
}

void Window::dataWordLabel(){

    Group3 = new QGroupBox(tr("Data Word Label"));
    data_word_label = new QLabel(tr("Data Word Value :"));///65535
    data_word_spinbox1 = new QSpinBox;
    data_word_spinbox1->setRange(0,65535);
    data_word_spinbox1->setValue(0);

    QFormLayout* formLayout3 = new QFormLayout;
    formLayout3->addRow(data_word_label, data_word_spinbox1);

    Group3->setLayout(formLayout3);
}

void Window::remoteTerminals(){

    QGroupBox* pointer[32]= {};
    QGridLayout* remote_terminals_box_layout = new QGridLayout;


    for( int i = 0; i <= 31; i++ )
    {

        QString tmp = QString::number(i);
        QString message = "RT" + tmp;
        pointer[i] = new QGroupBox(message);

        QPalette palette3 = pointer[i]->palette();
        palette3.setColor(QPalette::Window, QColor(255,0,0));
        pointer[i]->setAutoFillBackground(true);
        pointer[i]->setPalette(palette3);

        if(i <= 7){
            remote_terminals_box_layout->addWidget(pointer[i],0,i);
        }
        else if(7 < i && i<=15 ){
            remote_terminals_box_layout->addWidget(pointer[i],1,i-8);
        }
        else if(15 < i && i <= 23){
            remote_terminals_box_layout->addWidget(pointer[i],2,i-16);
        }
        else if(23 < i && i <= 31){
            remote_terminals_box_layout->addWidget(pointer[i],3,i-24);
        }

    }

    Group4 = new QGroupBox(tr("Remote Terminals"));
    Group4->setLayout(remote_terminals_box_layout);

}
