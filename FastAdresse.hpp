/* 
 * File:   FastAdresse.hpp
 * Author: markus
 *
 * Created on 13. Februar 2016, 23:06
 */

#ifndef FASTADRESSE_HPP
#define	FASTADRESSE_HPP

#include <string>
#include <ostream>
#include <random>

namespace FastAdresse {

class RandomObjects {
public:
    static std::wstring randomString(std::minstd_rand0& randomizer,
            size_t length) {
        wchar_t rs[length];
        for (size_t i=0; i<length; ++i) {
            uint_fast32_t randomNumber = randomizer();
            randomNumber %= 26;
            randomNumber += 65;
            rs[i] = static_cast<wchar_t>(randomNumber);
        }
        return std::wstring (rs, length);
    }
    static uint_fast32_t randomNumber(std::minstd_rand0& randomizer,
           uint_fast32_t maxNumber) {
        uint_fast32_t randomNumber = randomizer();
        randomNumber %= maxNumber;
        return randomNumber;
    }
};
    
class Adresse {
public:
    Adresse (const std::wstring& vorname, const std::wstring& name,
             const std::wstring& strasse, int hausnummer, int plz,
             const std::wstring& ort)
    : _vorname (vorname)
    , _name (name)
    , _strasse (strasse)
    , _hausnummer (hausnummer)
    , _plz (plz)
    , _ort (ort) {
    }
    std::wstring getVorname() const {
        return _vorname;
    }
    std::wstring getName() const {
        return _name;
    }
    std::wstring getStrasse() const {
        return _strasse;
    }
    int getHausnummer() const {
        return _hausnummer;
    }
    int getPlz() const {
        return _plz;
    }
    std::wstring getOrt() const  {
        return _ort;
    }
    friend std::wostream& operator<< (std::wostream& stream, const Adresse& a) {
        stream << "Name=" << a._name << ", Vorname=" << a._vorname
               << ", Strasse=" << a._strasse << ' ' << a._hausnummer << ", Ort="
               << a._plz << ' ' << a._ort;
        return stream;
    }
    static Adresse randomAdresse(std::minstd_rand0& randomizer) {
        return Adresse (RandomObjects::randomString (randomizer, 10),
                RandomObjects::randomString (randomizer, 15),
                RandomObjects::randomString (randomizer, 12),
                RandomObjects::randomNumber(randomizer, 100),
                RandomObjects::randomNumber(randomizer, 100000),
                RandomObjects::randomString (randomizer, 17));
    }
private:
    std::wstring _vorname;
    std::wstring _name;
    std::wstring _strasse;
    int _hausnummer;
    int _plz;
    std::wstring _ort;
};

class VornameNameExact {
public:
    VornameNameExact (const std::wstring& vorname, const std::wstring& name)
    : _vorname(vorname)
    , _name(name) {
    }
    bool operator<(const VornameNameExact& other) const {
        _numberOfComparisons++;
        if (_name != other._name) {
            return _name < other._name;
        } else {
            return _vorname < other._vorname;
        }
    }
    std::wstring getVorname() const {
        return _vorname;
    }
    std::wstring getName() const {
        return _name;
    }
    static VornameNameExact randomVornameNameExact(
        std::minstd_rand0& randomizer) {
        return VornameNameExact (RandomObjects::randomString (randomizer, 10),
                                 RandomObjects::randomString (randomizer, 15));
        
    }
    static void resetNumberOfComparisons() {
        _numberOfComparisons = 0;
    }
    static int getNumberOfComparisons() {
        return _numberOfComparisons;
    }
private:
    std::wstring _vorname;
    std::wstring _name;
    static int _numberOfComparisons;
};

class HausnummerPlzExact {
public:
    HausnummerPlzExact (int hausnummer, int plz)
    : _hausnummer(hausnummer)
    , _plz(plz) {
    }
    inline bool operator<(const HausnummerPlzExact& other) const {
        _numberOfComparisons++;
        if (_plz ^ other._plz) {
            // Curious: This seems to be faster than:
            // return _plz < other._plz;
            return _plz - other._plz < 0 ? true : false;
        } else {
            // Curious: This seems to be faster than:
            // return _hausnummer < other._hausnummer;
            return _hausnummer - other._hausnummer < 0 ? true : false;
        }
    }
    int getHausnummer() const {
        return _hausnummer;
    }
    int getPlz() const {
        return _plz;
    }
    static HausnummerPlzExact randomHausnummerPlzExact(
        std::minstd_rand0& randomizer) {
        return HausnummerPlzExact (RandomObjects::randomNumber (randomizer, 100),
                RandomObjects::randomNumber (randomizer, 100000));
       
    }
    static void resetNumberOfComparisons() {
        _numberOfComparisons = 0;
    }
    static int getNumberOfComparisons() {
        return _numberOfComparisons;
    }
private:
    int _hausnummer;
    int _plz;
    static int _numberOfComparisons;
};

}

#endif	/* FASTADRESSE_HPP */

