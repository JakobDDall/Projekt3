from guizero import App, PushButton, Text, ListBox, Box, TextBox
import sys
import time
import spidev
   
class TouchscreenPy:
    
    def __init__(self, advancedmode, simplemode):
        self.advancedmode = advancedmode
        self.simplemode = simplemode
    
        
    def toggleSimple(self):
        self.simplemode = True
        self.simpleButton.enabled = False
        self.advancedButton.enabled = False
        print("Simple funktion er valgt")
        
        #Skriv til filen at simple er valgt:
        text = "Simple\n"
        lineNumber = 0
        self.writeToFile(lineNumber,text)
        
    def toggleAdvanced(self):
        self.advancedmode = True
        self.advancedButton.enabled = False
        self.simpleButton.enabled = False
        #self.valgtMode.value = "Avanceret funktion er valgt"
        
        #Skriv til filen at advanced er valgt:
        text = "Advanced\n"
        lineNumber = 0
        self.writeToFile(lineNumber,text)
           
    def stopButton(self):
        self.advancedmode = False
        self.simplemode = False
        self.advancedButton.enabled = True
        self.simpleButton.enabled = True
        self.valgtMode.value = "Ingen funktion er valgt"
          
        
        #Skriv til filen at STOP er valgt:
        text = "STOP\n"
        lineNumber = 0
        self.writeToFile(lineNumber,text)
        
        self.writeToFile(1,"0\n")

        
    def writeToFile(self,lineNumber,text):
        #Read:
        read_f = open("Screen.txt",'r')
        data = read_f.readlines()
        read_f.close()
        
        #Write:
        write_f = open("Screen.txt",'w')
        data[lineNumber] = text
        write_f.writelines(data)
        write_f.close()
        print(data)
        
    def readData(self, lineNumber):
        #Read:
        read_f = open("Screen.txt",'r')
        data = read_f.readlines()
        lineType = data[lineNumber]
        print(lineType)
        read_f.close()    
        return lineType
            
    #Main:
    def main(self):
        if self.simplemode == True or self.advancedmode == True:
        #Kører callback:
           nextMove = self.readData(3)
           self.move.value = nextMove
           
           lineType = self.readData(2)
           self.linje.value = lineType
           
           distance = self.readData(1)
           self.distance.value = distance
           
           self.valgtMode.value = self.readData(0)
        
            
            
    def GUI(self):
        ###### Visualisering af knapper og text: ######################
        self.app = App('Hovedmenu for LineBot', height = 480, width = 800)

        modes = Text(self.app, text= "Vælg en mode for LineBot", align = "top")
        Mode_box = Box(self.app, align="top", width="fill")


        self.simpleButton = PushButton(Mode_box, self.toggleSimple, text="Kør simpel labyrint", align="left",width = "fill", height = 2, enabled = True)
        self.simpleButton.text_size = 15


        self.advancedButton = PushButton(Mode_box, self.toggleAdvanced, text="Kør avanceret labyrint", align="right",width = "fill", height = 2, enabled = True)
        self.advancedButton.text_size = 15


        self.valgtMode = Text(self.app, text ="Ingen funktion er valgt", align="top", width = "fill", height = 2 )
        

        Text(self.app, text="Aflagte distance:", align ="top")
        self.distance = Text(self.app, text= "0")
        
        
        Text(self.app, text="Nuværende linjetype:", align ="top")
        self.linje = Text(self.app, text="Ingen linjetype")
        self.linje.repeat(100, self.main)  # Laver callback hvert 100ms
        
        Text(self.app, text="Næste move:", align ="top")
        self.move = Text(self.app, text="Ingen")
        

        self.stopButton = PushButton(self.app, self.stopButton, text="STOP", align="bottom",width = 20, height = 3)
        self.stopButton.text_size = 15

        self.app.display()
            
        
            
H_menu = TouchscreenPy(False,False)
H_menu.GUI()





