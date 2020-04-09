#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setupLogic();
    this->setupElements();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupElements()
{
    QStringList list = QStringList();
    QComboBox * cb;
    this->setCBElements("vehicleChoiceCB", this->vehicleGenerator.getAvailableVehicles());
    this->setCBElements("iteratorTagCB", this->vehicleGenerator.getAllTags());
    this->setCBElements("iteratorPropertyCB", this->vehicleGenerator.getAllProperties());
    cb = ui->centralwidget->findChild<QComboBox*>("iteratorChoiceCB");
    list.push_back("Circle Iterator"); list.push_back("Circle Sorted Iterator");
    cb->clear();
    cb->addItems(list);
    list.clear();

    cb = ui->centralwidget->findChild<QComboBox*>("iteratorSortMethodCB");
    list.push_back("Bubble Sort");
    list.push_back("Insertion Sort");
    list.push_back("Selection Sort");
    cb->clear();
    cb->addItems(list);
    cb->setDisabled(true);
    list.clear();

}

void MainWindow::setupLogic()
{
    this->collection = new VehicleCollection();
    this->vehicleGenerator = VehicleGenerator();
}

void MainWindow::setCBElements(std::string cbName, std::vector<std::string> elements)
{
    QComboBox * cb = ui->centralwidget->findChild<QComboBox*>(QString::fromStdString(cbName));
    QStringList list = QStringList();
    for (int i = 0; i < elements.size(); i++)
        list.push_back(QString::fromStdString(elements[i]));
    cb->clear();
    cb->addItems(list);
}

void MainWindow::findAndReplaceParam(std::string param, double val)
{
    for (int i = 0; i < this->params.size(); i++)
        if (this->params[i].first == param)
            this->params[i].second = val;
}

std::vector<QString> MainWindow::createVehicleDesc(TemplateVehicle tv) {
    std::vector<QString> desc = std::vector<QString>();
    std::vector<std::string> tags = tv.getTags();
    std::vector<VehicleProperty> props = tv.getAllProperties();
    desc.push_back(QString()); desc.push_back(QString());
    desc[0].push_back("Tags: ");
    for(int i = 0; i < tags.size(); i++) {
        desc[0].push_back(QString::fromStdString(tags[i]));
        if (i != tags.size()-1)
            desc[0].push_back(" | ");
    }
    desc[1].push_back("Properties: ");
    for (int i = 0; i < props.size(); i++) {
        desc[1].push_back(QString::fromStdString(props[i].getName()));
        desc[1].push_back("=");
        desc[1].push_back(QString::number(props[i].getValue()));
        if (i != props.size()-1)
            desc[1].push_back(" | ");
    }

    return desc;
}

void MainWindow::putTextOnCollectionTE() {
    QTextEdit * te = ui->centralwidget->findChild<QTextEdit*>("collectionTE");
    te->clear();
    std::vector<QString> desc;
    QString headerString;
    for (int i = 0; i < this->collection->getLength(); i++){
        headerString.clear();
        headerString.push_back("Vehicle: #");
        headerString.push_back(QString::number(i));
        te->append(headerString);
        desc = createVehicleDesc(*this->collection->getItem(i));
        for (int i = 0; i <= 1; i++)
            te->append(desc[i]);
    }
}

void MainWindow::on_vehiclePropertyCB_activated(const QString &arg1)
{
    QLineEdit * le = ui->centralwidget->findChild<QLineEdit*>("vehiclePropertyVauleEdit");
    le->setText("0");
}

void MainWindow::on_vehicleChoiceCB_activated(const QString &arg1)
{
    QComboBox * cb = ui->centralwidget->findChild<QComboBox*>("vehiclePropertyCB");
    this->setCBElements("vehiclePropertyCB", this->vehicleGenerator.getRequiredProperties(arg1.toStdString()));
    cb->setDisabled(false);
    this->params = std::vector<std::pair<std::string, double>>();
    std::vector<std::string> props = this->vehicleGenerator.getRequiredProperties(arg1.toStdString());
    for (int i = 0; i < props.size(); i++)
        this->params.push_back(std::pair<std::string, double>(props[i], 0));

    QLineEdit * le = ui->centralwidget->findChild<QLineEdit*>("vehiclePropertyVauleEdit");
    le->setText("0");
}

