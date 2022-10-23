#In this file the functions for rhythm generation and playing the rhythms are located.
from midiutil import MIDIFile
#importing modules to use in functions
import time
import simpleaudio as sa
import random as ra
import UI_file as ui
import random
#Samples dictionary
samples = {
    'kick': sa.WaveObject.from_wave_file("assets/SD_Kick_Battalion.wav"),
    'snare': sa.WaveObject.from_wave_file("assets/SD_Snare_Bewitch.wav"),
    'hat': sa.WaveObject.from_wave_file("assets/SD_ClHat_Cherry.wav"),
    'fx':   sa.WaveObject.from_wave_file("assets/SD_Perc_FXSonar.wav")
}

#list with instruments dicts to choose from 
names = ['kick','snare','hat','fx']

#Rhythm generation
#euclidean amount of steps for time signatures
num_amount_78 = 7
num_amount_54 = 5

#densities for different rhythms
note_densities = {
    'kick': [0.2, 0.3],
    'snare': [0.3, 0.5],
    'hat': [0.5, 0.9],
    'fx': [0.2,0.2]

}

#function for calculating the durations based on steps and notes
def calculate_durations(steps,notes):
    note_durations = []
    duration16th = int(steps/notes)
    note_durations =[duration16th]*notes
    rest_value = steps - (notes * duration16th)
    for i in range(rest_value):
        note_durations[i] += 1
    return(note_durations)
#function for converting notedurations to timedurations.
def note_dur_to_td(note_durations,bpm,sig):
        
    time_durations = []
    if (sig == "5/4"):
        convert_value = 60/bpm
    if(sig == "7/8"):
        convert_value = 30/bpm

    for note_dur in note_durations:
        time_durations.append(note_dur * convert_value)
    return time_durations
#function for calculating timestamps from the time durations
def time_dur_to_ts(time_durations):
    time_stamps = []
    timestamp = 0
    # iterate through the source sequence, sum durations and store these as
    # timestamp in the destination Sequence
    for time_dur in time_durations:
        time_stamps.append(timestamp)
        timestamp += time_dur

    return time_stamps
#function for creating events based on timestamps, sample, name and time durations
def create_events(sample,timestamps,notedur):
    #dictionary for 1 event
    event_dict = {}
    #empty list for different events
    events_list = []
    #create different dictionaries and add them to a list
    #creating copies of the event dict otherwise it will just output 1 dict.
    for i in range(len(timestamps)): 
        event_dict = {"Sample":sample, "Ts": timestamps[i], "Nd":notedur[i]}
        events_list.append(event_dict.copy())
    return events_list
#function for repeating asking the density per sample
def ask_note_dens(name):
        note_dens = ui.dens_input()
        print(name,"density =", note_dens)
        return(note_dens)
#function for actually changing the density
def change_note_dens(name,dens):
    if dens == "1":
        note_densities[name] = [0.2,0.3]
    if dens == "2":
        note_densities[name] = [0.4,0.5]
    if dens == "3":
        note_densities[name] = [0.6,0.7]
    if dens == "4":
        note_densities[name] = [0.7,0.8]
    if dens == "5":
        note_densities[name] = [0.8,1]
    if dens == "0":
        note_densities[name]
    return(name)
def ask_randomizer():
    rand_input = ui.randomizer_input()
    return(rand_input)
#function for repeating the sequence according to amount of loops
def loop_dur_list(note_durations,loop_amount,rand_input):
    note_durations_loop = list(note_durations)
    for i in range(loop_amount):
        for e in note_durations_loop:
            note_durations.append(e)
    if rand_input == "adventure":
        random.shuffle(note_durations)
    return note_durations
#function for executing the different functions al together to create events.
def execute_functions(names,num_amount,loop_amount,bpm,sig):
        event_list = [] 
        #executing the randomizer function once
        rand_input = ask_randomizer()
        for name in names:
            #Ask the user for note density per instrument
            note_dens = ask_note_dens(name)
            #change the note density according to user input
            change_note_dens(name,note_dens)
            num_notes_min = round(num_amount * note_densities[name][0])
            num_notes_max = round(num_amount * note_densities[name][1])
            num_notes = ra.randint(num_notes_min, num_notes_max)

            # retrieve the durations
            durations = calculate_durations(num_amount, num_notes,)

            # repeat the bar - loop_amount times
            durations = loop_dur_list(durations, loop_amount,rand_input)

            #transform to timestamps
            time_durations = note_dur_to_td(durations,bpm,sig)
            timestamps = time_dur_to_ts(time_durations)
            #create events add them to a list
            event_list.append(create_events(name, timestamps, durations))
        #adding the different lists to a combined one
        event_list = [x for l in event_list for x in l]
        return event_list
#function for playing the events and displaying name + ts
def play_event(event,i):
    sampleName = event[i]["Sample"]
    samples[sampleName].play()
    #printing different symbols for visualisation
    if event[i]["Sample"] == 'kick':
        print('0')
    if event[i]["Sample"] == 'snare':
        print('=')
    if event[i]["Sample"] == 'hat':
        print('-')
    if event[i]["Sample"] == 'fx':
        print('~')
        
    #print(event[i]["Ts"])
#function for adding events to midi
def add_events_to_midi(events,quarter_note_dur,midi_file,track,channel,instr_midi_pitch,velocity):
    for event in events:
        # transform time (sec) to (qnote)
        
        qnote_time = event["Ts"] / quarter_note_dur
        instr_name = event["Sample"]
        midi_file.addNote(track, channel, instr_midi_pitch[instr_name], qnote_time,event["Nd"], velocity)