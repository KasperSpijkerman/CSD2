import time
import simpleaudio as sa
import random as ra

#Samples dictionary 
samples = {
    "Kick":  sa.WaveObject.from_wave_file("assets/SD_Kick_Battalion.wav"),
    "Snare": sa.WaveObject.from_wave_file("assets/SD_Snare_Bewitch.wav"),
    "Hat":   sa.WaveObject.from_wave_file("assets/SD_ClHat_Cherry.wav")
    }


#list with note durations
note_durations = []
time_stamps = []
#gebasseerd op de les
correctInput = False
bpm = 120

while (not correctInput):
    user_bpm = input("enter a bpm")

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



#function for converting notedurations to timedurations.
def note_dur_to_td(note_durations,bpm):
    
    time_durations = []
    dur_bpm = 60/bpm

    for note_dur in note_durations:
        time_durations.append(note_dur * dur_bpm)
    return time_durations

#function converting time durations to timestamps
def time_dur_to_ts(time_durations):
    time_stamps = []
    timestamp = 0
    # iterate through the source sequence, sum durations and store these as
    # timestamp in the destination Sequence
    for time_dur in time_durations:
        timestamps.append(timestamp)
        timestamp += time_dur

    return time_stamps

#to do: dictionary maken met samples, namen en timestamps
#inputs voor verschillende waardes zoals bpm
#nootduraties omzetten naar timestamps
#minimaal 16 events 


#afspelen van de sequence ->nog aanpassen
while True:
    now = time.time() - time_start
    #check if the timestamp has been reached and play sample if so, stop loop if no timestamps.
    if(now >= ts):
        play_obj = wave_obj.play()
        if(timestamps):
            ts = timestamps.pop(0)
        else:
            break
        time.sleep(0.001)

#16 maten