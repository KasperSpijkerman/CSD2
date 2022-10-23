#Ui file the main will get the values from here. 
#Import sys for making sure control c will still work to quit the program.
import sys
def sig_input():
    #UI for input time signature
    #Making sure the user can only enter 5/4 or 7/8
    correct_sig = False
    while not correct_sig:
        try:
            time_sig = input("So first: Choose a time signature for your adventure. Choose between 5/4 and 7/8: ")
            if time_sig == "5/4":
                correct_sig = True
            if time_sig == "7/8":
                correct_sig = True
        except KeyboardInterrupt:
            sys.exit()
        except:
            print("Please enter 5/4 or 7/8") 
        

    return time_sig    
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

    for name in names:
        print (name)
        correct_inst = False
        while not correct_inst:
            try:
                keep_inst = input("Would you like to have this instrument in the sequence? y/n")
                if keep_inst == "y":
                    correct_inst = True
                if keep_inst == "n":
                    correct_inst = True
                    names.pop(name)
            except KeyboardInterrupt:
                sys.exit()
            except:
                print("Incorrect input enter y/n") 
def dens_input():
    correct_dens = False
    while not correct_dens:
        try:
            note_dens = input("Fill in the density per instrument from 1 to 5. Start with kick, snare, hat then fx. ")
            if note_dens == "1":
                correct_dens = True
                print(note_dens)
            if note_dens == "2":
                correct_dens = True
                print(note_dens)
            if note_dens == "3":
                correct_dens = True
                print(note_dens)
            if note_dens == "4":
                correct_dens = True
                print(note_dens)
            if note_dens == "5":
                correct_dens = True
                print(note_dens)
                
        except KeyboardInterrupt:
            sys.exit()
        except:
            print("Incorrect number please enter 1, 2, 3, 4 or 5 for low or high density") 
    return(note_dens)
def loop_input():
    #UI for loop amount
    #making sure the user can only input a whole number
    correct_loop = False
    while not correct_loop:
        try:
            loop_amount = int((input("Enter the amount of loops for the duration of the whole trip ")))
            correct_loop = True
        
        except KeyboardInterrupt:
            sys.exit()
        except ValueError:
            print("Use a whole number please") 
    return(loop_amount)
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
                print('Too scared to travel? You can still safe the experience to use somewhere else ')
        except KeyboardInterrupt:
            sys.exit()
        except:
            print("Please enter y or n") 
    return(switch_seq)


