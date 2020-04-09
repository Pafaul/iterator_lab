#ifndef OBJECTS_H
#define OBJECTS_H
#include <vector>
#include <map>

//Done
class VehicleProperty {
protected:
    std::string name;
    double value, minValue, maxValue;
    std::string storedtype;
    double manageType(double val, std::string type);
public:
    VehicleProperty();
    VehicleProperty(std::string name, double minValue, double maxValue, std::string type);
    std::string getName();
    double getValue();
    void setValue(double value);
};


//Done
class VehiclePropertyGenerator {
protected:
    std::vector <VehicleProperty> templateProperties;
    int findProperty(std::string name);
public:
    VehiclePropertyGenerator();
    bool addTemplateProperty(std::string name, double minValue, double maxValue, std::string type);
    VehicleProperty createTemplateProperty(std::string name, double value);
    std::vector<VehicleProperty> getAllProperties();
};

//Done
class TemplateVehicle {
protected:
    std::vector<VehicleProperty> properties;
    std::vector<std::string> tags;
public:
    TemplateVehicle();
    TemplateVehicle(std::vector<std::string> tags, std::vector<VehicleProperty> values);
    std::vector<std::string> getAvailablePropertiesNames();
    VehicleProperty getProperty(std::string);
    std::vector<std::string> getTags();
    std::vector<VehicleProperty> getAllProperties();
};


//Done
class VehicleGenerator {
protected:
    VehiclePropertyGenerator generator;
    std::vector<std::pair<std::string, std::vector<std::string>>> vehicleTags,
                                                                  requiredProperties;
    std::vector<std::string> allVehicles, allTags, allProperties;
public:
    VehicleGenerator();
    std::vector<std::string> getAvailableVehicles();
    std::vector<std::string> getAllTags();
    std::vector<std::string> getAllProperties();
    TemplateVehicle * generateVehicle(std::string vehicleName, std::vector<std::pair<std::string, double>> values);
    std::vector<std::string> getRequiredProperties(std::string vehicleName);
};


//Done
class PropertyAssistant {
public:
    static int findProperty(std::vector<VehicleProperty> properties, std::string name);
};

#endif // OBJECTS_H
