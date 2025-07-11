#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <algorithm>
#include <cctype>
#include <limits.h>
#include <queue>
#include <set>
#include <limits>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
using namespace std;

void exit();
void displayFunctions();
void showmap();
void home();
void cheapest();
void fastest();
void addStation();

int stationIdUsed = -1; // To maintain station Id

class node // For Tries
{
public:
    char c;
    unordered_map<char, node*> m;
    bool t;

    node(char ch)
    {
        c = ch;
        t = false;
    }
};

class Stations // implementation of Tries to store all stations
{

    node* station;

public:
    Stations()
    {
        station = new node('\0');
    }

    void insert(string word)
    {
        node* temp = station;
        for (int i = 0; word[i] != '\0'; i++)
        {
            if (temp->m.count(word[i]))
            {
                temp = temp->m[word[i]];
            }
            else
            {
                node* n = new node(word[i]);
                temp->m[word[i]] = n;
                temp = n;
            }
        }

        temp->t = true;
    }

    bool find(string word)
    {
        node* temp = station;

        for (int i = 0; word[i] != '\0'; i++)
        {
            if (temp->m.count(word[i]) == 0)
            {
                return false;
            }
            else
            {
                temp = temp->m[word[i]];
            }
        }
        return temp->t;
    }

    void setStations()
    {
        insert("welcome");
        insert("seelampur");
        insert("shastri park");
        insert("kashmere gate");
        insert("tis hazari");
        insert("pulbangash");
        insert("pratap nagar");
        insert("shastri nagar");
        insert("inderlok");
        insert("kanhaiya nagar");
        insert("netaji subhash place");
        insert("rithala");
        insert("madipur");
        insert("shivaji park");
        insert("punjabi bagh");
        insert("ashok park");
        insert("sat guru ram singh marg");
        insert("kirti nagar");
        insert("shadipur");
        insert("keshav puram");
        insert("patel nagar");
        insert("rajender place");
        insert("karol bagh");
        insert("rajiv chowk");
        insert("barakhamba road");
        insert("mandi house");
        insert("pragati maiden");
        insert("inderprastha");
        insert("yamuna bank");
        insert("vishwavidalaya");
        insert("vidhan sabha");
        insert("civil lines");
        insert("chandni chowk");
        insert("chawri bazar");
        insert("new delhi");
        insert("patel chowk");
        insert("central secretariat");
        insert("udyog bhawan");
        insert("lok kalyan marg");
        insert("jor bagh");
        insert("lal qila");
        insert("jama masjid");
        insert("delhi gate");
        insert("ito");
        insert("janptah");
        insert("khan market");
        insert("jl nehru stadium");
        insert("jangpura");
        insert("rajouri garden");
        insert("ramesh nagar");
        insert("moti nagar");
    }

    void addStation(string word)
    {
        insert(word);
    }
};

Stations s;

class LineColors // To store information about metro colors
{
public:
    unordered_map<string, unordered_set<string>> colors;

    LineColors()
    {
    }

