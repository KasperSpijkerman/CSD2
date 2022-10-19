#to do's: 
#Zorgen dat alle inputs bug free zijn
#Variatie maken in het algoritme van verdeling maten
#Leuke details toevoegen UI
#Losse bestanden maken voor verschillende onderdelen programma 

#import modules
import time
import simpleaudio as sa
import random as ra
from random import randint
from midiutil import MIDIFile
import UI_file as ui
import Functions as fnc

#Samples 
Kick= sa.WaveObject.from_wave_file("assets/SD_Kick_Battalion.wav")
Snare= sa.WaveObject.from_wave_file("assets/SD_Snare_Bewitch.wav")
Hat=  sa.WaveObject.from_wave_file("assets/SD_ClHat_Cherry.wav")

#Dicts with names
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
username = ui.username
print("Hello " + username) 
print('This is the Irregular Beat Generator 3000')

    #rhythm generation
    #euclidean steps for time signatures
num_steps_78 = 7
num_steps_54 = 5
#euclidean notes per steps
num_notes_54 = 4
num_notes_78 = 8
#the program placed in a while loop to be able to keep creating different sequences.
while True:

    #UI for input time signature
    time_sig = ui.time_sig

    print("Time Signature is: ", time_sig)

    #function for creating events based on timestamps, sample, name and time durations
    def create_events(sample,timestamps,name,notedur):
        #dictionary for 1 event
        event_dict = {}
        #empty list for different events
        events_list = []
        #create different dictionaries and add them to a list
        #creating copies of the event dict otherwise it will just output 1 dict.
        for i in range(len(timestamps)): 
            event_dict = {"Sample":sample, "Name":name, "Ts": timestamps[i], "Nd":notedur[i]}
            events_list.append(event_dict.copy())
        return events_list




    #checking the user input and executing the function
    #To do fix correctinput


    if time_sig == "5/4":
        note_durations_kick =fnc.calculate_durations(num_steps_54,num_notes_54)
        note_durations_snare = fnc.calculate_durations(num_steps_54,ra.randrange(1,4))
        note_durations_hat = fnc.calculate_durations(num_steps_54,ra.randrange(1,4))
        print(note_durations_kick)
        print(note_durations_snare)
        print(note_durations_hat)

    if time_sig == "7/8":
        note_durations_kick = fnc.calculate_durations(num_steps_78,num_notes_78)
        note_durations_snare = fnc.calculate_durations(num_steps_78,ra.randrange(1,8))
        note_durations_hat = fnc.calculate_durations(num_steps_78,ra.randrange(1,8))
        print(note_durations_kick)
        print(note_durations_snare)
        print(note_durations_hat)


    #UI for loop amount
    loop_amount = ui.loop_amount

    #loop lists 
    fnc.loop_dur_list(note_durations_kick,loop_amount)
    fnc.loop_dur_list(note_durations_snare,loop_amount)
    fnc.loop_dur_list(note_durations_hat,loop_amount)

    #input for bpm
    correctInput = False
    bpm = 120
    #Check the bpm and see if it is the right value. 

    default_bpm = True

    keep_default = input("Default Bpm is 120, would you like to keep it? y/n ")

    if keep_default == "n":
        default_bpm = False
    else:
        default_bpm = True


    if default_bpm == False:
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

    #executing functions for converting values to timestamps
    time_durations_kick = fnc.note_dur_to_td(note_durations_kick,bpm)
    time_durations_snare = fnc.note_dur_to_td(note_durations_snare,bpm)
    time_durations_hat = fnc.note_dur_to_td(note_durations_hat,bpm)
    # print("The Time Durations between the notes are:",time_durations)
    timestamps_kick = fnc.time_dur_to_ts(time_durations_kick)
    timestamps_snare = fnc.time_dur_to_ts(time_durations_snare)
    timestamps_hat = fnc.time_dur_to_ts(time_durations_hat)
    # print("The timestamps are:",timestamps)
    ts_kick_events = create_events(kick_dict["Instrument"],timestamps_kick,kick_dict["Name"],note_durations_kick)
    ts_snare_events = create_events(snare_dict["Instrument"],timestamps_snare,snare_dict["Name"],note_durations_snare)
    ts_hat_events = create_events(hat_dict["Instrument"],timestamps_hat,hat_dict["Name"],note_durations_hat)

    #add all the events to a combined list
    all_events_list = ts_kick_events + ts_snare_events + ts_hat_events

    #sort the list based on timestamps
    all_sortedevents_list = sorted(all_events_list, key=lambda d: d['Ts']) 

    #play the sequence when the user inputs y
    on = False
    switch_seq = input("Play the sequence? y/n: ")
    if switch_seq == "y":
        on = True

    if switch_seq == "n":
        on = False


    #input for storing midifile
    export_true = False
    store = input("Would you like to export the sequence into a Midifile? y/n ")

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


