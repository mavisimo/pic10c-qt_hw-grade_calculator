#include "grade_calculator.h"
#include "ui_grade_calculator.h"

grade_calculator::grade_calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::grade_calculator)
{
    ui->setupUi(this);

    // inital set of class and final grade output
    ui->lineEdit->setText(QString::number(0.0));
    ui->progressBar->setValue(0);
    ui->comboBox->addItem("PIC10B");
    ui->comboBox->addItem("PIC10C");
    connect(ui->comboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(choose_class()));

    // setting range and connecting sliders and spin boxes
    QSpinBox* inputs[10];
    for(int i = 1; i<11; i++)
    {
        QSpinBox* spinbox = findChild<QSpinBox*>("spinBox_" + QString::number(i));
        QSlider* slider = findChild<QSlider*>("horizontalSlider_" + QString::number(i));
        inputs[i] = findChild<QSpinBox*>("spinBox_" + QString::number(i));
        spinbox->setRange(0,100);
        slider->setRange(0,100);

        connect(spinbox, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));
        connect(slider, SIGNAL(valueChanged(int)), spinbox, SLOT(setValue(int)));
    }

    // connect radio buttons to final grade calculations
    connect(ui->radioButton, SIGNAL(toggled(bool)), this, SLOT(final_grade_A()));
    connect(ui->radioButton, SIGNAL(toggled(bool)), this, SLOT(radio_to_A()));
    connect(ui->radioButton_2, SIGNAL(toggled(bool)), this, SLOT(final_grade_B()));
    connect(ui->radioButton_2, SIGNAL(toggled(bool)), this, SLOT(radio_to_B()));
    ui->radioButton->toggle();
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
    return (hw_sum - lowest_hw)/6.0;
}

void grade_calculator::choose_class()
{
    if (ui->comboBox->currentText() == "PIC10B")
    {
        ui->label_8->setText("Midterm 1");
        ui->label_9->setText("Midterm 2");

        // connect radio buttons to final grade calculations
        connect(ui->comboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(final_grade_A()));
        connect(ui->radioButton, SIGNAL(toggled(bool)), this, SLOT(final_grade_A()));
        connect(ui->radioButton, SIGNAL(toggled(bool)), this, SLOT(radio_to_A()));
        connect(ui->radioButton_2, SIGNAL(toggled(bool)), this, SLOT(final_grade_B()));
        connect(ui->radioButton_2, SIGNAL(toggled(bool)), this, SLOT(radio_to_B()));
        ui->radioButton->toggle();
    }
    else //PIC10C
    {
        ui->label_8->setText("Midterm");
        ui->label_9->setText("Final Project");

        // connect radio buttons to final grade calculations
        connect(ui->comboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(final_grade_C()));
        connect(ui->radioButton, SIGNAL(toggled(bool)), this, SLOT(final_grade_C()));
        connect(ui->radioButton, SIGNAL(toggled(bool)), this, SLOT(radio_to_A()));
        connect(ui->radioButton_2, SIGNAL(toggled(bool)), this, SLOT(final_grade_C()));
        connect(ui->radioButton_2, SIGNAL(toggled(bool)), this, SLOT(radio_to_B()));
        ui->radioButton->toggle();
    }
}

void grade_calculator::radio_to_A()
{
    QSpinBox* inputs[10];
    for(int i = 1; i<11; i++)
    {
        inputs[i] = findChild<QSpinBox*>("spinBox_" + QString::number(i));
        connect(inputs[i], SIGNAL(valueChanged(int)), this, SLOT(final_grade_A()));
    }
}
void grade_calculator::radio_to_B()
{
    QSpinBox* inputs[10];
    for(int i = 1; i<11; i++)
    {
        inputs[i] = findChild<QSpinBox*>("spinBox_" + QString::number(i));
        connect(inputs[i], SIGNAL(valueChanged(int)), this, SLOT(final_grade_B()));
    }
}

void grade_calculator::final_grade_A()
{
    double hw_avg = hw_grade();
    int midterm_1 = ui->spinBox_8->value();
    int midterm_2 = ui->spinBox_9->value();
    int final = ui->spinBox_10->value();
    double final_score = 0.25*hw_avg + 0.2*midterm_1 + 0.2*midterm_2 + 0.35*final;
    ui->lineEdit->setText(QString::number(final_score));
    ui->progressBar->setValue(final_score);
}

void grade_calculator::final_grade_B()
{
    double hw_avg = hw_grade();
    int midterm = ui->spinBox_8->value();
    int midterm_2 = ui->spinBox_9->value();
    if (midterm < midterm_2)  midterm = midterm_2;
    int final = ui->spinBox_10->value();
    double final_score = 0.25*hw_avg + 0.3*midterm + 0.45*final;
    ui->lineEdit->setText(QString::number(final_score));
    ui->progressBar->setValue(final_score);
}

void grade_calculator::final_grade_C()
{
    double hw_avg = hw_grade();
    int midterm = ui->spinBox_8->value();
    int project = ui->spinBox_9->value();
    int final = ui->spinBox_10->value();
    double final_score = 0.15*hw_avg + 0.25*midterm + 0.3*project + 0.3*final;
    ui->lineEdit->setText(QString::number(final_score));
    ui->progressBar->setValue(final_score);
}

void grade_calculator::final_grade_D()
{
    double hw_avg = hw_grade();
    int project = ui->spinBox_9->value();
    int final = ui->spinBox_10->value();
    double final_score = 0.15*hw_avg + 0.5*project + 0.35*final;
    ui->lineEdit->setText(QString::number(final_score));
    ui->progressBar->setValue(final_score);
}

grade_calculator::~grade_calculator()
{
    delete ui;
}

