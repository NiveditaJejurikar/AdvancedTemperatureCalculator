/*
 * nsj8P4.cpp
 *
 * COSC 051 Summer 2015
 * Project #4
 *
 * Due on: AUG 5, 2015
 * Author: Nivu Jejurikar
 *
 *
 * In accordance with the class policies and Georgetown's
 * Honor Code, I certify that, with the exception of the
 * class resources and those items noted below, I have neither
 * given nor received any assistance on this project.
 *
 * References not otherwise commented within the program source code.
 * Note that you should not mention any help from the TAs, the professor,
 * or any code taken from the class textbooks.
 */

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include <stdio.h>

using namespace std;

class TemperatureReading
{
    friend ostream& operator<<(ostream &os, const TemperatureReading &rhsObj);
    friend istream& operator>>(istream &is, TemperatureReading &rhsObj);
    
private:
    double temperatureValue;
    char scale;
    int year;
    int month;
    int day;
    string analystName;
    TemperatureReading *next;
    
public:
    // non-inline functions
    TemperatureReading();
    TemperatureReading( double v, char s, int y, int m, int d, string n );
    TemperatureReading( const TemperatureReading &otherObj );
    ~TemperatureReading();
    
    // potential inline functions
    void setTemperature( double tVal );
    void setName( string nVal );
    void setScale( char sVal );
    
    double getTemperature() { return temperatureValue; }

    char getScale() { return scale; }
    int getYear() { return year; }
    int getMonth() { return month; }
    int getDay() { return day; }
    string getName() { return analystName; }
    
    TemperatureReading* getNext()  { return next; }
    void setNext( TemperatureReading *n ) { next = n; }
    
    // non-inline functions
    void setDate(int yyyy, int mm, int dd);
    
    double getFahrenheit(float temperatureInCelsius) const;
    double getKelvin(float temperatureInCelsius) const;
    double getRankine(float temperatureInCelsius) const;
    double getNewton(float temperatureInCelsius) const;
    bool isValidScale(char scaleReading, TemperatureReading &tmp) const;
    
    
}; //END TemperatureReading class delcaration

TemperatureReading::TemperatureReading()
//default constructor
{
    temperatureValue = 0;
    scale = 0;
    year = 0;
    month = 0;
    day = 0;
    analystName = "";
    
    next = NULL;
}

TemperatureReading::TemperatureReading( double v, char s, int y, int m, int d, string n )
// constructor w/ parameters
{
    temperatureValue = v;
    scale = s;
    year = y;
    month = m;
    day = d;
    analystName = n;
}

TemperatureReading::TemperatureReading( const TemperatureReading &tmpReading )
//copy constructor
{
    this->temperatureValue = tmpReading.temperatureValue;
    this->scale = tmpReading.scale;
    this->year = tmpReading.year;
    this->month = tmpReading.month;
    this->day = tmpReading.day;
    this->analystName = tmpReading.analystName;
    
    this->next = NULL;
}

TemperatureReading::~TemperatureReading() //destructor
{}

void TemperatureReading::setTemperature( double tVal )
{
    temperatureValue = tVal;
    cout << "stored temp value is " << tVal << endl;
}

void TemperatureReading::setName( string nVal )
{
    analystName = nVal;
    cout <<	"stored name is " << nVal << endl;
}

void TemperatureReading::setScale( char sVal )
{
    scale = sVal;
    cout << "stored scale value is " << sVal << endl;
}

void TemperatureReading::setDate(int yyyy, int mm, int dd)
{
    year = yyyy;
    month = mm;
    day = dd;
    cout << "stored date is " << yyyy << "/" << mm << "/" << dd << endl;
}

istream& operator>>(istream &is, TemperatureReading &tmpReading)
{
    char ch = 'A';
    is >> tmpReading.temperatureValue >> tmpReading.scale >> tmpReading.year;
    is >> ch >> tmpReading.month >> ch >> tmpReading.day && getline(is,tmpReading.analystName);
    TemperatureReading Scale;
    return is;
} //END overloaded stream extraction operator for TemperatureReading class

ostream& operator<<(ostream &os, const TemperatureReading &tmpReading)
{
    os << tmpReading.temperatureValue << ", ";
    os << tmpReading.scale << ", ";
    os << tmpReading.year << " X ";
    os << tmpReading.month << ", ";
    os << tmpReading.day << ", ";
    os << tmpReading.analystName << ", ";
    
    return os;
}

/*****************************************
 END OF CLASS TempRead
 
 *****************************************/

// FUNCTION PROTOTYPES
char presentMenu();
void processSingleEntry();
bool validTemperatureScale(char temperatureScale);

