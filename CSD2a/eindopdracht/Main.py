#to do's: 
#Zorgen dat alle inputs bug free zijn
#Variatie maken in het algoritme van verdeling maten
#Leuke details toevoegen UI
#Losse bestanden maken voor verschillende onderdelen programma 

#import modules
import time
import simpleaudio as sa
import random as ra
from midiutil import MIDIFile
import UI_file as ui
import Functions as fnc


#input username and explanation of rhythm generator
username = ui.username
print("Hello " + username) 
print('This is the Irregular Beat Generator 3000')



#the program placed in a while loop to be able to keep creating different sequences.
while True:

    #UI for input time signature
    time_sig = ui.time_sig

    print("Time Signature is: ", time_sig)
    #checking the user input and executing the function
    #To do fix correctinput
    
    #UI for loop amount
    loop_amount = ui.loop_amount
    print("Loop amount is: ", loop_amount)

    #input for bpm
    correctInput = False
    bpm = 120
    #Check the bpm and see if it is the right value. 

    default_bpm = True

    keep_default = ui.keep_default

    if keep_default == "n":
        default_bpm = False
    else:
        default_bpm = True


    if default_bpm == False:
        while (not correctInput):
            user_bpm = ui.user_bpm

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

 
    #executing the functions all together to make a list of events based on time signature.
    if time_sig == "5/4":
        events =  fnc.execute_functions(fnc.names,fnc.num_amount_54,fnc.num_value_54,loop_amount)
        print(events)

    if time_sig == "7/8":
        events =  fnc.execute_functions(fnc.names,fnc.num_amount_78,fnc.num_value_78,loop_amount)
        print(events)
    


    #sort the list based on timestamps
    all_sortedevents_list = sorted(events, key=lambda d: d['Ts']) 

    #play the sequence when the user inputs y
    on = False
    switch_seq = ui.switch_seq
    if switch_seq == "y":
        on = True

    if switch_seq == "n":
        on = False


    #input for storing midifile
    export_true = False
    store = ui.store

    if store == "y":
        export_true = True
        #Function for exporting the midi ->
    else:
        export_true = False

    if export_true == True:
        fnc.add_events_to_midi(all_sortedevents_list,fnc.quarter_note_dur)

    # store the current time
    time_start = time.time()
    i = 0
    print("Start ", time_start)


    #Play sequence according to timestamp and instrument
    while True:
            now = time.time() - time_start
            #play samples if timestamp is reached
            if now >= all_sortedevents_list[i]["Ts"]:
                fnc.play_event(all_sortedevents_list,i)
                if all_sortedevents_list:
                    all_sortedevents_list.pop(0)   
                else:
                    break
            #if every sample has played quit.
            if(i == len(all_sortedevents_list)):
                break   

        
    with open("events_lists.midi",'wb') as outf:
        fnc.midi_file.writeFile(outf)
    if input("Would you like another sequence? n will stop the program ") == "n":
        break