void MainWindow::on_iteratorChoiceCB_activated(int index)
{
    if (index == 1) {
        QComboBox * cb = ui->centralwidget->findChild<QComboBox*>("iteratorSortMethodCB");
        cb->setDisabled(false);
    }
}

void MainWindow::on_applyVehiclePropertyButton_clicked()
{
    QComboBox * cb = ui->centralwidget->findChild<QComboBox*>("vehiclePropertyCB");
    QLineEdit * le = ui->centralwidget->findChild<QLineEdit*>("vehiclePropertyVauleEdit");
    QString qs = cb->currentText();
    this->findAndReplaceParam(qs.toStdString(), le->text().toDouble());
}

void MainWindow::on_createVehicleB_clicked()
{
    QComboBox * cb = ui->centralwidget->findChild<QComboBox*>("vehicleChoiceCB");
    QString qs = cb->currentText();
    TemplateVehicle * tv = this->vehicleGenerator.generateVehicle(qs.toStdString(), this->params);
    this->collection->pushBack(tv);
    this->putTextOnCollectionTE();
}

void MainWindow::on_createIteratorButton_clicked()
{
    QComboBox * cb = ui->centralwidget->findChild<QComboBox*>("iteratorChoiceCB");
    QComboBox * tag = ui->centralwidget->findChild<QComboBox*>("iteratorTagCB");
    QComboBox * property = ui->centralwidget->findChild<QComboBox*>("iteratorPropertyCB");
    QString qsTag = tag->currentText();
    QString qsProperty = property->currentText();

    switch (cb->currentIndex()) {
    case 0: {
        this->vehicleIterator = new CircleVehicleIterator(this->collection, qsTag.toStdString(), qsProperty.toStdString());
        this->iterName = cb->currentText();
        break;
    }
    case 1: {
        this->sortIterator = new CircleSortIterator(this->collection, qsTag.toStdString(), qsProperty.toStdString());
        QComboBox * sort = ui->centralwidget->findChild<QComboBox*>("iteratorSortMethodCB");
        switch (sort->currentIndex()) {
        case 0: {
            this->sortIterator->setSortingAlgorithm(new BubbleSort());
            break;
        }
        case 1: {
            this->sortIterator->setSortingAlgorithm(new InsertionSort());
            break;
        }
        case 2: {
            this->sortIterator->setSortingAlgorithm(new SelectionSort());
            break;
        }
        }
        this->vehicleIterator = this->sortIterator;
        this->iterName = cb->currentText();
        break;
    }
    }

}

void MainWindow::on_NEXTBUTTON_clicked()
{
    TemplateVehicle * tv = this->vehicleIterator->getNext();
    std::vector<QString> desc = this->createVehicleDesc(*tv);
    QTextEdit * te = ui->centralwidget->findChild<QTextEdit*>("currentElementEdit");
    te->clear();
    te->append(desc[0]);
    te->append(desc[1]);
    QString iteratorInfo;
    iteratorInfo.push_back("Iterator: ");
    iteratorInfo.push_back(this->iterName);
    te->append(iteratorInfo);
    iteratorInfo.clear();
    te->append("Has more? ");
    te->append(this->vehicleIterator->hasMore() ? "Yes" : "No");
}

void MainWindow::on_pushButton_clicked()
{
    this->collection = new VehicleCollection();
    this->vehicleIterator->~VehicleIterator();
    QTextEdit * te = this->ui->centralwidget->findChild<QTextEdit*>("currentElementEdit");
    te->clear();
    te = this->ui->centralwidget->findChild<QTextEdit*>("collectionTE");
    te->clear();
}