//new P4 functions
void loadBulkData(TemperatureReading* &listHead, TemperatureReading* &listTail);
void reportBulkData(TemperatureReading* listHead);
void unloadBulkData(TemperatureReading* &listHead, TemperatureReading* &listTail);
void addMe (TemperatureReading* &new_TR);

int main()
{
    TemperatureReading *listHead = NULL;
    TemperatureReading *listTail = NULL;
    
    //store the user's menu option in the variable userChoice
    char userChoice = 'A';
    
    //continue to present the menu after executing the menu choice
    //as long as the user does not pick 'q', or 'quit'
    while( (userChoice != 'q') && (userChoice != 'Q') )
    {
        userChoice = presentMenu();
        switch (userChoice)
        {
                //if the user enters s then call the single entry function
            case 's':
            case 'S':
                processSingleEntry();
                break;
                //if the user enters s then process single entry
            case 'b':
            case 'B':
                loadBulkData(listHead, listTail);
                break;
                //if the user enters b then load bulk data
            case 'r':
            case 'R':
                reportBulkData(listHead);
                break;
                //if the user enters r then report bulk data
                //if data has not previously been loaded, display error msg
            case 'c':
            case 'C':
                unloadBulkData(listHead, listTail);
                break;
                //if the user enters c then unload bulk data
                //if data has not previously been loaded, display error msg
            case 'q':
            case 'Q':
                unloadBulkData(listHead, listTail);
                cout<<"Quitting program..."<<endl;
                break;
                //if the user enters q then unload bulk data and display quit msg
            default:
                cout<< "Incorrect command. Try again.\n\n";
                break;
        } // end of switch
    }
    
    cout << "The program will quit now" << endl;
    return 0;
    //if the user chooses 'q', terminate program
} // end of main

char presentMenu() //use this function to repeatedly display menu
{
    //define the variable that will store the menu choice of the user
    char userChoice[15];
    
    cout << "Welcome to the Alleghany Calculator Specialists (ACS) ";
    cout << "AllTemp Conversion System." << endl;
    cout << "\ts - Single entry from keyboard\n";
    cout << "\tb - Bulk entry from file\n";
    cout << "\tr - Bulk data Report\n";
    cout << "\tc - Clear all bulk data\n";
    cout << "\tq - Quit\n";
    
    //prompt the user to enter a menu choice
    cout << "Please enter the letter corresponding to one of the options above" << endl;
    
    //store user input in the variable userChoice
    cin >> userChoice[0];
    
    //return the first character of user input
    return userChoice[0];
}

bool validTemperatureScale(char temperatureScale) //validate tempscale input for single entry
{
    if ( (temperatureScale == 'c') || (temperatureScale == 'C')
        || (temperatureScale == 'f') || (temperatureScale == 'F') )
    {
        return 1;
    }
    else
    {
        cout << "Please enter a valid temperature scale";
        cout << " that begins with either 'C' or 'F' lower or upper case" << endl;
        return 0;
    }
}

void loadBulkData( TemperatureReading* &listHead, TemperatureReading* &listTail )
{
    //define the string for the headings of the temp readings data
    string headings = " ";
    //name the temp readings data 'fileName'
    ifstream inFile;
    string fileName = "";
    
    //name the counter for the number of nodes in list
    int NodeCount = 0;
    
    //prompt user to enter file name and store in fileName
    cout << "Please enter the file name to process." << endl;
    cin >> fileName;
    
    //define the variable to be entered in isValidScale
    char scaleReading;
    
    //if file opened fails, display error msg
    inFile.open(fileName.c_str());
    if (!inFile)
    {
        cout << "ERROR reading file, no new data will be loaded..." << endl;
        return;
    }
    else
    {
        getline(inFile, headings);
        
        TemperatureReading tmp;
        TemperatureReading *new_TR;
        
        while(inFile>> tmp)
        {
            TemperatureReading *tmpReading;
            tmpReading = new TemperatureReading (tmp);
            
            if (listHead == NULL)
            {
                listHead = listTail = tmpReading;
                NodeCount++; //if the list is empty set head to tail and increment NodeCount
            }
           
            else
            //else set the new pointer the head and input scale values into the variable scaleReading
            {
                new_TR = listHead;
                scaleReading = tmp.getScale();
                if (tmp.isValidScale(scaleReading, tmp))
                {
                    addMe(new_TR);
                    new_TR->setNext(tmpReading);
                    listTail = tmpReading;
                    //if scale valid, call addMe to create new node
                    //advance the pointer and increment NodeCount
                    NodeCount++;
                }
            }
        }//end of while loop
        
        inFile.close(); // close the open file before leaving the function.
            
        //display the number of items loaded
        cout << endl << NodeCount << " new data records were loaded." << endl << endl;
        return;
    } // END of else
} // END loadBulkData function

