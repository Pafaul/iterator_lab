#include "vehicles.h"

/** Конструктор характеристик средств передвижения, задаёт мин/макс значения и хранимый тип
 * @param name {std::string}
 * @param minValue {double}
 * @param maxValue {double}
 * @param type {std::string}
 */
VehicleProperty::VehicleProperty(std::string name, double minValue, double maxValue, std::string type) {
    this->name = name;
    this->minValue = minValue;
    this->maxValue = maxValue;
    this->storedtype = type;
}

/** Проверка задаваемого значения на граничные условия, если не взодит в них -
 * присвоение максимального или минимального значения
 * @brief VehicleProperty::setValue
 * @param value {double}
 */
void VehicleProperty::setValue(double value) {
    value = this->manageType(value, this->storedtype);
    value = value > this->maxValue ? this->maxValue : value;
    value = value < this->minValue ? this->minValue : value;
    this->value = value;
}

/** Проверка соответствия значения хранимому типу, и приведение, если необходимо
 * @brief VehicleProperty::manageType
 * @param val {double}
 * @param type {std::string}
 * @return {double}
 */
double VehicleProperty::manageType(double val, std::string type) {
    if (type == "double") {
        return val;
    } else {
        return static_cast<int>(val);
    }
}

/** Получение значения
 * @brief VehicleProperty::getValue
 * @return {double}
 */
double VehicleProperty::getValue() {
    return this->value;
}

/** Получение названия характеристики
 * @brief VehicleProperty::getName
 * @return {std::string}
 */
std::string VehicleProperty::getName() {
    return this->name;
}

/** Конструктр генератора характеристик средств передвижения
 * @brief VehiclePropertyGenerator::VehiclePropertyGenerator
 */
VehiclePropertyGenerator::VehiclePropertyGenerator() {
    this->templateProperties = std::vector <VehicleProperty>();
    this->addTemplateProperty("Fuel Volume", 0, 50, "double");
    this->addTemplateProperty("Parking Days Count", 0, 10, "int");
    this->addTemplateProperty("Current Parking Day", 0, 10, "int");
    this->addTemplateProperty("Parking Lot", 0, 200, "int");
    this->addTemplateProperty("Cargo Weight", 0, 50, "double");
    this->addTemplateProperty("Sit Amount", 0, 50, "int");
    this->addTemplateProperty("Passenger Count", 0, 50, "int");
    this->addTemplateProperty("Rockets Amount", 0, 6, "int");
    this->addTemplateProperty("Required Place", 0, 200, "int");
    this->addTemplateProperty("Gas Station Status", 0, 1, "int");
}

/** Добавление новой характеристики в генератор
 * @brief VehiclePropertyGenerator::addTemplateProperty
 * @param name
 * @param minValue
 * @param maxValue
 * @param type
 * @return
 */
bool VehiclePropertyGenerator::addTemplateProperty(std::string name, double minValue, double maxValue, std::string type) {
    if (PropertyAssistant::findProperty(this->getAllProperties(), name) == -1) {
        this->templateProperties.push_back(VehicleProperty(name, minValue, maxValue, type));
        return true;
    }
    return false;
}

/** Создание характеристики средства передвижения из шаблона
 * @brief VehiclePropertyGenerator::createTemplateProperty
 * @param name
 * @param value
 * @return
 */
VehicleProperty VehiclePropertyGenerator::createTemplateProperty(std::string name, double value) {
    int index = PropertyAssistant::findProperty(this->getAllProperties(), name);
    if (index != -1) {
        VehicleProperty prop = this->templateProperties[index];
        prop.setValue(value);
        return prop;
    }
}

/** Получение всех имеющихся шаблонных характеристик средств передвижения
 * @brief VehiclePropertyGenerator::getAllProperties
 * @return
 */
std::vector<VehicleProperty> VehiclePropertyGenerator::getAllProperties() {
    return this->templateProperties;
}


/** Конструктор шаблонного средства передвижения
 * @brief TemplateVehicle::TemplateVehicle
 * @param tags
 * @param values
 */
