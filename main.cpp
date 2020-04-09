#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
//int main()
//{
//    Collection * collection = new VehicleCollection();
//    VehicleGenerator vehicleGenerator = VehicleGenerator();
//    std::cout << "All Vehicles: ";
//    for (int i = 0; i < vehicleGenerator.getAvailableVehicles().size(); i++)
//    {
//        std::cout << "Properties for " << vehicleGenerator.getAvailableVehicles()[i] << ":" << std::endl;
//        for (int j = 0; j < vehicleGenerator.getRequiredProperties(vehicleGenerator.getAvailableVehicles()[i]).size(); j++)
//            std::cout << vehicleGenerator.getRequiredProperties(vehicleGenerator.getAvailableVehicles()[i])[j] << " | ";
//        std::cout << std::endl;
//    }
//    std::cout << std::endl;
//}
