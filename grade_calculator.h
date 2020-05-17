#ifndef GRADE_CALCULATOR_H
#define GRADE_CALCULATOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class grade_calculator; }
QT_END_NAMESPACE

class grade_calculator : public QMainWindow
{
    Q_OBJECT

public:
    grade_calculator(QWidget *parent = nullptr);
    double hw_grade();
    ~grade_calculator();

private:
    Ui::grade_calculator *ui;

private slots:
    void final_grade_A();
    void final_grade_B();
    void radio_to_A();
    void radio_to_B();
};
#endif // GRADE_CALCULATOR_H
