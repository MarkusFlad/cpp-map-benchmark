/* 
 * File:   Adresse.hpp
 * Author: markus
 *
 * Created on 13. Februar 2016, 22:54
 */

#ifndef ADRESSE_HPP
#define	ADRESSE_HPP

#include <string>
#include <ostream>
#include <random>

namespace SlowAdresse {

class RandomObjects {
public:
    static std::wstring randomString(std::minstd_rand0& randomizer,
            size_t length);
    static uint_fast32_t randomNumber(std::minstd_rand0& randomizer,
           uint_fast32_t maxNumber);
};

class Adresse {
public:
    Adresse (const std::wstring& vorname, const std::wstring& name,
             const std::wstring& strasse, int hausnummer,
             int plz, const std::wstring& ort);
    std::wstring getVorname() const;
    std::wstring getName() const;
    std::wstring getStrasse() const;
    int getHausnummer() const;
    int getPlz() const;
    std::wstring getOrt() const;
    friend std::basic_ostream<wchar_t>& operator<< (std::basic_ostream<wchar_t>& stream,
                                                    const Adresse& a) {
        stream << "Name=" << a._name << ", Vorname=" << a._vorname
               << ", Strasse=" << a._strasse << ' ' << a._hausnummer << ", Ort="
               << a._plz << ' ' << a._ort;
        return stream;
    }
    static std::wstring randomString(std::minstd_rand0& randomizer,
           std::size_t length);
    static uint_fast32_t randomNumber(std::minstd_rand0& randomizer,
           uint_fast32_t maxNumber);
    static Adresse randomAdresse(std::minstd_rand0& randomizer);
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
    VornameNameExact (const std::wstring& vorname, const std::wstring& name);
    inline bool operator<(const VornameNameExact& other) const {
        _numberOfComparisons++;
        if (_name != other._name) {
            return _name < other._name;
        } else {
            return _vorname < other._vorname;
        }
    }
    std::wstring getVorname() const;
    std::wstring getName() const;
    static VornameNameExact randomVornameNameExact(
        std::minstd_rand0& randomizer);
    static void resetNumberOfComparisons();
    static int getNumberOfComparisons();
private:
    std::wstring _vorname;
    std::wstring _name;
    static int _numberOfComparisons;
};

class HausnummerPlzExact {
public:
    HausnummerPlzExact (int hausnummer, int plz);
    inline bool operator<(const HausnummerPlzExact& other) const {
        _numberOfComparisons++;
        if (_plz != other._plz) {
            return _plz < other._plz;
        } else {
            return _hausnummer < other._hausnummer;
        }
    }
    int getHausnummer() const;
    int getPlz() const;
    static HausnummerPlzExact randomHausnummerPlzExact(
        std::minstd_rand0& randomizer);
    static void resetNumberOfComparisons();
    static int getNumberOfComparisons();
private:
    int _hausnummer;
    int _plz;
    static int _numberOfComparisons;
};

}

#endif	/* ADRESSE_HPP */