    void setColors()
    {
        colors["welcome"].insert("Red");
        colors["seelampur"].insert("Red");
        colors["shastri park"].insert("Red");
        colors["kashmere gate"].insert("Red");
        colors["kashmere gate"].insert("Yellow");
        colors["kashmere gate"].insert("Violet");
        colors["tis hazari"].insert("Red");
        colors["pulbangash"].insert("Red");
        colors["pratap nagar"].insert("Red");
        colors["shastri nagar"].insert("Red");
        colors["inderlok"].insert("Green");
        colors["inderlok"].insert("Red");
        colors["kanhaiya nagar"].insert("Red");
        colors["netaji subhash place"].insert("Red");
        colors["rithala"].insert("Red");
        colors["madipur"].insert("Green");
        colors["shivaji park"].insert("Green");
        colors["punjabi bagh"].insert("Green");
        colors["ashok park"].insert("Green");
        colors["sat guru ram singh marg"].insert("Green");
        colors["kirti nagar"].insert("Green");
        colors["kirti nagar"].insert("Blue");
        colors["shadipur"].insert("Blue");
        colors["keshav puram"].insert("Red");
        colors["patel nagar"].insert("Blue");
        colors["rajender place"].insert("Blue");
        colors["karol bagh"].insert("Blue");
        colors["rajiv chowk"].insert("Blue");
        colors["rajiv chowk"].insert("Yellow");
        colors["barakhamba road"].insert("Blue");
        colors["mandi house"].insert("Blue");
        colors["mandi house"].insert("Violet");
        colors["pragati maiden"].insert("Blue");
        colors["inderprastha"].insert("Blue");
        colors["yamuna bank"].insert("Blue");
        colors["vishwavidalaya"].insert("Yellow");
        colors["vidhan sabha"].insert("Yellow");
        colors["civil lines"].insert("Yellow");
        colors["chandni chowk"].insert("Yellow");
        colors["chawri bazar"].insert("Yellow");
        colors["new delhi"].insert("Yellow");
        colors["patel chowk"].insert("Yellow");
        colors["central secretariat"].insert("Yellow");
        colors["central secretariat"].insert("Violet");
        colors["udyog bhawan"].insert("Yellow");
        colors["lok kalyan marg"].insert("Yellow");
        colors["jor bagh"].insert("Yellow");
        colors["lal qila"].insert("Violet");
        colors["jama masjid"].insert("Violet");
        colors["delhi gate"].insert("Violet");
        colors["ito"].insert("Violet");
        colors["janptah"].insert("Violet");
        colors["khan market"].insert("Violet");
        colors["jl nehru stadium"].insert("Violet");
        colors["jangpura"].insert("Violet");
        colors["rajouri garden"].insert("Blue");
        colors["ramesh nagar"].insert("Blue");
        colors["moti nagar"].insert("Blue");
    }

    void addColors(string station, vector<string>& color)
    {
        for (auto x : color)
        {
            colors[station].insert(x);
        }
    }
};

LineColors c;

class Mapping // mapping stations with codes
{
public:
    vector<string> stationFromId;

    Mapping()
    {
        stationFromId.resize(51);
        stationIdUsed = 50;
    }

    void setMapping()
    {
        stationFromId[0] = "welcome";
        stationFromId[1] = "seelampur";
        stationFromId[2] = "shastri park";
        stationFromId[3] = "kashmere gate";
        stationFromId[4] = "tis hazari";
        stationFromId[5] = "pulbangash";
        stationFromId[6] = "pratap nagar";
        stationFromId[7] = "shastri nagar";
        stationFromId[8] = "inderlok";
        stationFromId[9] = "kanhaiya nagar";
        stationFromId[10] = "keshav puram";
        stationFromId[11] = "netaji subhash place";
        stationFromId[12] = "rithala";
        stationFromId[13] = "madipur";
        stationFromId[14] = "shivaji park";
        stationFromId[15] = "punjabi bagh";
        stationFromId[16] = "ashok park";
        stationFromId[17] = "sat guru ram singh marg";
        stationFromId[18] = "kirti nagar";
        stationFromId[19] = "shadipur";
        stationFromId[20] = "patel nagar";
        stationFromId[21] = "rajender place";
        stationFromId[22] = "karol bagh";
        stationFromId[23] = "rajiv chowk";
        stationFromId[24] = "barakhamba road";
        stationFromId[25] = "mandi house";
        stationFromId[26] = "pragati maiden";
        stationFromId[27] = "inderprastha";
        stationFromId[28] = "yamuna bank";
        stationFromId[29] = "vishwavidalaya";
        stationFromId[30] = "vidhan sabha";
        stationFromId[31] = "civil lines";
        stationFromId[32] = "chandni chowk";
        stationFromId[33] = "chawri bazar";
        stationFromId[34] = "new delhi";
        stationFromId[35] = "patel chowk";
        stationFromId[36] = "central secretariat";
        stationFromId[37] = "udyog bhawan";
        stationFromId[38] = "lok kalyan marg";
        stationFromId[39] = "jor bagh";
        stationFromId[40] = "lal qila";
        stationFromId[41] = "jama masjid";
        stationFromId[42] = "delhi gate";
        stationFromId[43] = "ito";
        stationFromId[44] = "janptah";
        stationFromId[45] = "khan market";
        stationFromId[46] = "jl nehru stadium";
        stationFromId[47] = "jangpura";
        stationFromId[48] = "rajouri garden";
        stationFromId[49] = "ramesh nagar";
        stationFromId[50] = "moti nagar";
    }

