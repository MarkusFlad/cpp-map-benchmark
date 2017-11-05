/* 
 * File:   main.cpp
 * Author: markus
 *
 * Created on 8. Februar 2016, 22:03
 */

#include "FastAdresse.hpp"
#include "SlowAdresse.hpp"
#include <vector>
#include <map>
#include <iostream>
#include <chrono>
#include <fstream>
#include <sstream>

using namespace std;
using namespace std::chrono;
using namespace FastAdresse;

int main(int argc, char** argv) {
    auto start = steady_clock::now();
    vector<Adresse> addresses;
    minstd_rand0 randomizer;
    wifstream infile1("addresses.txt");
    if (infile1.good()) {
        wcout << "Reading addresses.txt file ..." << endl;
        wstring line;
        int i = 0;
        wstring vorname;
        wstring name;
        wstring strasse;
        int hausnummer;
        int plz;
        wstring ort;
        while (std::getline(infile1, line)) {
            switch (i) {
                case 0:
                    vorname = line;
                    break;
                case 1:
                    name = line;
                    break;
                case 2:
                    strasse = line;
                    break;
                case 3:
                {
                    wistringstream ossHausnummer (line);
                    ossHausnummer >> hausnummer;
                    break;
                }
                case 4:
                {
                    wistringstream ossPlz (line);
                    ossPlz >> plz;
                    break;
                }
                case 5:
                    ort = line;
                    break;
            }
            i++;
            if (i>5) {
                addresses.push_back(Adresse(vorname, name, strasse, hausnummer,
                        plz, ort));
                i=0;
            }
        }
    } else {
        wcout << "Putting adresses to vector and file ..." << endl;
        wofstream outfile("addresses.txt");
        for (int i=0; i<3000000; i++) {
            addresses.push_back(Adresse::randomAdresse(randomizer));
            const Adresse& adresse = addresses[i];
            outfile << adresse.getVorname() << '\n';
            outfile << adresse.getName() << '\n';
            outfile << adresse.getStrasse() << '\n';
            outfile << adresse.getHausnummer() << '\n';
            outfile << adresse.getPlz() << '\n';
            outfile << adresse.getOrt() << '\n';
        }
    }
    wcout << "Adresses in vector:" << addresses.size() << endl;
    auto startBuildingIndex1 = steady_clock::now();
    auto diff1 = startBuildingIndex1 - start;
    wcout << "Time to create adresses: " <<
            duration_cast<milliseconds>(diff1).count() << "ms." << endl;
    wcout << "Building index for Vorname Name..." << endl;
    typedef map<VornameNameExact, const Adresse*> SearchMap1;
    SearchMap1 addressMap1;
    for (const Adresse& adresse :  addresses) {
        addressMap1[VornameNameExact(adresse.getVorname(),
                adresse.getName())] = &adresse;
    }
    auto startBuildingIndex2 = steady_clock::now();
    auto diff1_1 = startBuildingIndex2 - startBuildingIndex1;
    wcout << "Time for indexing for Vorname Name: " <<
            duration_cast<milliseconds>(diff1_1).count() << "ms." << endl;
    wcout << "Building index for Hausnummer and PLZ ..." << endl;
    typedef map<HausnummerPlzExact, const Adresse*> SearchMap2;
    SearchMap2 addressMap2;
    for (const Adresse& adresse :  addresses) {
        addressMap2[HausnummerPlzExact(adresse.getHausnummer(),
                adresse.getPlz())] = &adresse;
    }
    auto startCreatingSearchRequests1 = steady_clock::now();
    auto diff2_1 = startCreatingSearchRequests1 - startBuildingIndex2;
    wcout << "Time for indexing for Hausnummer and PLZ: " <<
            duration_cast<milliseconds>(diff2_1).count() << "ms." << endl;
    vector<VornameNameExact> searchRequests1;
    wifstream infile2("searchRequests1.txt");
    if (infile2.good()) {
        wcout << "Reading searchRequests1.txt file ..." << endl;
        wstring line;
        int i = 0;
        wstring vorname;
        wstring name;
        while (std::getline(infile2, line)) {
            switch (i) {
                case 0:
                    vorname = line;
                    break;
                case 1:
                    name = line;
                    break;
            }
            i++;
            if (i>1) {
                searchRequests1.push_back(VornameNameExact(vorname, name));
                i=0;
            }
        }
    } else {
        wcout << "Putting search requests 1 to vector and file ..." << endl;
        wofstream outfile("searchRequests1.txt");
        for (int i=0; i<1000000; i++) {
            searchRequests1.push_back(VornameNameExact::randomVornameNameExact(
                                      randomizer));
            VornameNameExact& vne = searchRequests1[i];
            outfile << vne.getVorname() << '\n';
            outfile << vne.getName() << '\n';
        }
    }
    auto startCreatingSearchRequests2 = steady_clock::now();
    auto diff2_2 = startCreatingSearchRequests2 - startCreatingSearchRequests1;
    wcout << "Time for building search requests 1: " <<
            duration_cast<milliseconds>(diff2_2).count() << "ms." << endl;
    vector<HausnummerPlzExact> searchRequests2;
    wifstream infile3("searchRequests2.txt");
    if (infile3.good()) {
        wcout << "Reading searchRequests2.txt file ..." << endl;
        wstring line;
        int i = 0;
        int hausnummer;
        int plz;
        while (std::getline(infile3, line)) {
            switch (i) {
                case 0:
                {
                    wistringstream ossHausnummer (line);
                    ossHausnummer >> hausnummer;
                    break;
                }
                case 1:
                {
                    wistringstream ossPlz (line);
                    ossPlz >> plz;
                    break;
                }
            }
            i++;
            if (i>1) {
                searchRequests2.push_back(HausnummerPlzExact(hausnummer, plz));
                i=0;
            }
        }
    } else {
        wcout << "Putting search requests 2 to vector and file ..." << endl;
        wofstream outfile("searchRequests2.txt");
        for (int i=0; i<1000000; i++) {
            searchRequests2.push_back(HausnummerPlzExact::
                                      randomHausnummerPlzExact(randomizer));
            HausnummerPlzExact hpe = searchRequests2[i];
            outfile << hpe.getHausnummer() << '\n';
            outfile << hpe.getPlz() << '\n';
        }
    }
    VornameNameExact::resetNumberOfComparisons();
    HausnummerPlzExact::resetNumberOfComparisons();
    auto startSearch1 = steady_clock::now();
    auto diff3_1 = startSearch1 - startCreatingSearchRequests2;
    wcout << "Time for building search requests 2: " <<
            duration_cast<milliseconds>(diff3_1).count() << "ms." << endl;
    wcout << "Performing 1x" << searchRequests1.size() << " search requests 1 ..."
         << endl;
    for (int i=0; i<1; i++) {
        for (const VornameNameExact& searchRequest : searchRequests1) {
            SearchMap1::const_iterator itFound = addressMap1.find(searchRequest);
            if (itFound != addressMap1.end()) {
                const Adresse* foundAdresse = itFound->second;
                //wcout << "Found adresse: " << *foundAdresse << endl;
            }
        }
    }
    auto startSearch2 = steady_clock::now();
    auto diff3_2 = startSearch2 - startSearch1;
    wcout << "Time for searching 1: " <<
            duration_cast<milliseconds>(diff3_2).count() << "ms." << endl;
    wcout << "Performing 1x" << searchRequests1.size() << " search requests 2 ..."
         << endl;
    const Adresse* lastFoundAdresse = 0;
    for (int i=0; i<1; i++) {
        for (const HausnummerPlzExact& searchRequest : searchRequests2) {
            SearchMap2::const_iterator itFound = addressMap2.find(searchRequest);
            if (itFound != addressMap2.end()) {
                lastFoundAdresse = itFound->second;
            }
        }
    }
    if (lastFoundAdresse) {
        wcout << "Last found adresse: " << *lastFoundAdresse << endl;
    }
    auto end = steady_clock::now();
    auto diff4 = end - startSearch2;
    wcout << "Time for searching 2: " <<
            duration_cast<milliseconds>(diff4).count() << "ms." << endl;
    //wcout << *addresses.begin() << endl;
    auto diff5 = end - start;
    wcout << "Overall time: " << duration_cast<milliseconds>(diff5).count()
         << "ms." << endl;
    wcout << "Number of Vorname/Name comparisons=" <<
            VornameNameExact::getNumberOfComparisons() << endl;
    wcout << "Number of hausnummer/PLZ comparisons=" <<
            HausnummerPlzExact::getNumberOfComparisons() << endl;
}

