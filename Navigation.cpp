#include "Navigation.hpp"
#include "defines.hpp"



Navigation::Navigation(/* args */)
{
    handlerAppIF_ = new HandlerAppIF(data_);
    lineDecider_ = new LinetypeDecider(data_);
    touchscreen_ = new TouchscreenCpp("Screen.txt", data_);

    //Setting initialdata entries
    data_.setDist("0");
    data_.setLineType("0");
    data_.setMode("STOP");
    data_.setNextMove("0");
    data_.setSensorData("0");


    lastMove_ = new std::string;
}

Navigation::~Navigation()
{
    delete handlerAppIF_;
    delete lineDecider_;
    delete touchscreen_;
    delete lastMove_;
}


void Navigation::startMainLoop() //Hele programmet foregår i denne metode
{
    while (1)
    {
        touchscreen_->updateData(); //Læser brugerinput. Opdaterer data i data-klassen
        handlerAppIF_->updateData(); //Hent ny data fra PSoC. Opdaterer data i data-klassen
        lineDecider_->updateData(); //Bestemmer linjetypen ud fra sensordata fra PSoC. Opdaterer data i data-klassen
        determineNextMove();        //Bestemmer den næste kommando der skal sendes til PSoC'en ud fra linjetype og sidste kommando udført af PSoC. Opdaterer data i data-klassen
        touchscreen_->updateScreen(); //Opdaterer touchskærmen med opdateret data fra data-klassen
        handlerAppIF_->sendCmd(); //Sender kommando til PSoC
        usleep(10000); //Venter i 10ms. Dette gøres for at PSoC'en kan nå at få ny data før der sendes SPI-requests
    }


}
//Logik til beslutningstagen er som følger:
//Move bestemmes:
    //Navigation -> determineNextMove() forholder sig til hvilken mode der er valg, og kalder passende funktion
    //Denne funktion ser på hvad linebot netop nu er i gang med, og bestemmer næste move herudfra.
    //Eksempelvis: Kører vi ligeud analyserer vi linjetype, er vi ved at dreje, ser vi blot på en enkelt sensor

    //Efter ovenstående har kørt, skriver robotten et move ind i nextMove variablen i data klassen.

//Move sendes
    //HandlerAppIF holder i hvert gennemløb af main-loop øje med om der er sket ændringer i robottens næste move.
    //Hvis det er tilfældet, sendes ny kommando til PSoC.


void Navigation::determineNextMove()
{
    if (*data_.getModeP() == "STOP") //Hvis stop er valgt, sættes nextMove blot til stop
    {
        *data_.getNextMoveP() = TYPE_STOP;
        return;
    }
    else if (*data_.getModeP() == "Simple")
    {
        determineSimple();
        return;
    }
    else if (*data_.getModeP() == "Advanced")
    {
        determineAdvanced();
        return;
    }
}

void Navigation::determineSimple()
{
    std::string linetype = *data_.getLineTypeP();
    std::string nextMove = *data_.getNextMoveP();
    uint8_t sensorData = std::stoi(*data_.getSensorDataP());
 
    if(nextMove == MOV_STRAIGHT || nextMove == MOV_ADJ_RIGHT || nextMove == MOV_ADJ_LEFT) //Hvis linebotten kører ligeud
    {
        if(ihavejustturned) //Hvis lineBot lige har drejet, skal den køre ligeud i et sekund. Herved undgås at linebot begynder at dreje med det samme igen
        {
            if (turnDone_ == false)
            {
                turning_timer_ = std::chrono::system_clock::now(); //Start "timer"
                turnDone_ = true;
            }
            if(turnDone_ && (std::chrono::duration_cast<std::chrono::milliseconds>
                (std::chrono::system_clock::now() - turning_timer_).count() > 1000)) //Hvis der er gået 1s eller over siden "timer" blev startet
            {
                turnDone_ = false;
                ihavejustturned = false;
            }
        }

        else if(linetype == TYPE_RIGHT)
        {                        
            *data_.getNextMoveP() = MOV_RIGHT;
        }

        else if(linetype == TYPE_LEFT)
        {
            *data_.getNextMoveP() = MOV_LEFT;
        }

        else if((sensorData & SENSOR_FRONTRIGHT) && !(sensorData & SENSOR_FRONTLEFT) && !(sensorData & SENSOR_FRONT))
        {
            *data_.getNextMoveP() = MOV_ADJ_RIGHT; //Anvendes til at justere linebottens kurs lidt mod højre
        }

        else if(!(sensorData & SENSOR_FRONTRIGHT) && (sensorData & SENSOR_FRONTLEFT) && !(sensorData & SENSOR_FRONT))
        {
            *data_.getNextMoveP() = MOV_ADJ_LEFT; //Anvendes til at justere linebotens kurs lidt mod venstre
        }
        else if(linetype == TYPE_STRAIGHT)
        {
            *data_.getNextMoveP() = MOV_STRAIGHT;
        }

        else if(linetype == TYPE_STOP)
        {
            *data_.getNextMoveP() = MOV_STOP;
        }
    }
    else if (nextMove == MOV_STOP) //Hvis linebotten er standset
    {
       if (linetype == TYPE_STRAIGHT) //Kør ligeud, når linebotten ser en linje
       {
        *data_.getNextMoveP() = MOV_STRAIGHT;
       }
    }
    else if(nextMove == MOV_RIGHT || nextMove == MOV_LEFT) //Hvis linebotten drejer
    {
        if (turning_ == false)
            {
                
                turning_timer_ = std::chrono::system_clock::now(); //Start "timer" ved påbegyndelse af sving
                turning_ = true;
            }
            if(turning_ && (std::chrono::duration_cast<std::chrono::milliseconds>
                (std::chrono::system_clock::now() - turning_timer_).count() > 500)) //Hvis der er gået 500ms eller mere siden sving blev påbegyndt. Anvendes så frontsensoren ikke reagerer på dens nuværende linje
            {
                if(sensorData & SENSOR_FRONT) //Hvis frontsensor ser linje
                {
                    
                    *data_.getNextMoveP() = MOV_STRAIGHT; //Kør ligeud
                    turning_ = false;
                    ihavejustturned = true; //Variabel anvendt til at undgå at LineBot drejer med det samme igen
                }
            }
    }

    *lastMove_ = *data_.getNextMoveP(); //Opdater lastmove
}