    void addStationId(string station)
    {
        ++stationIdUsed;
        stationFromId.push_back(station);
    }

    void displayAll()
    {
        system("cls");

        cout << "STATION LIST WITH SERIAL NUMBER " << endl
            << endl;

        for (int i = 0; i <= stationIdUsed; ++i)
        {
            cout << i << "    ";
            if (i < 10)
                cout << " ";
            cout << stationFromId[i] << endl;
        }

        cout << endl
            << "Press any key to go back... ";

        cin.get();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        system("cls");
        home();
    }
};

Mapping m;

void generatePath(vector<string>& journey) // to print journey route
{

    string startingColor;
    for (auto x : c.colors[journey[0]])
    {
        if (c.colors[journey[1]].find(x) != c.colors[journey[1]].end())
        {
            startingColor = x;
            break;
        }
    }

    cout << endl
        << " > Start with " << startingColor << " colour line" << endl;

    cout << journey[0];

    for (int i = 1; i < journey.size(); ++i)
    {
        if (c.colors[journey[i]].find(startingColor) != c.colors[journey[i]].end())
        {
            cout << "->" << journey[i];
        }
        else
        {
            for (auto x : c.colors[journey[i - 1]])
            {
                if (c.colors[journey[i]].find(x) != c.colors[journey[i - 1]].end())
                {
                    startingColor = x;
                    break;
                }
            }
            cout << endl
                << endl
                << " > Switch to " << startingColor << " color line" << endl;
            cout << journey[i];
        }
    }
}

class info // for graph
{
public:
    string station;
    int cost;
    double distance;

    info(string s, int c, double d)
    {
        station = s;
        cost = c;
        distance = d;
    }
};

class Lines // graph to store network connection
{
    unordered_map<string, list<info>> line;

public:
    void addLine(string a, string b, int c, double d)
    {
        info temp1(a, c, d);
        info temp2(b, c, d);
        line[a].push_back(temp2);
        line[b].push_back(temp1);
    }

