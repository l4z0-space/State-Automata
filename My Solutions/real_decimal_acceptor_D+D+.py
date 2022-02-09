
# Build a program that simulates the Finite State Automata that scans and accepts or rejects input strings (sequences of characters) that may be considered as:
#     d/ D+.D+;


def real_decimal_acceptor():
    '''
        TRANSITION TABLE
                q0 | q1 | q2 | q3
                __________________
            D | q1 | q1 | q3 | q3
            . | F  | q2 | F  | F
            # | F  | F  | F  | qf
    '''

    # BUILD THE TRANSITION TABLE
    TRANSITION_TABLE = {}
    TRANSITION_TABLE['q0'] = {} # Initialize the columns
    TRANSITION_TABLE['q1'] = {} # Initialize the columns
    TRANSITION_TABLE['q2'] = {} # Initialize the columns
    TRANSITION_TABLE['q3'] = {} # Initialize the columns

    # FILL THE CELLS FOR TRANSITION TABLE
    TRANSITION_TABLE['q0']['D'] = 'q1'
    TRANSITION_TABLE['q0']['.'] = 'F'
    TRANSITION_TABLE['q0']['#'] = 'F'

    TRANSITION_TABLE['q1']['D'] = 'q1'
    TRANSITION_TABLE['q1']['.'] = 'q2'
    TRANSITION_TABLE['q1']['#'] = 'F'

    TRANSITION_TABLE['q2']['D'] = 'q3'
    TRANSITION_TABLE['q2']['.'] = 'F'
    TRANSITION_TABLE['q2']['#'] = 'F'

    TRANSITION_TABLE['q3']['D'] = 'q3'
    TRANSITION_TABLE['q3']['.'] = 'F'
    TRANSITION_TABLE['q3']['#'] = 'qf'

    # VARIABLES
    q0 = 'q0'
    q1 = 'q1'
    qf = 'qf'
    L = 'L'
    DOT = '.'
    ZERO = '0'
    D = 'D' # DIGIT HERE DENOTES DIGITS IN RANGE [0, 7]

    TERMINATOR = '#'
    CURRENT_STATE = q0
    TYPE = None
    FOUND = False

    PATTERN = '3.2#'


    def get_type(char):
        '''
            Returns the type of the char.
            INVALID if no part of our alphabet
        '''
        if char.isdigit():
            return D
      
        elif char == TERMINATOR:
            return char

        elif char == '.':
            return DOT
        else:
            return 'INVALID'


    for current_char in PATTERN:

        TYPE = get_type(current_char)
        if TYPE == 'INVALID':
            print(f' > Error: INVALID CHAR - "{current_char}"')
            return

        
        NEW_STATE = TRANSITION_TABLE[CURRENT_STATE][TYPE]
    
        print(f'\nState: {CURRENT_STATE} + {TYPE} GOES TO STATE  > {NEW_STATE} \n')


        if NEW_STATE == qf:
            FOUND = True

        elif NEW_STATE == 'F':
            print(f' > Program was terminated at transition: state "{CURRENT_STATE}" + "{TYPE}"')
            return

        CURRENT_STATE = NEW_STATE
        

    if FOUND:
        print(f' > {PATTERN} is a valid real declimal! D+D+\n')

    else:
        print(f' > Terminating char was not found!')




def main():
	real_decimal_acceptor()


if __name__ == "__main__":
   main()