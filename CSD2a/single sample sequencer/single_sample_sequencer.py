#import simpleaudio module and time module
import simpleaudio as sa
import time 
#input username for walk through user
username = input("Enter Username: ")
print("Hello " + username) 
print('This is a rhythmical sample player')

#input for amount of playback times
numPlaybackTimes = int(input('Fill in the times of playback of the sample: '))
#empty list for the time between the samples
rhythm = []

#verschillende waardes voor in de lijst
#vullen lijsten met hoe vaak de gebruiker invult.
for i in range(0,numPlaybackTimes):
    noteValue = float(input("Fill in the note durations "))

    rhythm.append(noteValue)

print(rhythm)
bpm = float(input("Fill in the bpm for the duration of a quarter note ") )
dur_quarter = 60/bpm
time_Durations = [rhythmInS * dur_quarter for rhythmInS in rhythm]
print(time_Durations)

#transform time durations into timestamp sequence. 
seq_Timestamps = []

#sum the durations for time sequence
sum = 0
for time_dur in time_Durations:
    seq_Timestamps.append(sum)
    sum = sum + time_dur
print(seq_Timestamps)


# choose sample file
wave_obj = sa.WaveObject.from_wave_file("assets/SD_Kick_Onset.wav")

#get the timestamp 
if seq_Timestamps:
    ts = seq_Timestamps.pop(0)
else:
    print("no timestamps so sequence stops")

#Capture current time
time_start = time.time()
print("start time = ",time_start)


#Go through the timestamps sequence and play the sample
#While true has no statements, it just stops when break.
while True:
    now = time.time() - time_start
    #check if the timestamp has been reached and play sample if so, stop loop if no timestamps.
    if(now >= ts):
        play_obj = wave_obj.play()
        if(seq_Timestamps):
            ts = seq_Timestamps.pop(0)
        else:
            break
    time.sleep(0.001)

time.sleep(time_Durations[-1])