void addMe (TemperatureReading* &new_TR) //create new nodes
{
        while(new_TR->getNext() != NULL)
            new_TR = new_TR->getNext();
        //while the pointer to the next node is not empty,
        //advance the pointer and set it to the previous one
}

void reportBulkData( TemperatureReading * listHead )
{
    cout << "Entered function reportBulkData" << endl;
    //temp variables
    const float CELSIUS_CONVERTER_MULTIPLIER = 0.555555555;
    const float CELSIUS_CONVERTER_CONSTANT = 32;
    double temperatureInCelsius = 0;
    float temperatureInFahrenheit = 0;
    double temperatureInKelvin = 0;
    double temperatureInRankine = 0;
    double temperatureInNewton = 0;
    double CelsiusTotal = 0;
    double FahrenheitTotal = 0;
    double KelvinTotal = 0;
    double RankineTotal = 0;
    double NewtonTotal = 0;
    double CelsiusAvg = 0;
    double FahrenheitAvg = 0;
    double KelvinAvg = 0;
    double RankineAvg = 0;
    double NewtonAvg = 0;
    
    int rowCount_ValidData = 0;
    
    //new obj to call get functions
    TemperatureReading tmpObj;
    
    if (listHead == NULL) //if list is empty display error msg
    {
        cout << "The bulk data has not been loaded. ";
        cout << "Please select menu option b and load data before requesting report" << endl;
        return;
    }
    else
    {
        //print the heading
        cout << "                            Temperature Scale" << endl;
        cout << "\tDate" << setw(17) << "C" << setw(11) << "F" << setw(11);
        cout << "K" << setw(11) <<  "R" << setw(11) <<  "N" << "\t\t     Analyst" << endl;
        cout << "___________________________________________________";
        cout << "_____________________________________________" << endl;
        
        while (listHead != NULL)
        {
            rowCount_ValidData++;
            cout << "  " << listHead->getYear() << "/";
            cout << right << setw(2) << setfill('0');
            cout << listHead->getMonth() << "/";
            cout << right << setw(2) << setfill('0');
            cout << listHead->getDay() << "     ";
            cout << setfill(' '); //print date and increment row counter
            
            //whether scale is c or f, store appropriate values in tmpCelsius and tmpFahrenheit
            if (listHead->getScale() == 'C' || listHead->getScale() == 'c')
            {
            temperatureInCelsius = listHead->getTemperature();
            temperatureInFahrenheit = (tmpObj.getFahrenheit(temperatureInCelsius));
                
            }
            else if (listHead->getScale() == 'F' || listHead->getScale() == 'f')
            {
            temperatureInCelsius = ((CELSIUS_CONVERTER_MULTIPLIER) * ( (temperatureInFahrenheit) - CELSIUS_CONVERTER_CONSTANT));
            temperatureInFahrenheit = listHead->getTemperature();
            }
            
            //call get functions to convert into various tmp scales then print
            temperatureInKelvin = tmpObj.getKelvin(temperatureInCelsius);
            temperatureInRankine = tmpObj.getRankine(temperatureInCelsius);
            temperatureInNewton = tmpObj.getNewton(temperatureInCelsius);
           
            
            cout << right << setw(11) << fixed << setprecision(2) << temperatureInCelsius;
            cout << right << setw(11) << fixed << setprecision(2) << temperatureInFahrenheit;
            cout << right << setw(11) << fixed << setprecision(2) << temperatureInKelvin;
            cout << right << setw(11) << fixed << setprecision(2) << temperatureInRankine;
            cout << right << setw(11) << fixed << setprecision(2) << temperatureInNewton;
            
            CelsiusTotal += temperatureInCelsius;
            FahrenheitTotal += temperatureInFahrenheit;
            KelvinTotal += temperatureInKelvin;
            RankineTotal += temperatureInRankine;
            NewtonTotal += temperatureInNewton; //keep a running total of temp values

            cout << "     " << listHead->getName() << endl << endl;
            listHead = listHead->getNext(); //print name and advance to the next node
        }
    
    CelsiusAvg = (CelsiusTotal)/(rowCount_ValidData);
    FahrenheitAvg = (FahrenheitTotal)/(rowCount_ValidData);
    KelvinAvg = (KelvinTotal)/(rowCount_ValidData);
    RankineAvg = (RankineTotal)/(rowCount_ValidData);
    NewtonAvg = (NewtonTotal)/(rowCount_ValidData); //calculate average temps
        
    cout << "_________________________________________________";
    cout << "______________________________________________" << endl << endl;
    cout << "\tAverage: " << "\tCelsius: " << CelsiusAvg << "\t   Fahrenheit: ";
    cout << FahrenheitAvg << "\tKelvin: " << KelvinAvg;
    cout << "\t\tRankine:  " << RankineAvg << "\t   Newton: " << NewtonAvg << endl << endl;
    cout << "\t" << rowCount_ValidData << " valid temperature objects are on the linked list";
        //print total nodes and tmp avgs
    cout << endl << endl << "Exiting function ReportBulkData" << endl;
    return;
    }
} // END reportBulkData

