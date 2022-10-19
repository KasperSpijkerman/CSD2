#functions for converting values to timestamps and creating events
#also the function for exporting a midifile
from midiutil import MIDIFile
import UI_file as ui

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


    #function for repeating the sequence according to amount of loops
def loop_dur_list(note_durations,loop_amount,):
    note_durations_loop = list(note_durations)
    for i in range(loop_amount):
        for element in note_durations_loop:
            note_durations.append(element)
    #print("Looped list:", note_durations)
    return note_durations

    

#function for playing the events and displaying name + ts
def play_event(event,i):
    event[i]['Sample'].play()
    print(event[i]["Name"])
    print(event[i]["Ts"])

bpm = ui.bpm
#additional midi values
quarter_note_dur = 60 / bpm
instr_midi_pitch = {
    "Kick": 35,
    "Snare": 38,
    "Hat": 42,
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
        instr_name = event["Name"]
        midi_file.addNote(track, channel, instr_midi_pitch[instr_name], qnote_time,event["Nd"], velocity)