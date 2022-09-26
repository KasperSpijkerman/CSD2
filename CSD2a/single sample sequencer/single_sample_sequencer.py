#import simpleaudio module and time module
import simpleaudio as sa
import time 
#input username for walk through user
username = input("Enter Username: ")
print("Hello " + username) 
print('This is a Single Sample Sequencer')
bpm = 120
quarterNoteDuration = 60 / bpm
sixteenthNoteDuration = quarterNoteDuration/4
print("The default bpm is:", bpm)
bpm = int(input("Input the bpm: "))

# empty timestamp list, will be filled in based on bpm and timestamps in 16th
timestamps = []

#empty list for 16th timestamps
timestamps16th = []

#list with possible notedurations
noteDurations = []

#input for amount of playback times
sampleAmount = int(input("Input the amount of samples: "))
loopPlayback = int(input("Input the amount of loops: "))


#input for notedurations
for i in range(0,sampleAmount):
    noteDuration = float(input("Fill in the note durations "))

    noteDurations.append(noteDuration) 
print("Note durations are: ", noteDurations)

#function for converting durations to 16th timestamps.
def durationsToTimestamps16th(noteduration):
    sum = 0
    timestamps16th.append(sum)
    for  noteduration in noteDurations:
        sum = sum + 4* noteduration 
        timestamps16th.append(sum)
    return(timestamps16th)

timestamps16th = durationsToTimestamps16th(noteDurations)
print("Timestamps in 16thn notes are: ", timestamps16th)


def timestampBPMinput(bpm, timestamps16th):
    quarterNoteDuration = 60 / bpm
    sixteenthNoteDuration = quarterNoteDuration/4
    for timestamp in timestamps16th:
        timestamps.append(timestamp * sixteenthNoteDuration)

    print("The timestamps based on bpm are: ",timestamps)

timestampBPMinput(bpm, timestamps16th)


# choose sample file
wave_obj = sa.WaveObject.from_wave_file("assets/SD_Kick_Onset.wav")

#get the timestamp 
if timestamps:
    ts = timestamps.pop(0)
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
        if(timestamps):
            ts = timestamps.pop(0)
        else:
            break
        time.sleep(0.001)
    

#  time.sleep(noteDurations[-1])


