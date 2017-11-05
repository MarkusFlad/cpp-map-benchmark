/* 
 * File:   Adresse.cpp
 * Author: markus
 * 
 * Created on 13. Februar 2016, 22:54
 */

#include "SlowAdresse.hpp"

using namespace SlowAdresse;
using namespace std;

wstring RandomObjects::randomString(minstd_rand0& randomizer, size_t length) {
    wchar_t rs[length];
    for (size_t i=0; i<length; ++i) {
        uint_fast32_t randomNumber = randomizer();
        randomNumber %= 26;
        randomNumber += 65;
        rs[i] = static_cast<wchar_t>(randomNumber);
    }
    return wstring (rs, length);
}
uint_fast32_t RandomObjects::randomNumber(minstd_rand0& randomizer,
        uint_fast32_t maxNumber) {
    uint_fast32_t randomNumber = randomizer();
    randomNumber %= maxNumber;
    return randomNumber;
}

Adresse::Adresse (const wstring& vorname, const wstring& name,
                  const wstring& strasse, int hausnummer,
                  int plz, const wstring& ort)
: _vorname (vorname)
, _name (name)
, _strasse (strasse)
, _hausnummer (hausnummer)
, _plz (plz)
, _ort (ort) {
}
wstring Adresse::getVorname() const {
    return _vorname;
}
wstring Adresse::getName() const {
    return _name;
}
wstring Adresse::getStrasse() const {
    return _strasse;
}
int Adresse::getHausnummer() const {
    return _hausnummer;
}
int Adresse::getPlz() const {
    return _plz;
}
wstring Adresse::getOrt() const  {
    return _ort;
}
Adresse Adresse::randomAdresse(minstd_rand0& randomizer) {
    return Adresse (RandomObjects::randomString (randomizer, 10),
            RandomObjects::randomString (randomizer, 15),
            RandomObjects::randomString (randomizer, 12),
            RandomObjects::randomNumber(randomizer, 100),
            RandomObjects::randomNumber(randomizer, 100000),
            RandomObjects::randomString (randomizer, 17));
}

VornameNameExact::VornameNameExact (const wstring& vorname,
        const wstring& name)
: _vorname (vorname)
, _name (name) {
}
bool VornameNameExact::operator<(const VornameNameExact& other) const {
    _numberOfComparisons++;
    if (_name != other._name) {
        return _name < other._name;
    } else {
        return _vorname < other._vorname;
    }
}
wstring VornameNameExact::getVorname() const {
    return _vorname;
}
wstring VornameNameExact::getName() const {
    return _name;
}
VornameNameExact VornameNameExact::randomVornameNameExact(minstd_rand0& randomizer) {
    return VornameNameExact (RandomObjects::randomString (randomizer, 10),
                             RandomObjects::randomString (randomizer, 15));
}
int VornameNameExact::_numberOfComparisons = 0;
void VornameNameExact::resetNumberOfComparisons() {
    _numberOfComparisons = 0;
}
int VornameNameExact::getNumberOfComparisons() {
    return _numberOfComparisons;
}
HausnummerPlzExact::HausnummerPlzExact (int hausnummer, int plz)
: _hausnummer (hausnummer)
, _plz (plz) {
}
bool HausnummerPlzExact::operator<(const HausnummerPlzExact& other) const {
    _numberOfComparisons++;
    if (_plz != other._plz) {
        return _plz < other._plz;
    } else {
        return _hausnummer < other._hausnummer;
    }
}
int HausnummerPlzExact::getHausnummer() const {
    return _hausnummer;
}
int HausnummerPlzExact::getPlz() const {
    return _plz;
}
HausnummerPlzExact HausnummerPlzExact::randomHausnummerPlzExact(minstd_rand0& randomizer) {
    return HausnummerPlzExact (RandomObjects::randomNumber (randomizer, 100),
                               RandomObjects::randomNumber (randomizer, 100000));
}
int HausnummerPlzExact::_numberOfComparisons = 0;
void HausnummerPlzExact::resetNumberOfComparisons() {
    _numberOfComparisons = 0;
}
int HausnummerPlzExact::getNumberOfComparisons() {
    return _numberOfComparisons;
}
