import time
import simpleaudio as sa
import random as ra

#Samples 
Kick= sa.WaveObject.from_wave_file("assets/SD_Kick_Battalion.wav")
Snare= sa.WaveObject.from_wave_file("assets/SD_Snare_Bewitch.wav")
Hat=  sa.WaveObject.from_wave_file("assets/SD_ClHat_Cherry.wav")

#Link the samples to a name in a dictionary
kick_event = {
    "Name": "Kick",
    "Instrument": Kick,
    }

snare_event = {
    "Name": "Snare",
    "Instrument": Snare,
    }

hat_event = {
    "Name": "Hat",
    "Instrument": Hat,
    }
#input BPM
#gebasseerd op de les
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

#Note durations pre generated, to do - > input
note_durations_kick = [1,2,1,1]
note_durations_snare = [2,1,3,1]
note_durations_hat = [0.5,0.5,0.5,0.5]

#function for converting notedurations to timedurations.
def note_dur_to_td(note_durations,bpm):
    
    time_durations = []
    dur_bpm = 60/bpm

    for note_dur in note_durations:
        time_durations.append(note_dur * dur_bpm)
    return time_durations

#fill the time durations array with time durations calculated from note durations
#for every seperate sample
time_durations_kick = note_dur_to_td(note_durations_kick,bpm)
time_durations_snare = note_dur_to_td(note_durations_snare,bpm)
time_durations_hat = note_dur_to_td(note_durations_hat,bpm)
print("Kick Time durations: ", time_durations_kick)
print("Snare Time durations: ", time_durations_snare)
print("Hat Time durations: ", time_durations_hat)

#function converting time durations to timestamps
def time_dur_to_ts(time_durations):
    time_stamps = []
    timestamp = 0
    # iterate through the source sequence, sum durations and store these as
    # timestamp in the destination Sequence
    for time_dur in time_durations:
        time_stamps.append(timestamp)
        timestamp += time_dur

    return time_stamps


time_stamps_kick = time_dur_to_ts(time_durations_kick)
time_stamps_snare = time_dur_to_ts(time_durations_snare)
time_stamps_hat = time_dur_to_ts(time_durations_hat)

#printing the different timestamps 
print("Timestamps Kick: ",time_stamps_kick)
print("Timestamps Snare: ",time_stamps_snare)
print("Timestamps Hat: ",time_stamps_hat)


#function for adding timestamp to event dictionairies
#input the name of the instrument and the timestamp
def create_events(nametag,timestamps):
    #dictionary for 1 event
    event_dict = {}
    #empty list for different events
    events_list = []
    #create different dictionaries and add them to a list
    #creating copies of the event dict otherwise it will just output 1 dict.
    for i in range(len(timestamps)): 
        event_dict = {"Sample":nametag, "Ts": timestamps[i]}
        events_list.append(event_dict.copy())
    return events_list


#executing the functions to generate different lists with timestamps per instrument
ts_kick_events = create_events(kick_event["Instrument"],time_stamps_kick)
ts_snare_events = create_events(snare_event["Instrument"],time_stamps_snare)
ts_hat_events = create_events(hat_event["Instrument"],time_stamps_hat)
#printing the function outputs
print("The Kick events: ",ts_kick_events)
print("The Snare events: ",ts_snare_events)
print("The Hat events: ", ts_hat_events)

#merge all seperate events to 1 list
all_events_list = ts_kick_events + ts_snare_events + ts_hat_events

print("All Events: ",all_events_list)

#sort the event list based on timestamp
all_sortedevents_list = sorted(all_events_list, key=lambda d: d['Ts']) 

print("All events sorted", all_sortedevents_list)

#a function for playing the sample
def play_event(event):
    print(event['Sample'])
    event['Sample'].play()


# store the current time
time_start = time.time()
print("Start ", time_start)

#Play sequence according to timestamp and instrument
while True:
    now = time.time() - time_start
    for i in range(len(all_sortedevents_list)):
        if now >= all_sortedevents_list[i]["Ts"]:
            play_event(all_sortedevents_list[i])
            time.sleep(0.1)
            play_event(all_sortedevents_list[i])

            
            

