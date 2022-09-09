#importeren van simpleaudio module
import simpleaudio as sa
#invoeren username voor persoonlijke groeting/uitleg.
username = input("Enter Username: ")
print("Hello " + username) 
print('This is a sample player')

#aantal keer sample afspelen input
amount = input('Fill in the times of playback of the sample: ')

#bestand kiezen voor sample
wave_obj = sa.WaveObject.from_wave_file("/Volumes/SSD Kasper 1/HKU/Jaar_2/CSD2/python_basics/Sample_Playsoundscript/SD_DrumLoop_Approximation_80.wav")

#sample afspelen aantal keer dat die is ingevoerd en wachten tot het klaar is.
while amount != 0:
    play_obj = wave_obj.play()
    play_obj.wait_done()
    amount = int(amount) -1
    print(amount)
    if int(amount) == 0:
        break
