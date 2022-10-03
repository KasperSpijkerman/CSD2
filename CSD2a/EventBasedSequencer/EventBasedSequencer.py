import time
import simpleaudio as sa
import random as ra

#Samples 
Kick = sa.WaveObject.from_wave_file("assets/SD_Kick_Battalion.wav"),
Snare = sa.WaveObject.from_wave_file("assets/SD_Snare_Bewitch.wav"),
Hat  =  sa.WaveObject.from_wave_file("assets/SD_ClHat_Cherry.wav")

#Link the samples to a name in a dictionary
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


#Function for adding timestamp to event dictionairies
#Input the name of the instrument and the timestamp
def create_events(nametag,timestamps):
    #dictionary for event
    event_dict = {}
    #list with different events
    events_list = []
    #Create different dictionaries and add them to a list
    for i in range(len(timestamps)): 
        event_dict = {"sample":nametag, "Ts": timestamps[i]}
        events_list.append(event_dict.copy())
    return events_list


#executing the functions to generate different lists with timestamps per instrument
ts_kick_events = create_events(kick_event["Name"],time_stamps_kick)
ts_snare_events = create_events(snare_event["Name"],time_stamps_snare)
ts_hat_events = create_events(hat_event["Name"],time_stamps_hat)
#printing the function outputs
print(ts_kick_events)
print(ts_snare_events)
print(ts_hat_events)


#merge events
def merge_samples(kickevent,snareevent,hatevent):
	merged_events = kickevent | snareevent | hatevent
	return merged_events
events_sequence = merge_samples(kick_event,snare_event,hat_event)
print(events_sequence)

#Function for playing the sample on timestamp

# def play_samples(event,timestamp):
#     event['Name'].play()
# # print("the Timestamps are: ",time_stamps)

# # store the current time
# time_start = time.time()
# print("time zero:", time_start)

# # afspelen van de sequence ->nog aanpassen
# while True:
#     now = time.time() - time_start
#     if()
#     #check if the timestamp has been reached and play sample if so, stop loop if no timestamps.
# #     if(now >= tim ):
# #         play_obj = samples[].play()
# #         if(time_stamps):
# #             ts = time_stamps.pop(0)
# #         else:
# #             break
# #         time.sleep(0.001)

