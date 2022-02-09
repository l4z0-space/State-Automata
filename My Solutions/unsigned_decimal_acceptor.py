
# Build a program that simulates the Finite State Automata that scans and accepts or rejects input strings (sequences of characters) that may be considered as:
#   a/ unsigned integer decimal constants;



def unsigned_decimal_acceptor():
    '''
        TRANSITION TABLE
                q0  | q1
                ________
            D | q1 | q1
            # | F  | qf
    '''

    # BUILD THE TRANSITION TABLE
    TRANSITION_TABLE = {}
    TRANSITION_TABLE['q0'] = {} # Initialize the columns
    TRANSITION_TABLE['q1'] = {} # Initialize the columns

    # FILL THE CELLS FOR TRANSITION TABLE
    TRANSITION_TABLE['q0']['D'] = 'q1'
    TRANSITION_TABLE['q0']['#'] = 'F'
    TRANSITION_TABLE['q1']['D'] = 'q1'
    TRANSITION_TABLE['q1']['#'] = 'qf'

    # VARIABLES
    q0 = 'q0'
    q1 = 'q1'
    qf = 'qf'
    L = 'L'
    D = 'D'
    TERMINATOR = '#'
    CURRENT_STATE = q0
    TYPE = None
    FOUND = False

    PATTERN = '#'


    def get_type(char):
        '''
            Returns the type of the char.
            INVALID if no part of our alphabet
        '''
        if char.isdigit():
            return D
        elif char == TERMINATOR:
            return char
        else:
            return 'INVALID'


    for current_char in PATTERN:

        TYPE = get_type(current_char)
        if TYPE == 'INVALID':
            print(f'Error: INVALID CHAR > "{current_char}"')
            return

        
        NEW_STATE = TRANSITION_TABLE[CURRENT_STATE][TYPE]
    
        print(f'\nState: {CURRENT_STATE} + {TYPE} GOES TO STATE  > {NEW_STATE} \n')

        CURRENT_STATE = NEW_STATE

        if CURRENT_STATE == qf:
            FOUND = True

        elif CURRENT_STATE == 'F':
            print(f' > Program was terminated at transition: state "{CURRENT_STATE}" + "{TYPE}"')
            return

    if FOUND:
        print(f' > {PATTERN} is a valid identifier! \n')

    else:
        print(f' > Terminating char was not found!')




def main():
	unsigned_decimal_acceptor()


if __name__ == "__main__":
   main()