void unloadBulkData( TemperatureReading* &listHead, TemperatureReading* &listTail )
{
    TemperatureReading* delete_ptr = listHead;
    TemperatureReading* temp = delete_ptr;
    
    int counter = 0;
    
    if (delete_ptr == NULL) //if list empty display error msg
    {
        cout << "LIST ALREADY EMPTIED" << endl;
    }
    else
    {
        while (delete_ptr != NULL)
        {
            delete_ptr = delete_ptr->getNext();
            delete temp;
            temp = delete_ptr;
            //delete next pointer, then the previous one
            //set temp to head of list
            
            counter++; //incremenet total number of object unloaded and print
        }
        listHead = listTail = NULL;
        cout << endl << counter <<" objects unloaded.\n\n";
    };
} // END unloadBulkData

void processSingleEntry()
{
    //define the constants used in the calculations that convert Celsius
    //temperatures into various temperature scales
    const float DELISLE_CONVERTER_INITIAL = 100;
    const float DELISLE_CONVERTER_FINAL = 1.5;
    const float REAUMUR_CONVERTER = 0.8;
    const float ROMER_CONVERTER_MULTIPLIER = 0.525;
    const float ROMER_CONVERTER_CONSTANT = 7.5;
    const float FAHRENHEIT_CONVERTER_MULTIPLIER = 1.8;
    const float FAHRENHEIT_CONVERTER_CONSTANT = 32;
    const float CELSIUS_CONVERTER_MULTIPLIER = 0.555555555;
    const float CELSIUS_CONVERTER_CONSTANT = 32;
    
    //define the variable temperatureScale as an array of characters
    char temperatureScale;
    
    //define the variables that will express various temperature scales
    float temperatureInDegrees = 0;
    float temperatureInCelsius = 0;
    float temperatureInFahrenheit = 0;
    float Delisle_temp = 0;
    float Reaumur_temp = 0;
    float Romer_temp = 0;
    
    
    cout << "This program accepts a temperature reading (entered in either Fahrenheit or Celsius).\n";
    cout << "Once a valid temperature reading has been entered, the software will convert \n";
    cout << "that value to various other temperature scales.\n";
    cout << "Please enter only the numeric value of the temperature value you want to convert.\n";
    
    //store the temperature value entered by the user
    cin >> temperatureInDegrees;
    cout << "Please enter the temperature scale:" << endl;
    cout << "If the value is in Celsius, enter C" << endl;
    cout << "If the value is in Fahrenheit, enter F" << endl;
    
    //store the scale of the temperature entered by the user
    cin >> temperatureScale;
    cin.ignore(500,'\n');
    if (validTemperatureScale(temperatureScale))
    {
        
        //if the first character of the temperature scale entered is either 'c' or 'C', then store the
        //value entered by the user into the variable temperatureInCelsius. Then, convert the variable
        //temperatureInCelsius into Fahrenheit degrees and store in the variable temperatureInFahrenheit.

        if ((temperatureScale == 'c') || (temperatureScale == 'C'))
        {
            temperatureInCelsius = temperatureInDegrees;
            cout << "Your entry was " << temperatureInCelsius << " degrees Celsius." << endl;
            temperatureInFahrenheit = (temperatureInCelsius * FAHRENHEIT_CONVERTER_MULTIPLIER) + FAHRENHEIT_CONVERTER_CONSTANT;
        }
        
        //if the first character of temperatureScale is lower or uppercase ‘f’, then the program will
        //display the value of the temperature entered in Fahrenheit.
        if ((temperatureScale == 'f') || (temperatureScale == 'F'))
            {
                cout << "Your entry was " << temperatureInDegrees << " degrees Fahrenheit.\n";
                
                //Convert the Fahrenheit temperature into Celsius degrees and store
                //in the variable temperatureInCelsius. Then store the value entered by the user
                //in the variable temperatureInFahrenheit.
                temperatureInCelsius = (CELSIUS_CONVERTER_MULTIPLIER) * (temperatureInDegrees - CELSIUS_CONVERTER_CONSTANT);
                temperatureInFahrenheit = temperatureInDegrees;
            }
        
        ////calculate the values of the temperatures in different scales by
        //using the formulas given in the handout
        
        Delisle_temp = (DELISLE_CONVERTER_FINAL) * (DELISLE_CONVERTER_INITIAL - temperatureInCelsius);
        Reaumur_temp = (temperatureInCelsius) * (REAUMUR_CONVERTER);
        Romer_temp = (ROMER_CONVERTER_CONSTANT) + (ROMER_CONVERTER_MULTIPLIER * temperatureInCelsius);
        
        cout << "The following table lists your entry converted to various temperature scales:" << endl;
        cout << right << setw(10) << "Scale" << right << setw(10) << "Value" << endl;
        
        if ((temperatureScale == 'c') || (temperatureScale == 'C'))
        {
            cout << right << setw(10) << "Fahrenheit";
            cout << right << setw (10) << fixed << setprecision(2);
            cout << temperatureInFahrenheit << endl;
        }
        else if ((temperatureScale == 'f') || (temperatureScale == 'F'))
        {
            cout << right << setw(10) << "Celsius";
            cout << right << setw(10) << fixed << setprecision(2);
            cout << temperatureInCelsius << endl;
        }
        //define obj to use get functions for remaining tmp conversions
        TemperatureReading tmpObj;
        
        cout << right << setw(10) << "Kelvin";
        cout << right << setw(10) << fixed << setprecision(2);
        cout << tmpObj.getKelvin(temperatureInCelsius) << endl;
        
        cout << right << setw(10) << "Rankine";
        cout << right << setw(10) << fixed << setprecision(2);
        cout << tmpObj.getRankine(temperatureInCelsius) << endl;
        
        cout << right << setw(10) << "Delisle";
        cout << right << setw(10) << fixed << setprecision(2);
        cout << Delisle_temp << endl;
        
        cout << right << setw(10) << "Newton";
        cout << right << setw(10) << fixed << setprecision(2);
        cout << tmpObj.getNewton(temperatureInCelsius) << endl;
        
        cout << right << setw(10) << "Reaumur";
        cout << right << setw(10) << fixed << setprecision(2);
        cout << Reaumur_temp << endl;
        
        cout << right << setw(10) << "Romer";
        cout << right << setw(10) << fixed << setprecision(2);
        cout << Romer_temp << endl;
        
        return;
    } // end of valid temp
    else
    {
        cout<< "Temperature scale invalid. Please try again./n/n";
        return;
    }
}


