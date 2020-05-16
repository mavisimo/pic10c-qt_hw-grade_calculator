#include "grade_calculator.h"
#include "ui_grade_calculator.h"

grade_calculator::grade_calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::grade_calculator)
{
    ui->setupUi(this);

    // setting range and connecting sliders and spin boxes
    for(int i = 1; i<11; i++)
    {
        QSpinBox* spinbox = findChild<QSpinBox*>("spinBox_" + QString::number(i));
        QSlider* slider = findChild<QSlider*>("horizontalSlider_" + QString::number(i));
        spinbox->setRange(0,100);
        slider->setRange(0,100);
        connect(spinbox, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));
        connect(slider, SIGNAL(valueChanged(int)), spinbox, SLOT(setValue(int)));
    }


}

double grade_calculator::hw_grade()
{
    int hw_scores[7];
    int lowest_hw = 100;
    int hw_sum = 0;
    for (int i = 1; i<8; i++)
    {
        QSpinBox* spinbox = findChild<QSpinBox*>("spinBox_" + QString::number(i));
        hw_scores[i-1] = spinbox->value();
        hw_sum += hw_scores[i-1];
        if (lowest_hw > hw_scores[i-1])  lowest_hw = hw_scores[i-1];
    }
    return (hw_sum - lowest_hw)/6;
}

grade_calculator::~grade_calculator()
{
    delete ui;
}