    void setLines()
    {
        addLine("rithala", "netaji subhash place", 30, 5.2);
        addLine("netaji subhash place", "keshav puram", 10, 1.2);
        addLine("keshav puram", "kanhaiya nagar", 10, 0.8);
        addLine("kanhaiya nagar", "inderlok", 10, 1.2);
        addLine("madipur", "shivaji park", 10, 1.1);
        addLine("shivaji park", "punjabi bagh", 10, 1.6);
        addLine("punjabi bagh", "ashok park", 10, 0.9);
        addLine("ashok park", "sat guru ram singh marg", 10, 1.1);
        addLine("ashok park", "inderlok", 10, 1.4);
        addLine("rajouri garden", "ramesh nagar", 10, 1);
        addLine("ramesh nagar", "moti nagar", 10, 1.2);
        addLine("inderlok", "shastri nagar", 10, 1.2);
        addLine("moti nagar", "kirti nagar", 10, 1);
        addLine("sat guru ram singh marg", "kirti nagar", 10, 1);
        addLine("shastri nagar", "pratap nagar", 10, 1.7);
        addLine("kirti nagar", "shadipur", 10, 0.7);
        addLine("pratap nagar", "pulbangash", 10, 0.8);
        addLine("vishwavidalaya", "vidhan sabha", 10, 1);
        addLine("shadipur", "patel nagar", 10, 1.3);
        addLine("pulbangash", "tis hazari", 10, 0.9);
        addLine("vidhan sabha", "civil lines", 10, 1.3);
        addLine("patel nagar", "rajender place", 10, 0.9);
        addLine("tis hazari", "kashmere gate", 10, 1.1);
        addLine("civil lines", "kashmere gate", 10, 1.1);
        addLine("rajender place", "karol bagh", 10, 1);
        addLine("kashmere gate", "shastri park", 20, 2.2);
        addLine("kashmere gate", "lal qila", 10, 1.5);
        addLine("kashmere gate", "chandni chowk", 10, 1.1);
        addLine("shastri park", "seelampur", 10, 1.6);
        addLine("lal qila", "jama masjid", 10, 0.8);
        addLine("chandni chowk", "chawri bazar", 10, 1);
        addLine("seelampur", "welcome", 10, 1.1);
        addLine("jama masjid", "delhi gate", 10, 1.4);
        addLine("chawri bazar", "new delhi", 10, 0.8);
        addLine("karol bagh", "rajiv chowk", 20, 3.4);
        addLine("new delhi", "rajiv chowk", 10, 1.1);
        addLine("delhi gate", "ito", 10, 1.3);
        addLine("rajiv chowk", "barakhamba road", 10, 0.7);
        addLine("rajiv chowk", "patel chowk", 10, 1.3);
        addLine("ito", "mandi house", 10, 0.8);
        addLine("barakhamba road", "mandi house", 10, 1);
        addLine("mandi house", "pragati maiden", 10, 0.8);
        addLine("mandi house", "janptah", 10, 1.4);
        addLine("inderprastha", "pragati maiden", 10, 0.8);
        addLine("janptah", "central secretariat", 10, 1.3);
        addLine("patel chowk", "central secretariat", 10, 0.9);
        addLine("inderprastha", "yamuna bank", 10, 1.8);
        addLine("central secretariat", "udyog bhawan", 10, 0.3);
        addLine("central secretariat", "khan market", 20, 2.1);
        addLine("udyog bhawan", "lok kalyan marg", 10, 1.6);
        addLine("khan market", "jl nehru stadium", 10, 1.4);
        addLine("lok kalyan marg", "jor bagh", 10, 1.2);
        addLine("jl nehru stadium", "jangpura", 10, 0.9);
    }

    void displayNetwork()
    {
        system("cls");
        cout << "NETWORK CONNECTION OF ALL STATIONS " << endl
            << endl;

        for (auto x : line)
        {
            cout << "Station '" << x.first << "' is connected to ->" << endl;
            for (auto y : x.second) // or auto x:m[p.first]
            {
                cout << "     " << y.station << " by cost " << y.cost << " and distance " << y.distance << endl;
            }
            cout << endl;
        }

        cout << endl;
        cout << "Press any key to go back... ";

        cin.get();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        system("cls");
        home();
    }

    void cheapestRoute(string src, string dest)
    {

        unordered_map<string, int> visitedCost;
        unordered_map<string, string> parent;

        for (int i = 0; i <= stationIdUsed; ++i)
        {
            visitedCost[m.stationFromId[i]] = INT_MAX;
            parent[m.stationFromId[i]] = "none";
        }

        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;

        visitedCost[src] = 0;
        pq.push({ 0, src });

        while (!pq.empty())
        {

            auto t = pq.top();
            pq.pop();

            int c = t.first;
            string stat = t.second;

            if (stat == dest)
                break;

            for (auto nbr : line[stat])
            {
                string nbrstat = nbr.station;
                int addc = nbr.cost;

                if (visitedCost[nbrstat] > addc + c)
                {
                    visitedCost[nbrstat] = addc + c;
                    parent[nbrstat] = stat;
                    pq.push({ visitedCost[nbrstat], nbrstat });
                }
            }
        }

        string temp = dest;
        vector<string> journey;

        while (temp != "none")
        {
            journey.push_back(temp);
            temp = parent[temp];
        }

        reverse(journey.begin(), journey.end());
        generatePath(journey);

        cout << endl
            << endl
            << "*** Total cost of journey will be rupees " << visitedCost[dest] << " ***" << endl
            << endl
            << endl;
    }