TemplateVehicle::TemplateVehicle(std::vector<std::string> tags, std::vector<VehicleProperty> values) {
    this->tags = tags;
    this->properties = values;
}

/** Получение характеристик, присущих данному средству передвижения
 * @brief TemplateVehicle::getAvailablePropertiesNames
 * @return
 */
std::vector<std::string> TemplateVehicle::getAvailablePropertiesNames() {
    std::vector<std::string> names = std::vector<std::string>();
    if (this->properties.size() > 0)
        for (std::vector<VehicleProperty>::iterator it = this->properties.begin(); it < this->properties.end(); ++it)
            names.push_back(it->getName());
    return names;
}

/** Получения конкретной характеристики средства передвижения
 * @brief TemplateVehicle::getProperty
 * @param name
 * @return
 */
VehicleProperty TemplateVehicle::getProperty(std::string name) {
    int index = PropertyAssistant::findProperty(this->getAllProperties(), name);
    if ( index != -1 ) {
        return this->properties[index];
    }
}

/** Получение всех тэгов (название средства передвижения, его тип,...), присущих средству передвижения
 * @brief TemplateVehicle::getTags
 * @return
 */
std::vector<std::string> TemplateVehicle::getTags() {
    return this->tags;
}


/** Получение всех характеристик средвства передвижения
 * @brief TemplateVehicle::getAllProperties
 * @return
 */
std::vector<VehicleProperty> TemplateVehicle::getAllProperties() {
    return this->properties;
}

/** Конструктор генератора средств передвижения. Происходит инициализация генератора
 * характеристик средств передвижения, а также определяется какие свойства и тэги
 * присущи конкретному средству передвижения
 * @brief VehicleGenerator::VehicleGenerator
 */
VehicleGenerator::VehicleGenerator() {
    this->generator = VehiclePropertyGenerator();

    //Vehicle Names
    std::string
            ssp = "Single Sit Plane",
            tp = "Transport Plane",
            pp = "Passenger Plane",
            lh = "Light Helicopter",
            bh = "Battle Helicopter",
            fp = "Fighter Plane",
            gt = "Gasoline Tanker",
            bs = "Bus";
    this->allVehicles = std::vector<std::string>{ssp ,tp, pp, lh, bh, fp, gt, bs};

    //Tags
    std::string
            flyingObj = "Flying Vehicle",
            landObj = "Land Vehicle",
            passObj = "Passenger Vehicle",
            cargoObj = "Cargo Vehicle",
            battleObj = "Battle Vehicle";
    this->allTags = std::vector<std::string>{flyingObj, landObj, passObj, cargoObj, battleObj, ssp ,tp, pp, lh, bh, fp, gt, bs};

    //Properties
    std::string
            fuel = "Fuel Volume",
            pdc = "Parking Days Count",
            cpd = "Current Parking Day",
            pl = "Parking Lot",
            cw = "Cargo Weight",
            sa = "Sit Amount",
            pc = "Passenger Count",
            ra = "Rockets Amount",
            rp = "Required Place",
            gss = "Gas Station Status";
    this->allProperties = std::vector<std::string>{fuel, pdc, cpd, pl, cw, sa, pc, ra, rp, gss};

    this->vehicleTags = std::vector<std::pair<std::string, std::vector<std::string>>> {
        std::make_pair(ssp, std::vector<std::string> {
                                   flyingObj, ssp
                       }),
        std::make_pair(tp, std::vector<std::string> {
                                   flyingObj, cargoObj, tp
                       }),
        std::make_pair(pp, std::vector<std::string> {
                                   flyingObj, passObj, pp
                       }),
        std::make_pair(lh, std::vector<std::string> {
                                   flyingObj, lh
                       }),
        std::make_pair(bh, std::vector<std::string> {
                                   flyingObj, battleObj, bh
                       }),
        std::make_pair(fp, std::vector<std::string> {
                                   flyingObj, battleObj, fp
                       }),
        std::make_pair(gt, std::vector<std::string> {
                                   landObj, cargoObj, gt
                       }),
        std::make_pair(bs, std::vector<std::string> {
                                   landObj, passObj, bs
                       })
    };

    this->requiredProperties = std::vector<std::pair<std::string, std::vector<std::string>>> {
        std::make_pair(ssp, std::vector<std::string> {
                                   fuel, pdc, cpd, pl
                       }),
        std::make_pair(tp, std::vector<std::string> {
                                   fuel, pdc, cpd, pl, cw
                       }),
        std::make_pair(pp, std::vector<std::string> {
                                   fuel, pdc, cpd, pl, sa, pc
                       }),
        std::make_pair(lh, std::vector<std::string> {
                                   fuel, pdc, cpd, pl
                       }),
        std::make_pair(bh, std::vector<std::string> {
                                   fuel, pdc, cpd, pl, ra
                       }),
        std::make_pair(fp, std::vector<std::string> {
                                   fuel, pdc, cpd, pl, ra
                       }),
        std::make_pair(gt, std::vector<std::string> {
                                   fuel, pdc, cpd, pl, gss, rp
                       }),
        std::make_pair(bs, std::vector<std::string> {
                                   fuel, pl, sa, pc, rp
                       })
    };
}

