#functions for converting values to timestamps and creating events
#also the function for exporting a midifile
from midiutil import MIDIFile
import UI_file as ui
import time
import simpleaudio as sa
import random as ra

def calculate_durations(steps,notes):
    note_durations = []
    duration16th = int(steps/notes)
    note_durations =[duration16th]*notes
    rest_value = steps - (notes * duration16th)
    for i in range(rest_value):
        note_durations[i] += 1
    return(note_durations)


    #function for converting notedurations to timedurations.
def note_dur_to_td(note_durations,bpm):
        
    time_durations = []
    dur_quarter = 60/bpm

    for note_dur in note_durations:
        time_durations.append(note_dur * dur_quarter)
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
    print('create_events', sample,timestamps,notedur)
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

    #function for repeating the sequence according to amount of loops
def loop_dur_list(note_durations,loop_amount,):
    note_durations_loop = list(note_durations)
    for i in range(loop_amount):
        for element in note_durations_loop:
            note_durations.append(element)
    #print("Looped list:", note_durations)
    return note_durations

#Samples 
samples = {
    'kick': sa.WaveObject.from_wave_file("assets/SD_Kick_Battalion.wav"),
    'snare': sa.WaveObject.from_wave_file("assets/SD_Snare_Bewitch.wav"),
    'hat': sa.WaveObject.from_wave_file("assets/SD_ClHat_Cherry.wav")
}

note_densities = {
    'kick': [0.2, 0.3],
    'snare': [0.3, 0.4],
    'hat': [0.5, 0.9]
}

#list with instruments dicts to choose from 
names = ['kick','snare','hat']


#rhythm generation
#euclidean steps for time signatures
num_amount_78 = 7
num_amount_54 = 5
#euclidean notevalues 
num_value_54 = 4
num_value_78 = 8


def execute_functions(names,num_amount,num_value,loop_amount):
        event_list = [] 
        for name in names:
        # calculate the range for the number of notes to generate
        # using the number of beats as maximum number of pulses
        # and applying the range of the given instrument
            num_notes_min = round(num_amount * note_densities[name][0])
            num_notes_max = round(num_amount * note_densities[name][1])
            num_notes = ra.randint(num_notes_min, num_notes_max)

            # retrieve the durations
            durations = calculate_durations(num_amount, num_notes)

            # repeat the bar - loop_amount times
            durations = loop_dur_list(durations, loop_amount)

            #transform to events
            time_durations = note_dur_to_td(durations,bpm)
            timestamps = time_dur_to_ts(time_durations)
            # NOTE: slightly adapted events format - see samples dictionary above,
            # name is sufficient to playback correct sample
            event_list.append(create_events(name, timestamps, durations))
            #adding the different lists to a combined one
        event_list = [x for l in event_list for x in l]
        return event_list




    

#function for playing the events and displaying name + ts
def play_event(event,i):
    sampleName = event[i]["Sample"]
    samples[sampleName].play()
    print(event[i]["Sample"])
    print(event[i]["Ts"])

bpm = ui.bpm
#additional midi values
quarter_note_dur = 60 / bpm
instr_midi_pitch = {
    "kick": 35,
    "snare": 38,
    "hat": 42,
    }

#print(all_sortedevents_list)
#setting default values for midi export
velocity= 80
track = 0
channel = 9 # corresponds to channel 10 drums

# create the MIDIfile object, to which we can add notes
midi_file = MIDIFile(1)
# set name and tempo
time_beginning = 0
midi_file.addTrackName(track, time_beginning, "Beat Sample Track")
midi_file.addTempo(track, time_beginning, bpm)

#function for adding events to midi
def add_events_to_midi(events,quarter_note_dur):
    for event in events:
        # transform time (sec) to (qnote)
        qnote_time = event["Ts"] / quarter_note_dur
        instr_name = event["Sample"]
        midi_file.addNote(track, channel, instr_midi_pitch[instr_name], qnote_time,event["Nd"], velocity)