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

#setting default values for midi export
velocity= 80
track = 0
channel = 10 # corresponds to channel 10 drums




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
    dur_quarter = 60/bpm

    for note_dur in note_durations:
        time_durations.append(note_dur * dur_quarter)
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

#executing functions for converting values to timestamps
time_durations = note_dur_to_td(note_durations,bpm)
print("The Time Durations between the notes are:",time_durations)
timestamps = time_dur_to_ts(time_durations)
print("The timestamps are:",timestamps)

ts_kick_events = create_events(kick_dict["Instrument"],timestamps,kick_dict["Name"])

#print the events
print("The Kick events: ",ts_kick_events)


#add all the events to a combined list
all_events_list = ts_kick_events #+ ts_snare_events + ts_hat_events

#sort the list based on timestamps
all_sortedevents_list = sorted(all_events_list, key=lambda d: d['Ts']) 

#play the sequence when the user inputs y
on = False
switch_seq = input("Play the sequence? y/n:")
if switch_seq == "y":
    on = True

if switch_seq == "n":
    on = False


def play_event(event):
    print(event["Name"])
    print(event["Ts"])
    event['Sample'].play()

# store the current time
time_start = time.time()
print("Start ", time_start)

#Play sequence according to timestamp and instrument
while on == True:
    now = time.time() - time_start
    for i in range(len(all_sortedevents_list)):
        if now >= all_sortedevents_list[i]["Ts"]:
            play_event(all_sortedevents_list[i])
            all_sortedevents_list.pop(0)
            time.sleep(0.1)
            # play_event(all_sortedevents_list[i])





#input for storing midifile
export_true = False
store = input("Would you like to export the sequence into a Midifile? Y/N ")
if store == "Y":
    export_true = True
    #Function for exporting the midi ->


# create the MIDIfile object, to which we can add notes
midi_file = MIDIFile(1)
# set name and tempo
time_beginning = 0
midi_file.addTrackName(track, time_beginning, "Beat Sample Track")
midi_file.addTempo(track, time_beginning, bpm)


#additional values
quarter_note_dur = 60 / bpm
instr_midi_pitch = {
    "Kick": 35,
    "Snare": 38,
    "Hat": 40
}


def add_events_to_midi(events):
    for event in events:
        # transform time (sec) to (qnote)
        qnote_time = event["timestamp"] / quarter_note_dur
        instr_name = event["instr_name"]
        midi_file.addNote(track, channel, instr_midi_pitch[instr_name], qnote_time,
            event['note_dur'], velocity)

with open("events_lists.midi",'wb') as outf:
    midi_file.writeFile(outf)