    void ShortestRoute(string src, string dest)
    {

        unordered_map<string, double> visitedDist;
        unordered_map<string, string> parent;

        for (int i = 0; i <= stationIdUsed; ++i)
        {
            visitedDist[m.stationFromId[i]] = INT_MAX;
            parent[m.stationFromId[i]] = "none";
        }

        priority_queue<pair<double, string>, vector<pair<double, string>>, greater<pair<double, string>>> pq;

        visitedDist[src] = 0;
        pq.push({ 0, src });

        while (!pq.empty())
        {

            auto t = pq.top();
            pq.pop();

            double d = t.first;
            string stat = t.second;

            if (stat == dest)
                break;

            for (auto nbr : line[stat])
            {
                string nbrstat = nbr.station;
                double addd = nbr.distance;

                if (visitedDist[nbrstat] > addd + d)
                {
                    visitedDist[nbrstat] = addd + d;
                    parent[nbrstat] = stat;
                    pq.push({ visitedDist[nbrstat], nbrstat });
                }
            }
        }

        string temp = dest;
        vector<string> journey;

        while (temp != "none")
        {
            journey.push_back(temp);
            temp = parent[temp];
        }
        reverse(journey.begin(), journey.end());
        generatePath(journey);

        cout << endl
            << endl
            << "*** Total Distance of journey will be " << visitedDist[dest] << " kms ***" << endl
            << endl
            << endl;
    }
};

Lines l;

void getReady() // to initialize the application
{
    s.setStations();

    m.setMapping();

    c.setColors();

    l.setLines();
}

int main()
{

    getReady();
    home();
    system("cls");
    exit();

    return 0;
}

void displayFunctions()
{
    const char* homeText = R"(
  _____  ______ _      _    _ _____    __  __ ______ _______ _____   ____     _____            _____ _      
 |  __ \|  ____| |    | |  | |_   _|  |  \/  |  ____|__   __|  __ \ / __ \   |  __ \     /\   |_   _| |     
 | |  | | |__  | |    | |__| | | |    | \  / | |__     | |  | |__) | |  | |  | |__) |   /  \    | | | |     
 | |  | |  __| | |    |  __  | | |    | |\/| |  __|    | |  |  _  /| |  | |  |  _  /   / /\ \   | | | |     
 | |__| | |____| |____| |  | |_| |_   | |  | | |____   | |  | | \ \| |__| |  | | \ \  / ____ \ _| |_| |____ 
 |_____/|______|______|_|  |_|_____|  |_|  |_|______|  |_|  |_|  \_\\____/   |_|  \_\/_/    \_\_____|______|
)";

    // Output the hardcoded content
    std::cout << homeText << std::endl;

    cout << "What would you like to do ?" << endl;
    cout << "1. Display List Of Stations" << endl;
    cout << "2. See network of Stations" << endl;
    cout << "3. Complete Map of MetroLines" << endl;
    cout << "4. Cheapest way to reach your Destination" << endl;
    cout << "5. Fastest way to reach your Destination";
    cout << "                                             -1. Add Stations(Admin Only)" << endl
        << endl;
    cout << "Press 0 to exit" << endl
        << endl;
}

void home()
{
    displayFunctions();
    cout << "Enter Your Choice : ";
    int choice;
A:
    cin >> choice;

    switch (choice)
    {

    case 0:
        break;
    case 1:
        m.displayAll();
        break;

    case 2:
        l.displayNetwork();
        break;

    case 3:
        system("cls");
        showmap();
        break;

    case 4:
        system("cls");
        cheapest();
        break;

    case 5:
        system("cls");
        fastest();
        break;

    case -1:
        system("cls");
        addStation();
        break;

    default:
        system("cls");
        displayFunctions();
        cout << "Oops!!! Invalid Input.... Enter your choice again : ";
        goto A;
    }
}

