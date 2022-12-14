#include "TouchscreenCpp.hpp"


TouchscreenCpp::TouchscreenCpp(std::string fileName, Data& data)
{
    //Gem filnavn i variabel
    fileName_ = fileName;

    //Sætter default værdier
    dataFile_.open(fileName_, std::fstream::out | std::fstream::trunc);
    dataFile_ << "STOP\n0\n0\n0\n";
    dataFile_.close();
    
    //Læg passende data medlemmer ind i liste. Stemmer overens med rækkefølgen af den tilhørende txt fil
    dataRefs_.push_back(data.getModeP()); //L1: User input - mode select
    dataRefs_.push_back(data.getDistP()); //L2: Distance moved
    dataRefs_.push_back(data.getLineTypeP()); //L3: Linetype
    dataRefs_.push_back(data.getNextMoveP()); //L4: NextMove
}

TouchscreenCpp::~TouchscreenCpp()
{
}

void TouchscreenCpp::updateData() //Læser brugerinput på touchskærm og gemmer i data-klassen
{
    dataFile_.open(fileName_, std::fstream::in); //Åbn fil
    dataFile_.seekg (0, std::ios::beg); //Ryk filepointer til start
    std::string temp; //temp variabel til at gemme streng

    std::getline(dataFile_, temp); //Gem linjens tekst i temp strengen
    *dataRefs_.front() = temp; //Skriv linjen til data klassens tilsvarende element
    dataFile_.close();
}


void TouchscreenCpp::updateScreen() //Opdaterer touchskærmen med data fra data-klassen
{
    dataFile_.open(fileName_, std::fstream::out | std::fstream::trunc); //Åbn og clear fil
    dataFile_.seekg (0, std::ios::beg); //Ryk filepointer til start
    for (auto i : dataRefs_) //Loop gennem de 4 tilknyttede elementer i data klassen.
    {   
        dataFile_ << *i << std::endl;
    }
    dataFile_.close();
}
