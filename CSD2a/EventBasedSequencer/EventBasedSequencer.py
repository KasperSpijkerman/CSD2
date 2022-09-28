import time
import simpleaudio as sa
import random as ra

#Samples dictionary 
samples = {
    "Kick":  sa.WaveObject.from_wave_file("assets/SD_Kick_Battalion.wav"),
    "Snare": sa.WaveObject.from_wave_file("assets/SD_Snare_Bewitch.wav"),
    "Hat":   sa.WaveObject.from_wave_file("assets/SD_ClHat_Cherry.wav")
    }


#default bpm
bpm = 120

#list with note durations
note_durations = []

#functie omzetten note duraties
def note_dur_to_td(note_dur,bpm):
   
#to do: dictionary maken met samples, namen en timestamps
#nootduraties omzetten naar timestamps


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