void Navigation::determineAdvanced()
{
    std::string linetype = *data_.getLineTypeP();
    std::string nextMove = *data_.getNextMoveP();
    uint8_t sensorData = std::stoi(*data_.getSensorDataP());
 
    if(nextMove == MOV_STRAIGHT || nextMove == MOV_ADJ_RIGHT || nextMove == MOV_ADJ_LEFT) //Hvis linebotten kører ligeud
    {
        if(ihavejustturned) //Hvis lineBot lige har drejet, skal den køre ligeud i et sekund. Herved undgås at linebot begynder at dreje med det samme igen
        {
            if (turnDone_ == false)
            {
                turning_timer_ = std::chrono::system_clock::now();
                turnDone_ = true;
            }
            if(turnDone_ && (std::chrono::duration_cast<std::chrono::milliseconds>
                (std::chrono::system_clock::now() - turning_timer_).count() > 1000))
            {
                turnDone_ = false;
                ihavejustturned = false;
            }
        }

        //Ved disse linjetyper skal der drejes til højre, da LineBot prioriterer højre
        else if(linetype == TYPE_RIGHT || linetype == TYPE_TJUNCTION1 || linetype == TYPE_TJUNCTION2 || linetype == TYPE_4WAY || linetype == TYPE_UTURN)
        {                        
            *data_.getNextMoveP() = MOV_RIGHT;
        }

        //Derefter prioriterer linebot straight
        else if(linetype == TYPE_TJUNCTION3)
        {
            *data_.getNextMoveP() = MOV_STRAIGHT;
        }

        //Sidste prioritering er left
        else if(linetype == TYPE_LEFT)
        {
            *data_.getNextMoveP() = MOV_LEFT;
        }

        else if((sensorData & SENSOR_FRONTRIGHT) && !(sensorData & SENSOR_FRONTLEFT) && !(sensorData & SENSOR_FRONT))
        {
            *data_.getNextMoveP() = MOV_ADJ_RIGHT; //Anvendes til at justere linebottens kurs lidt mod højre
        }

        else if(!(sensorData & SENSOR_FRONTRIGHT) && (sensorData & SENSOR_FRONTLEFT) && !(sensorData & SENSOR_FRONT))
        {
            *data_.getNextMoveP() = MOV_ADJ_LEFT; //Anvendes til at justere linebottens kurs lidt mod venstre
        }
        else if(linetype == TYPE_STRAIGHT)
        {
            *data_.getNextMoveP() = MOV_STRAIGHT;
        }

        else if(linetype == TYPE_STOP)
        {
            *data_.getNextMoveP() = MOV_STOP;
        }
    }
    else if (nextMove == MOV_STOP) //Hvis LineBot er standset
    {
       if (linetype == TYPE_STRAIGHT) //Hvis LineBot ser en lige linje
       {
        *data_.getNextMoveP() = MOV_STRAIGHT;
       }
    }
    else if(nextMove == MOV_RIGHT || nextMove == MOV_LEFT) //Hvis linebotten drejer
    {
        if (turning_ == false)
            {
                
                turning_timer_ = std::chrono::system_clock::now(); //Start "timer" ved påbegyndelse af sving
                turning_ = true;
            }
            if(turning_ && (std::chrono::duration_cast<std::chrono::milliseconds>
                (std::chrono::system_clock::now() - turning_timer_).count() > 500)) //Hvis der er gået 500ms eller mere siden sving blev påbegyndt. Anvendes så frontsensoren ikke reagerer på dens nuværende linje
            {
                if(sensorData & SENSOR_FRONT) //Hvis frontsensor ser linje
                {
                    
                    *data_.getNextMoveP() = MOV_STRAIGHT; //Kør ligeud
                    turning_ = false;
                    ihavejustturned = true; //Variabel anvendt til at undgå at LineBot drejer med det samme igen
                }
            }
            else if(nextMove == MOV_LEFT && sensorData & SENSOR_RIGHT) //Hvis linebot har påbegyndt et venstre sving, men ser noget på højre sensor
            {
                *data_.getNextMoveP() = MOV_RIGHT; //Drej til højre i stedet (højreprioritering)
                turning_ = false;
            }
    }



    *lastMove_ = *data_.getNextMoveP(); //Opdater lastmove
}
