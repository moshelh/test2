#include "PhysicalNumber.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <exception>

using namespace std;
using namespace ariel;

PhysicalNumber::PhysicalNumber(double num, Unit unit) {
    this -> unit = unit;
    this->value = num;
}

ostream &ariel::operator<<(ostream &os, const PhysicalNumber &c) {
    string output;
    switch (c.unit){
        case Unit::KM : output = "[km]"; break;
        case Unit::M : output = "[m]"; break;
        case Unit::CM : output = "[cm]"; break;
        case Unit::TON : output = "[ton]"; break;
        case Unit::KG : output = "[kg]"; break;
        case Unit::G : output = "[g]"; break;
        case Unit::HOUR : output = "[hour]"; break;
        case Unit::MIN : output = "[min]"; break;
        case Unit::SEC : output = "[sec]"; break;
        default: throw ("Invalid input");
    }
    return os << c.value << output;
}

istream &ariel::operator>>(istream &in, PhysicalNumber &c) {
    string tmp;
    in >> tmp;
    size_t index = tmp.find_first_of('[');
    if(index == string::npos) {
        throw "Invalid input";
    }
    string value = tmp.substr(0, index);
    string unit = tmp.substr(index, tmp.length());
    transform(unit.begin(), unit.end(), unit.begin(), ::tolower);
    c.value = stod(value);

    if(unit.compare("[km]") == 0 ) c.unit = Unit::KM;
    else if(unit.compare("[m]") == 0 ) c.unit = Unit::M;
    else if(unit.compare("[cm]") == 0 ) c.unit = Unit::CM;

    else if(unit.compare("[ton]") == 0 ) c.unit = Unit::TON;
    else if(unit.compare("[kg]") == 0 ) c.unit = Unit::KG;
    else if(unit.compare("[g]") == 0 ) c.unit = Unit::G;

    else if(unit.compare("[hour]") == 0 ) c.unit = Unit::HOUR;
    else if(unit.compare("[min]") == 0 ) c.unit = Unit::MIN;
    else if(unit.compare("[sec]") == 0) c.unit = Unit::SEC;

    else throw "Invalid Unit";

    return in;
}

const ariel::PhysicalNumber ariel::operator+(const ariel::PhysicalNumber &c1, const ariel::PhysicalNumber &c2) {
    PhysicalNumber tmp1 = PhysicalNumber::convert(c1);
    PhysicalNumber tmp2 = PhysicalNumber::convert(c2);
    double tmp;
    if((int)tmp1.unit%3 == (int)tmp2.unit%3) {
        tmp = tmp1.value + tmp2.value;
        if((int)tmp1.unit%3 == 0) {
            switch (c1.unit){
                case Unit::KM : tmp = tmp/(1000*100); break;
                case Unit::M : tmp = tmp/100; break;
                case Unit::CM : break;
            }
        }
        else if((int)tmp1.unit%3 == 2) {
            switch (c1.unit){
                case Unit::TON : tmp = tmp/(1000*1000); break;
                case Unit::KG : tmp = tmp/1000; break;
                case Unit::G : break;
            }
        }
        else {
            switch (c1.unit){
                case Unit::HOUR : tmp = tmp/(60*60); break;
                case Unit::MIN : tmp = tmp/60; break;
                case Unit::SEC : break;
            }
        }
    }
    else
        throw "Invalid operation";
    return  PhysicalNumber(tmp,  c1.unit);
}

PhysicalNumber PhysicalNumber::convert(PhysicalNumber pn) {
    double tmp;
    switch (pn.unit){
        case Unit::KM : tmp = pn.value*1000*100; pn.unit= Unit::CM; break;
        case Unit::M : tmp = pn.value*100; pn.unit= Unit::CM; break;
        case Unit::CM : tmp = pn.value; break;

        case Unit::TON : tmp = pn.value*1000*1000; pn.unit= Unit::G; break;
        case Unit::KG : tmp = pn.value*1000; pn.unit= Unit::G; break;
        case Unit::G : tmp = pn.value; break;

        case Unit::HOUR : tmp = pn.value*60*60; pn.unit= Unit::SEC; break;
        case Unit::MIN : tmp = pn.value*60; pn.unit= Unit::SEC; break;
        case Unit::SEC : tmp = pn.value; break;

        default: throw ("Invalid input");
    }
    pn.value = tmp;
    return pn;
}

const PhysicalNumber ariel::operator-(const PhysicalNumber &pn1, const PhysicalNumber &pn2) {
    PhysicalNumber tmp = pn2;
    tmp.value = -tmp.value;
    return pn1 + tmp;
}

const PhysicalNumber ariel::operator-(const PhysicalNumber &pn1) {
    PhysicalNumber tmp = pn1;
    tmp.value = -tmp.value;
    return tmp;
}

const PhysicalNumber ariel::operator+(const PhysicalNumber &pn1) {
    return pn1;
}

const PhysicalNumber &ariel::operator+=(PhysicalNumber &pn1, const PhysicalNumber &pn2) {
    PhysicalNumber temp=pn1+pn2;
    pn1=temp;
    return pn1;
}

const PhysicalNumber &ariel::operator-=(PhysicalNumber &pn1, const PhysicalNumber &pn2) {
    PhysicalNumber temp=pn1-pn2;
    pn1=temp;
    return pn1;
}

const PhysicalNumber ariel::operator++(PhysicalNumber &pn1) {
    pn1.value=pn1.value+1;
    return pn1;
}

const PhysicalNumber ariel::operator++(PhysicalNumber &pn1, int) {
    return ++pn1;
}

const PhysicalNumber ariel::operator--(PhysicalNumber &pn1) {
    pn1.value=pn1.value-1;
    return pn1;
}

const PhysicalNumber ariel::operator--(PhysicalNumber &pn1, int) {
    return --pn1;
}

const bool ariel::operator!=(const PhysicalNumber &pn1, const PhysicalNumber &pn2) {
    return (!(pn1==pn2));
}

const bool ariel::operator==(const PhysicalNumber &pn1, const PhysicalNumber &pn2) {

    PhysicalNumber tmp1 = PhysicalNumber::convert(pn1);
    PhysicalNumber tmp2 = PhysicalNumber::convert(pn2);

    if((int)tmp1.unit%3 == (int)tmp2.unit%3){
        if (tmp1.value==tmp2.value) return true;
    } else throw "Invalid input";
    return false;
}

const bool ariel::operator>=(const PhysicalNumber &pn1, const PhysicalNumber &pn2) {
    return (pn1>pn2||pn1==pn2);
}

const bool ariel::operator>(const PhysicalNumber &pn1, const PhysicalNumber &pn2) {
    PhysicalNumber tmp1 = PhysicalNumber::convert(pn1);
    PhysicalNumber tmp2 = PhysicalNumber::convert(pn2);

    if((int)tmp1.unit%3 == (int)tmp2.unit%3){
        if (tmp1.value>tmp2.value) return true;
    } else throw "Invalid input";
    return false;
}

const bool ariel::operator<=(const PhysicalNumber &pn1, const PhysicalNumber &pn2) {
    return (pn2>=pn1);
}

const bool ariel::operator<(const PhysicalNumber &pn1, const PhysicalNumber &pn2) {
    return (pn2>pn1);
}



