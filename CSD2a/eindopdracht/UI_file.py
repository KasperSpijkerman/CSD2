#Ui file the main will get the values from here. 
#Import sys for making sure control c will still work to quit the program.
import sys
#signature input 5/4 or 7/8
def sig_input():
    #UI for input time signature
    #Making sure the user can only enter 5/4 or 7/8
    correct_sig = False
    while not correct_sig:
        try:
            time_sig = input("So first: Choose a time signature for your adventure. Choose between 5/4 and 7/8 or crazy: ")
            if time_sig == "5/4":
                correct_sig = True
            if time_sig == "7/8":
                correct_sig = True
            if time_sig == "crazy":
                correct_sig = True
            else:
                print("Please enter 5/4 or 7/8 or crazy") 
        except KeyboardInterrupt:
            sys.exit()
        except:
            print("Please enter 5/4 or 7/8 or crazy") 
        

    return time_sig  
#extra input for custom signature.
def custom_sig_input():
    correct_custom_sig = False
    while not correct_custom_sig:
        try:
            user_sig = int(input("Enter a custom amount of beats, min 3 max 16: "))
            if user_sig >= 3 and user_sig <= 16:
                correct_custom_sig = True
            else:
                print("Enter a value between 3 and 16")
        except KeyboardInterrupt:
            sys.exit()
        except:
            print("Enter a value between 3 and 16")
    return(user_sig)
#bpm input keep default or custom user input
def bpm_input():
    #input for bpm
    correctInput = False
    #Check the bpm and see if it is the right value. 
    bpm = 120
    default_bpm = True
    correct_default_bpm = False
    while not correct_default_bpm:
        try:
            keep_default = input("The speed is set to 120 BPM, would you like to keep it? y/n ")
            if keep_default == "y":
                correct_default_bpm = True
                default_bpm = True
            if keep_default == "n":
                correct_default_bpm = True
                default_bpm = False
            else:
                print("Please enter y or n:")
        except KeyboardInterrupt:
            sys.exit()
        except:
            print("Please enter y or n:")


    if default_bpm == False:
        while (not correctInput):
            user_bpm = input("Enter a bpm between the 60 and 300: ")

            # check if we 'received' an empty string
            if not user_bpm:
                # empty string --> use default
                correctInput = True
            else:
                try:
                    bpm = float(user_bpm)
                    if bpm >= 60 and bpm <= 300:
                        correctInput = True
                    else:
                        print("BPM out of range - please enter a bpm in range (or enter nothing - default bpm)")
                except KeyboardInterrupt:
                    sys.exit()
                except:
                    print("Incorrect input - please enter a bpm (or enter nothing - default bpm)")
    return(bpm)
#note density input, lets the user decide per instrument how dense the sequence is
def dens_input():
    correct_dens = False
    while not correct_dens:
        try:
            #seperated them in seperate conditions.
            note_dens = input("Fill in the density per instrument from 1 to 5. Start with kick, snare, hat then fx. ")
            if note_dens == "1":
                correct_dens = True
            if note_dens == "2":
                correct_dens = True
            if note_dens == "3":
                correct_dens = True
            if note_dens == "4":
                correct_dens = True
            if note_dens == "5":
                correct_dens = True
            if note_dens == "0":
                correct_dens = True
            else:
                print("Incorrect number please enter 1 to 5 for low or high density")
                
        except KeyboardInterrupt:
            sys.exit()
        except:
            print("Incorrect number please enter 1 to 5 for low or high density") 
    return(note_dens)
#input for the amount of loops
def loop_input():
    #UI for loop amount
    #making sure the user can only input a whole number
    correct_loop = False
    while not correct_loop:
        try:
            loop_amount = int((input("Enter the amount of loops for the duration of the whole trip (max 10) ")))
            if loop_amount <= 10:
                correct_loop = True
            else:
                print("Use a whole number please, not larger then 10") 
        
        except KeyboardInterrupt:
            sys.exit()
        except ValueError:
            print("Use a whole number please, not larger then 10") 
    return(loop_amount)
#input yes or no for playing the sequence
def switch_input():
    #play the sequence when the user inputs y
    correct_switch = False
    while not correct_switch:
        try:
            switch_seq = input("Ready for take off? y/n: ")
            if switch_seq == "y":
                correct_switch = True
            if switch_seq == "n":
                correct_switch = True
                print('Too scared to travel? You can still save the experience to use somewhere else ')
            else:
                print("Please enter y or n") 
        except KeyboardInterrupt:
            sys.exit()
        except:
            print("Please enter y or n") 
    return(switch_seq)
#input for randomizer
def randomizer_input():
    correct_rand_in = False
    while not correct_rand_in:
        try:
            rand_input = input("Would you like a steady trip or a more adventurous one? Enter steady or adventure ")
            if rand_input == "steady":
                correct_rand_in = True
                print("Have a steady trip!")
            if rand_input == "adventure":
                correct_rand_in = True
                print("Let's go on adventure!")
            else:
                print("Please enter steady or adventure") 
        except KeyboardInterrupt:
            sys.exit()
        except:
            print("Please enter steady or adventure") 
    return(rand_input)

