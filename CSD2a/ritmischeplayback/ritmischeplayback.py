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
    noteValue = float(input("Fill in the time in (s) between the samples and press enter: "))

    rhythm.append(noteValue)

print(rhythm)
bpm = float(input("Fill in the bpm for the speed: ") )
dur_quarter = 60/bpm
timeDurations = [rhythmInS * dur_quarter for rhythmInS in rhythm]
print(timeDurations)

# bestand kiezen voor sample
wave_obj = sa.WaveObject.from_wave_file("assets/SD_Kick_Onset.wav")

#sample afspelen aantal keer dat die is ingevoerd en wachten tot het klaar is.
for numPlaybackTimes in range(len(timeDurations)):
    play_obj = wave_obj.play()
    # play_obj.wait_done()
    time.sleep(timeDurations[numPlaybackTimes])
        

