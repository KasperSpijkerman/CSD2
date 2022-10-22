#Ui file the main will get the values from here. 
#Import sys for making sure control c will still work to quit the program.
import sys
def sig_input():
    #UI for input time signature
    #Making sure the user can only enter 5/4 or 7/8
    correct_sig = False
    while not correct_sig:
        try:
            time_sig = input("Fill in a irregular time signature for the sequence. Choose between 5/4 and 7/8: ")
            if time_sig == "5/4":
                correct_sig = True
            if time_sig == "7/8":
                correct_sig = True
        except KeyboardInterrupt:
            sys.exit()
        except:
            print("Incorrect signature enter 5/4 or 7/8") 
        

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
            keep_default = input("Default Bpm is 120, would you like to keep it? y/n ")
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
            user_bpm = input("Enter a bpm between the 60 and 500: ")

            # check if we 'received' an empty string
            if not user_bpm:
                # empty string --> use default
                correctInput = True
            else:
                try:
                    bpm = float(user_bpm)
                    if bpm >= 60 and bpm <= 500:
                        correctInput = True
                    else:
                        print("BPM out of range - please enter a bpm in range (or enter nothing - default bpm)")
                except KeyboardInterrupt:
                    sys.exit()
                except:
                    print("Incorrect input - please enter a bpm (or enter nothing - default bpm)")
    return(bpm)
def loop_input():
    #UI for loop amount
    #making sure the user can only input a whole number
    correct_loop = False
    while not correct_loop:
        try:
            loop_amount = int((input("Enter the amount of loops: ")))
            correct_loop = True
        
        except KeyboardInterrupt:
            sys.exit()
        except ValueError:
            print("Use a whole number please") 
    return(loop_amount)
def switch_input():
    #play the sequence when the user inputs y
    switch_seq = input("Play the sequence? y/n: ")
    return(switch_seq)


