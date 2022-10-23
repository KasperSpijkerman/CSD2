#to do's: 
#Variatie maken in het algoritme van verdeling maten
#Verschillende bestanden uit laten schrijven. 

#import modules
import time
import simpleaudio as sa
import random as ra
from midiutil import MIDIFile
import UI_file as ui
import Functions as fnc
import animation


#setting fixed values for midi
instr_midi_pitch = {
        "kick": 35,
        "snare": 38,
        "hat": 42,
        "fx": 45
        }
velocity= 80
track = 0
channel = 9 # corresponds to channel 10 drums

#short startup animation, (cannot be placed in a function due to the module.)
tags = ["E   ", "En  ", "Ent ", "Ente","Enter", "Enteri  ", "Enterin", "Entering", "Entering S","Entering Sp","Entering Spa", "Entering Spac", "Entering Space"]

animation = animation.Wait(tags, color="blue", speed=1)
animation.start()
time.sleep(3)
animation.stop()


#input username and explanation of rhythm generator
#asking the user 1 time for username
username = input("Greetings traveler what is your name? ")
print("Welcome on board " + username) 
print('This is the Spacious IBG ')
print("Ready to generate a special beat, according to your input!")



#the rest of the program placed in a while loop to be able to keep creating different sequences.
while True:

    #UI for input time signature
    time_sig = ui.sig_input()

    print("Time Signature is: ", time_sig)
    #checking the user input and executing the function
    #To do fix correctinput
    bpm = ui.bpm_input()
    print("The chosen speed is ",bpm, "BPM")

    

    
    
    #UI for loop amount
    loop_amount = ui.loop_input()
    print("Looping the adventure", loop_amount,"times")

    #executing the functions all together to make a list of events based on time signature.
    if time_sig == "5/4":
        events =  fnc.execute_functions(fnc.names,fnc.num_amount_54,loop_amount,bpm,time_sig)
        #print(events)

    if time_sig == "7/8":
        events =  fnc.execute_functions(fnc.names,fnc.num_amount_78,loop_amount,bpm,time_sig)
        #print(events)
    
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
        correct_midi = False
        while not correct_midi:
            try:
                store = input("Would you like to export this experience into a Midifile? y/n ")
                if store == "y":
                    correct_midi = True
                if store == "n":
                    correct_midi = True
            except:
                print('Please enter y/n')
    if store == "y":
        export_true = True
        #Function for exporting the midi ->
    else:
        export_true = False
        
    if export_true == True:
        with open("events_lists.midi",'wb') as outf:
            midi_file.writeFile(outf)
    if input("Would you like to travel another time? (any input will continue) n will stop ") == "n":
        break


