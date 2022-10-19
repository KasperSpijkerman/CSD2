#Ui file the main will get the values from here. 
#input username and explanation of rhythm generator
username = input("Enter Username: ")
print("Hello " + username) 
print('This is the Irregular Beat Generator 3000')


#UI for input time signature
time_sig = input("Fill in a irregular time signature for the sequence. Choose between 5/4 and 7/8: ")

print("Time Signature is: ", time_sig)
#checking the user input and executing the function
#To do fix correctinput



#UI for loop amount
loop_amount = int((input("Enter the amount of loops: ")))

#input for bpm
correctInput = False
bpm = 120
#Check the bpm and see if it is the right value. 

default_bpm = True

keep_default = input("Default Bpm is 120, would you like to keep it? y/n ")

if keep_default == "n":
    default_bpm = False
else:
    default_bpm = True


if default_bpm == False:
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

#play the sequence when the user inputs y
switch_seq = input("Play the sequence? y/n: ")


export_true = False
store = input("Would you like to export the sequence into a Midifile? y/n ")