/** Получение всех доступных средств передвижения
 * @brief VehicleGenerator::getAvailableVehicles
 * @return
 */
std::vector<std::string> VehicleGenerator::getAvailableVehicles() {
    return this->allVehicles;
}

/** Получение всех доступных тэгов
 * @brief VehicleGenerator::getAllTags
 * @return
 */
std::vector<std::string> VehicleGenerator::getAllTags() {
    return this->allTags;
}

/** Получение всех доступных свойств
 * @brief VehicleGenerator::getAllProperties
 * @return
 */
std::vector<std::string> VehicleGenerator::getAllProperties() {
    return this->allProperties;
}

/** Создание средства передвижения на основе полученной информации о названии средства передвижения
 * и переданных характеристик в виде пар "название"-"величина"
 * @brief VehicleGenerator::generateVehicle
 * @param vehicleName
 * @param values
 * @return
 */
TemplateVehicle * VehicleGenerator::generateVehicle(std::string vehicleName, std::vector<std::pair<std::string, double>> values) {
    std::vector<std::string> tags = std::vector<std::string>();
    std::vector<VehicleProperty> * properties = new std::vector<VehicleProperty>();

    for (std::vector<std::pair<std::string, double>>::iterator it = values.begin(); it < values.end(); it++) {
        properties->push_back(this->generator.createTemplateProperty(it->first, it->second));
    }

    for (std::vector<std::pair<std::string, std::vector<std::string>>>::iterator it = this->vehicleTags.begin(); it < this->vehicleTags.end(); it++)
    {
        if (it->first == vehicleName)
        {
            tags = it->second;
            break;
        }
    }

    return new TemplateVehicle(tags, *properties);
}

/** Получение характеристик, присущих(необходимых для создания) конкретного средства передвижения
 * @brief VehicleGenerator::getRequiredProperties
 * @param vehicleName
 * @return
 */
std::vector<std::string> VehicleGenerator::getRequiredProperties(std::string vehicleName) {
    std::vector<std::string> prop;
    for (std::vector<std::pair<std::string, std::vector<std::string>>>::iterator it = this->requiredProperties.begin();
         it < this->requiredProperties.end(); it++)
    {
        if (it->first == vehicleName){
            prop = it->second;
            break;
        }
    }
    return prop;
}


/** Вспомогательная функция для поиска индекса характеристики в векторе характеристик средств передвижения
 * @brief PropertyAssistant::findProperty
 * @param properties
 * @param name
 * @return
 */
int PropertyAssistant::findProperty(std::vector<VehicleProperty> properties, std::string name) {
    int index = -1;
    if ( properties.size() > 0 ) {
        for ( int i = 0; i < properties.size(); i++ )
        {
            if ( properties[i].getName() == name )
            {
                index = i;
                break;
            }
        }
    }

    return index;
}

