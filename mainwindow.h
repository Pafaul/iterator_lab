#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFormLayout>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include "collection.h"
#include "vehicles.h"
#include "iterator.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_vehiclePropertyCB_activated(const QString &arg1);

    void on_vehicleChoiceCB_activated(const QString &arg1);

    void on_iteratorChoiceCB_activated(int index);

    void on_applyVehiclePropertyButton_clicked();

    void on_createVehicleB_clicked();

    void on_createIteratorButton_clicked();

    void on_NEXTBUTTON_clicked();

    void on_pushButton_clicked();

private:
    void setupElements();
    void setupLogic();
    void setCBElements(std::string cbName, std::vector<std::string> elements);
    void findAndReplaceParam(std::string param, double val);
    void putTextOnCollectionTE();
    std::vector<QString> createVehicleDesc(TemplateVehicle tv);

    Ui::MainWindow *ui;

    VehicleGenerator vehicleGenerator;
    Collection * collection;

    VehicleIterator * vehicleIterator;
    SortIterator * sortIterator;
    QString iterName;

    std::vector<std::pair<std::string, double>> params;

};

#endif // MAINWINDOW_H