void showmap()
{
    cout << "----------------------------------------------------METRO LINES NETWORK-------------------------------------------------" << endl
        << endl;
    const char* metroMap = R"(
                            Rithala (R)                                        Madipur (G)
                            |                                                   |
                            |                                                   |
                            |                                                   |
                            |                                                   |
                            |                                                   |
                    Netaji Subhash Place (R)                             Shivaji Park (G)
                            |                                                   |
                            |                                                   |
                            |                                                   |
                            |                                                   |
                            |                                                   |
                       Keshav Puram (R)       Ranjouri Garden (B)        Punjabi Bagh (G)
                            |                         |                         |
                            |                         |                         |
                            |                         |                         |
                            |                         |                         |
                            |                         |                         |
                       Kanhaiya Nagar (R)       Ramesh Nagar (B)            Ashok Park (G)
                            |                         |                    /    |
                            |                         |                   /     |
                            |      /------------------|------------------/      |
                            |     /                   |                         |
                            |    /                    |                         |
                        Inderlok (R)              Moti Nagar (B)        Sat Guru Ram Singh Marg (G)
                            |                          \                        |   
                            |                           \                       |
                            |                            \-------------------\  |
                            |                                                 \ |
                            |                                                  \| 
                       Shastri Nagar (R)	                          Kirti Nagar (B,G)
                            |                                                   |
                            |                                                   |
                            |                                                   |
                            |                                                   |
                            |                                                   |
                       Pratap Nagar (R)        Vishwavidalaya (Y)               |
                            |                         |                         |
                            |                         |                         |
                            |                         |                     Shadipur (B)
                            |                         |                         |
                            |                         |                         |
                        Pulbangash (R)          Vidhan Sabha (Y)                |
                            |                         |                         |
                            |                         |                         |
                            |                         |                   Patel Nagar (B)
                            |                         |                         |
                            |                         |                         |
                       Tis Hazari (R)            Civil Lines (Y)                |
                            |                        /                          |
                            |                       /                           |
                            |  /-------------------/                     Rajender Place (B)
                            | /                                                 |
                            |/                                                  |
                      Kashmere Gate (R,V,Y)                                     |
                           /|\                                                  |
                          / | \                                                 |
       /-----------------/  |  \-----------------\                         Karol Bagh (B)
      /                     |                     \                             |
     /                      |                      \                            |
Shastri Park (R)         Lal Qila (V)         Chandni Chowk (Y)                 |
     |                      |                         |                         |
     |                      |                         |                         |
     |                      |                         |                         |
     |                      |                         |                         |
     |                      |                         |                         |
 Seelampur (R)          Jama Masjid (V)         Chawri Bazar (Y)                |
     |                      |                         |                         |
     |                      |                         |                         |
     |                      |                         |                         |
     |                      |                         |                         |
     |                      |                         |                         |
  Welcome (R)           Delhi Gate (V)            New Delhi (Y)                 |
                            |                          \                        |
                            |                           \---------------------\ |
                            |                                                  \|
                            |                                              Rajiv Chowk (Y,B)
                            |                                                  /|  
                           ITO (V)                         /------------------/ |
                            |                             /                     |
                            |                     Barakhamba Road (B)           |
                            |                           /                       |
                            | /------------------------/                        |
                            |/                                             Patel Chowk (Y)
                      Mandi House (V,B)                                       / 
                            |\                                               / 
                            | \                                             /  
                            |  \------------------\                        /  
                            |                      \                      /  
                            |                       \          /---------/  
                       Pragati Maiden (B)        Janptah (V)  /  
                            |                         |      /  
                            |                         |     /  
                            |                         |    /   
                            |                         |   /  
                            |                         |  /  
                       Indraprastha (B)     Central Secretariat (V,Y)
                            |                         |\
                            |                         | \
                            |                         |  \-------------------\
                            |                         |                       \
                            |                         |                        \
                        Yamuna Bank (B)         Udyog Bhawan (Y)           Khan Market (V)
                                                      |                         |
                                                      |                         |
                                                      |                         |
                                                      |                         |
                                                      |                         |
                                              Lok Kalyan Marg (Y)        JL Nehru Stadium (V)
                                                      |                         |
                                                      |                         |
                                                      |                         |
                                                      |                         |
                                                      |                         |
                                                  Jor Bagh (Y)             Jangpura (V)
    )";

    // Output the hardcoded metro map
    std::cout << metroMap << std::endl;
    cout << endl
        << "------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << endl
        << "Press any key to go back...";
    cin.get();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    system("cls");
    home();
}

