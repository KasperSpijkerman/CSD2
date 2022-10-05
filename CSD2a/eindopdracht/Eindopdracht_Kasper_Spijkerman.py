#To do
#Maatsoort input 
#Events
#Random Kiezen 
#Algoritme bedenken voor creeeren sequenties. 
#UI
#Input voor aantal loops
#Vragen aan de user of ze de midi willen exporteren 

#import modules
import time
import simpleaudio as sa
import random as ra

#Samples 
Kick= sa.WaveObject.from_wave_file("assets/SD_Kick_Battalion.wav")
Snare= sa.WaveObject.from_wave_file("assets/SD_Snare_Bewitch.wav")
Hat=  sa.WaveObject.from_wave_file("assets/SD_ClHat_Cherry.wav")

#Events with names
kick_dict = {
    'Name': "Kick",
    "Instrument": Kick,
    }

snare_dict = {
    'Name': "Snare",
    "Instrument": Snare,
    }

hat_dict = {
    'Name': "Hat",
    "Instrument": Hat,
    }

#list with instruments dicts to choose from 
instruments = [kick_dict,snare_dict,hat_dict]

#input username and explanation of rhythm generator
username = input("Enter Username: ")
print("Hello " + username) 
print('This is the Irregular Beat Generator 3000')


#UI for input time signature
time_sig = input("Fill in a irregular time signature for the sequence. Choose between 5/7 and 3/8: ")

print("Time Signature is: ", time_sig)

#input for bpm
correctInput = False
bpm = 120
#Check the bpm and see if it is the right value. 
while (not correctInput):
    user_bpm = input("Enter a bpm: ")

    # check if we 'received' an empty string
    if not user_bpm:
        # empty string --> use default
        correctInput = True
    else:
        try:
            bpm = float(user_bpm)
            correctInput = True
        except:
            print("Incorrect input - please enter a bpm (or enter nothing - default bpm)")

print("Bpm is: ", bpm)

#input for storing midifile
export_true = False
store = input("Would you like to export the sequence into a Midifile? Y/N")
if store == "Y":
    export_true = True
    #Function for exporting the midi



