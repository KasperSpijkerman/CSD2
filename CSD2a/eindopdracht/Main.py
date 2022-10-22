#to do's: 
#Variatie maken in het algoritme van verdeling maten
#Leuke details toevoegen UI
#Programma laten loopen 
#Verschillende bestanden uit laten schrijven. 

#import modules
import time
import simpleaudio as sa
import random as ra
from midiutil import MIDIFile
import UI_file as ui
import Functions as fnc

#setting fixed values for midi
instr_midi_pitch = {
        "kick": 35,
        "snare": 38,
        "hat": 42,
        }
velocity= 80
track = 0
channel = 9 # corresponds to channel 10 drums

#input username and explanation of rhythm generator
#asking the user 1 time for username
username = input("Enter Username: ")
print("Hello " + username) 
print('This is the Irregular Beat Generator 3000')



#the rest of the program placed in a while loop to be able to keep creating different sequences.
while True:

    #UI for input time signature
    time_sig = ui.sig_input()

    print("Time Signature is: ", time_sig)
    #checking the user input and executing the function
    #To do fix correctinput
    bpm = ui.bpm_input()
    print(bpm)
    
    #UI for loop amount
    loop_amount = ui.loop_input()
    print("Loop amount is: ", loop_amount)

    #executing the functions all together to make a list of events based on time signature.
    if time_sig == "5/4":
        events =  fnc.execute_functions(fnc.names,fnc.num_amount_54,loop_amount,bpm,time_sig)
        print(events)

    if time_sig == "7/8":
        events =  fnc.execute_functions(fnc.names,fnc.num_amount_78,loop_amount,bpm,time_sig)
        print(events)
    
    #sort the list based on timestamps
    all_sortedevents_list = sorted(events, key=lambda d: d['Ts']) 

    #play the sequence when the user inputs y
    on = False
    switch_seq = ui.switch_input()
    if switch_seq == "y":
        on = True

    if switch_seq == "n":
        on = False

    #additional midi values
    quarter_note_dur = 60 / bpm
    

    # create the MIDIfile object, to which we can add notes
    midi_file = MIDIFile(1)
    # set name and tempo
    time_beginning = 0
    midi_file.addTrackName(track, time_beginning, "Beat Sample Track")
    midi_file.addTempo(track, time_beginning, bpm)



    fnc.add_events_to_midi(all_sortedevents_list,quarter_note_dur,midi_file,track,channel,instr_midi_pitch,velocity)

    # store the current time
    time_start = time.time()
    i = 0
    print("Start ", time_start)


    #Play sequence according to timestamp and instrument
    while on == True:
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
                on = False
                break   
            time.sleep(0.001)


    #input for storing midifile
    export_true = False
    if on == False:
        store = input("Would you like to export the sequence into a Midifile? y/n ")

    if store == "y":
        export_true = True
        #Function for exporting the midi ->
    else:
        export_true = False
        
    if export_true == True:
        with open("events_lists.midi",'wb') as outf:
            midi_file.writeFile(outf)
    if input("Would you like to repeat the sequence? n will stop ") == "n":
        break