void cheapest()
{
    string src, dest;
    cin.ignore();
B:
    cout << "Enter starting station ('back' to go back): ";
    string org;
    getline(cin, src);
    org = src;
    bool digit = true;
    for (int i = 0; i < src.length(); ++i)
    {
        if (src[i] < '0' || src[i] > '9')
            digit = false;
    }

    if (digit)
    {
        if (stoi(src) >= 0 && stoi(src) <= stationIdUsed)
            src = m.stationFromId[stoi(src)];
    }

    for (int i = 0; !digit && i < src.length(); ++i)
    {
        if (src[i] >= 'A' && src[i] <= 'Z')
            src[i] += 32;
    }
    if (src == "back")
    {
        system("cls");
        home();
        return;
    }
    if (!s.find(src))
    {
        system("cls");
        cout << "Invalid Starting Location" << endl
            << endl;
        goto B;
    }

C:
    cout << "Enter destination station ('back' to go back): ";
    getline(cin, dest);

    digit = true;
    for (int i = 0; i < dest.length(); ++i)
    {
        if (dest[i] < '0' || dest[i] > '9')
            digit = false;
    }

    if (digit)
    {
        if (stoi(dest) >= 0 && stoi(dest) <= stationIdUsed)
            dest = m.stationFromId[stoi(dest)];
    }

    for (int i = 0; !digit && i < dest.length(); ++i)
    {
        if (dest[i] >= 'A' && dest[i] <= 'Z')
            dest[i] += 32;
    }
    if (dest == "back")
    {
        system("cls");
        home();
        return;
    }
    if (!s.find(dest))
    {
        system("cls");

        cout << "Invalid Destination Location" << endl
            << endl;
        cout << "Enter starting location : " << org << endl;
        goto C;
    }
    system("cls");
    l.cheapestRoute(src, dest);

    cout << endl
        << endl;

    cout << "Press any key to go back... ";
    cin.get();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    system("cls");
    home();
}

void fastest()
{
    string src, dest;
    cin.ignore();
B:
    cout << "Enter starting station ('back' to go back): ";
    string org;
    getline(cin, src);
    org = src;
    bool digit = true;
    for (int i = 0; i < src.length(); ++i)
    {
        if (src[i] < '0' || src[i] > '9')
            digit = false;
    }

    if (digit)
    {
        if (stoi(src) >= 0 && stoi(src) <= stationIdUsed)
            src = m.stationFromId[stoi(src)];
    }

    for (int i = 0; !digit && i < src.length(); ++i)
    {
        if (src[i] >= 'A' && src[i] <= 'Z')
            src[i] += 32;
    }
    if (src == "back")
    {
        system("cls");
        home();
        return;
    }
    if (!s.find(src))
    {
        system("cls");
        cout << "Invalid Starting Location" << endl
            << endl;
        goto B;
    }

C:
    cout << "Enter destination station ('back' to go back): ";
    getline(cin, dest);

    digit = true;
    for (int i = 0; i < dest.length(); ++i)
    {
        if (dest[i] < '0' || dest[i] > '9')
            digit = false;
    }

    if (digit)
    {
        if (stoi(dest) >= 0 && stoi(dest) <= stationIdUsed)
            dest = m.stationFromId[stoi(dest)];
    }

    for (int i = 0; !digit && i < dest.length(); ++i)
    {
        if (dest[i] >= 'A' && dest[i] <= 'Z')
            dest[i] += 32;
    }
    if (dest == "back")
    {
        system("cls");
        home();
        return;
    }
    if (!s.find(dest))
    {
        system("cls");

        cout << "Invalid Destination Location" << endl
            << endl;
        cout << "Enter starting location : " << org << endl;
        goto C;
    }
    system("cls");
    l.ShortestRoute(src, dest);

    cout << endl
        << endl;

    cout << "Press any key to go back... ";
    cin.get();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    system("cls");
    home();
}

