#To do
#Maatsoort input 
#Events
#Random Kiezen 
#Algoritme bedenken voor creeeren sequenties -> Euclidean
#UI
#Input voor aantal loops
#Vragen aan de user of ze de midi willen exporteren 

#import modules
import time
import simpleaudio as sa
import random as ra
from midiutil import MIDIFile

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
time_sig = input("Fill in a irregular time signature for the sequence. Choose between 5/4 and 7/8: ")

print("Time Signature is: ", time_sig)


#rhythm generation
#euclidean steps for time signatures
num_steps_78 = 7
num_steps_54 = 5
#euclidean notes per steps
num_notes_54 = 4
num_notes_78 = 8

#function for calculating durations based on time signature
def calculate_durations(steps,notes):
    note_durations = []
    duration16th = int(steps/notes)
    note_durations =[duration16th]*notes
    rest_value = steps - (notes * duration16th)
    for i in range(rest_value):
        note_durations[i] += 1
    return(note_durations)

#To do: Rotation

#function for converting notedurations to timedurations.
def note_dur_to_td(note_durations,bpm):
    
    time_durations = []
    dur_bpm = 60/bpm

    for note_dur in note_durations:
        time_durations.append(note_dur * dur_bpm)
    return time_durations

#function for calculating timestamps
def time_dur_to_ts(time_durations):
    time_stamps = []
    timestamp = 0
    # iterate through the source sequence, sum durations and store these as
    # timestamp in the destination Sequence
    for time_dur in time_durations:
        time_stamps.append(timestamp)
        timestamp += time_dur

    return time_stamps

#function for creating events based on timestamps, sample and name
def create_events(sample,timestamps,name):
    #dictionary for 1 event
    event_dict = {}
    #empty list for different events
    events_list = []
    #create different dictionaries and add them to a list
    #creating copies of the event dict otherwise it will just output 1 dict.
    for i in range(len(timestamps)): 
        event_dict = {"Sample":sample, "Name":name, "Ts": timestamps[i]}
        events_list.append(event_dict.copy())
    return events_list




#checking the user input and executing the function
#To do fix correctinput
if time_sig == "5/4":
    note_durations = calculate_durations(num_steps_54,num_notes_54)
    print(note_durations)

if time_sig == "7/8":
    note_durations = calculate_durations(num_steps_78,num_notes_78)
    print(note_durations)



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
store = input("Would you like to export the sequence into a Midifile? Y/N ")
if store == "Y":
    export_true = True
    #Function for exporting the midi ->


# #setting default values for midi export
# velocity= 80
# track = 0
# channel = 10 # corresponds to channel 10 drums


# # create the MIDIfile object, to which we can add notes
# mf = MIDIFile(1)
# # set name and tempo
# time_beginning = 0
# mf.addTrackName(track, time_beginning, "Beat Sample Track")
# mf.addTempo(track, time_beginning, bpm)


# for event in events:
#     # transform time (sec) to (qnote)
#     qnote_time = event["timestamp"] / qnote_dur
#     instr_name = event["instr_name"]
#     mf.addNote(track, channel, instr_midi_pitch[instr_name], qnote_time,
#         event['note_dur'], velocity)

# with open("events_lists.midi",'wb') as outf:
#     mf.writeFile(outf)



