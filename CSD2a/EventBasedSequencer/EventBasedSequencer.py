import time
import simpleaudio as sa
import random as ra

#Samples 
Kick = sa.WaveObject.from_wave_file("assets/SD_Kick_Battalion.wav"),
Snare = sa.WaveObject.from_wave_file("assets/SD_Snare_Bewitch.wav"),
Hat  =  sa.WaveObject.from_wave_file("assets/SD_ClHat_Cherry.wav")

#Events
kick_event = {
    "Name": "Kick",
    "Instrument": Kick
    }

snare_event = {
    "Name": "Snare",
    "Instrument": Snare,
    }

hat_event = {
    "Name": "Hat",
    "Instrument": Hat,
    }

#list with note durations
note_durations = []
time_stamps = []
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

note_durations = [1,2,1,1]

#function for converting notedurations to timedurations.
def note_dur_to_td(note_durations,bpm):
    
    time_durations = []
    dur_bpm = 60/bpm

    for note_dur in note_durations:
        time_durations.append(note_dur * dur_bpm)
    return time_durations

#fill the time durations array with time durations calculated from note durations
time_durations = note_dur_to_td(note_durations,bpm)
print(time_durations)

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
time_stamps = time_dur_to_ts(time_durations)

print(time_stamps)

#Function for adding timestamp to kickevent
def create_events(event):
    for i in range(len(time_stamps)):
        event['Timestamp'+str(i)] = time_stamps[i]


# events_sequence = {"Sample": "", "ts": 0.0}
# def add_timestamp(timestamp,event,eventnumber):
#     for i in range(len(time_stamps)):
#         event["Timestamp"] = time_stamps[]

create_events(kick_event)
create_events(snare_event)
print(kick_event)
print(snare_event)
# add_timestamp(time_stamps,kick_event)
# print(events_sequence)
        
# for sample, timestamp in kick_event.items()
#         events_sequence["Sample"] = event["Name"]
#         events_sequence["ts"] = time_stamps









#Function for playing the sample on timestamp

# def play_samples(event):
#     event['instrument'].play()
# # print("the Timestamps are: ",time_stamps)

#sequence maken die bestaat uit events
#sample select maken bij verschillende timestamps
# for timestamps in time_stamps:
#     samples["TimestampKick"] = time_stamps[0]
#     samples["TimestampKick"] = time_stamps[1]
#     samples["TimestampKick"] = time_stamps[3]

# print(samples["TimestampKick"])
# #to do: dictionary maken met samples, namen en timestamps
# #minimaal 16 events 
# #koppeling timestamp en sample 

# #get the timestamp 
# if time_stamps:
#     ts = time_stamps.pop(0)
# else:
#     print("No timestamps so sequence stops")


# # store the current time
# time_start = time.time()
# print("time zero:", time_start)

#afspelen van de sequence ->nog aanpassen
# while True:
#     now = time.time() - time_start
#     #check if the timestamp has been reached and play sample if so, stop loop if no timestamps.
#     if(now >= ):
#         play_obj = samples[].play()
#         if(time_stamps):
#             ts = time_stamps.pop(0)
#         else:
#             break
#         time.sleep(0.001)