void addStation()
{
    system("cls");

    string pass;
    cout << "Enter Password ('back' to go back): ";
    char ch = 'A';

    while (ch != 13) // 13 is ASCII value of Enter key
    {
        ch = cin.get();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (isprint(ch))
        {
            cout << "*";
            pass.push_back(ch);
        }

        else if (ch == 8 && pass.length()) // 8 is ASCII value of Backspace key
        {
            pass.pop_back();
            cout << ("\b \b");
        }
    }

    if (pass == "back")
    {
        system("cls");
        home();
        return;
    }
    else if (pass != "yes")
    {
        system("cls");
        cout << "ERROR!!!! INVALID PASSWORD ! ";
        cout << endl
            << endl;
        cout << "Press any key to go back and try again... ";
        cin.get();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        addStation();
        return;
    }

    system("cls");
    cout << "***Login Successful***" << endl
        << endl;

    string name;
    cout << "Enter station Name : ";
    cin.ignore();

    getline(cin, name);
    s.addStation(name);
    m.addStationId(name);

    vector<string> color;
    string temp;
    int i = 1;

    while (i)
    {
        cout << "Enter color number " << i << " (NULL to stop entering): ";
        getline(cin, temp);
        if (temp == "NULL")
            break;
        color.push_back(temp);
        i++;
    }

    c.addColors(name, color);
    i = 1;
    int c;
    double d;
    while (i)
    {
        cout << "Enter directly connected Station number " << i << " (NULL to stop entering): ";
        if (i > 1)
            cin.ignore();
        getline(cin, temp);
        if (temp == "NULL")
            break;
        cout << "Enter cost of travel : ";
        cin >> c;
        cout << "Enter distance between stations : ";
        cin >> d;
        l.addLine(name, temp, c, d);
        i++;
    }

    cout << endl;

    cout << "Adding Station";
    for (int i = 1; i < 6; i++)
    {
        for (int j = 0; j < 200000000; j++)
        {
        }
        cout << ".";
    }
    cout << endl
        << endl;

    cout << "Station added successfully... " << endl;
    cout << "Press any key to go back...";
    cin.get();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    system("cls");
    home();
}

void exit()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Thank You - Delhi Metro App");

    // Load background image
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("background")) {
        std::cerr << "Failed to load background.png\n";
        return;
    }
    sf::Sprite background(backgroundTexture);

    // Scale background to fit the window
    sf::Vector2u textureSize = backgroundTexture.getSize();
    sf::Vector2u windowSize = window.getSize();
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
    background.setScale(scaleX, scaleY);

    // Load train image
    sf::Texture trainTexture;
    if (!trainTexture.loadFromFile("t3")) {
        std::cerr << "Failed to load train.png\n";
        return;
    }
    sf::Sprite train(trainTexture);

    // Position train in the center vertically
    float trainY = (windowSize.y - trainTexture.getSize().y) / 2.0f;
    train.setPosition(-static_cast<float>(trainTexture.getSize().x), trainY); // start off screen

    // Load font
    sf::Font font;
    if (!font.loadFromFile("Roboto_Condensed-Medium.ttf")) {
        std::cerr << "Failed to load font\n";
        return;
    }

    // Setup text for typewriter effect (larger size)
    std::string fullText = "Thank you for using Delhi Metro Route Finder!";
    std::string currentText = "";
    sf::Text typeText("", font, 40); // larger text size
    typeText.setFillColor(sf::Color::White);
    typeText.setPosition(50, 50); // more padding from top-left

    size_t charIndex = 0;
    sf::Clock typeClock;
    float charDelay = 0.05f;

    // Clock for train animation
    sf::Clock trainClock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Typewriter effect
        if (charIndex < fullText.size() && typeClock.getElapsedTime().asSeconds() > charDelay) {
            currentText += fullText[charIndex++];
            typeText.setString(currentText);
            typeClock.restart();
        }

        // Train animation
        float trainSpeed = 150.0f; // faster movement
        float elapsed = trainClock.restart().asSeconds();
        train.move(trainSpeed * elapsed, 0);
        if (train.getPosition().x > windowSize.x) {
            train.setPosition(-static_cast<float>(train.getGlobalBounds().width), trainY);
        }

        window.clear();
        window.draw(background);
        window.draw(train);
        window.draw(typeText);
        window.display();
    }
}