double TemperatureReading::getFahrenheit(float temperatureInCelsius) const
{ //convert from Celsius to Fahrenheit
const float FAHRENHEIT_CONVERTER_MULTIPLIER = 1.8;
const float FAHRENHEIT_CONVERTER_CONSTANT = 32;
double Fahrenheit = 0;
float temperatureInFahrenheit = 0;
temperatureInFahrenheit = (temperatureInCelsius * FAHRENHEIT_CONVERTER_MULTIPLIER) + FAHRENHEIT_CONVERTER_CONSTANT;
return Fahrenheit;
}

double TemperatureReading::getKelvin(float temperatureInCelsius) const
{ //convert from Celsius to Kelvin
const float KELVIN_CONVERTER = (273.15);
double Kelvin = 0;
Kelvin = temperatureInCelsius + KELVIN_CONVERTER;
return Kelvin;
}

double TemperatureReading::getRankine(float temperatureInCelsius) const
{ //convert from Celsius to Rankine
const float RANKINE_CONVERTER_MULTIPLIER = 1.8;
const float RANKINE_CONVERTER_CONSTANT = 273.15;
double Rankine = 0;
Rankine = (RANKINE_CONVERTER_MULTIPLIER) * (temperatureInCelsius + RANKINE_CONVERTER_CONSTANT);
return Rankine;
}

double TemperatureReading::getNewton(float temperatureInCelsius) const
{ //convert from Celsius to Newton
const float NEWTON_CONVERTER = 0.33;
double Newton = 0;
Newton = (temperatureInCelsius) * (NEWTON_CONVERTER);
return Newton;
}

bool TemperatureReading::isValidScale(char scale, TemperatureReading &tmp) const
//validate scale of items in list
{
    if ( (tmp.getScale() == 'c') || (tmp.getScale() == 'C')
        || (tmp.getScale() == 'f') || (tmp.getScale() == 'F') )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}




