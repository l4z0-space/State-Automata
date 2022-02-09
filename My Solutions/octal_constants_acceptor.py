
# Build a program that simulates the Finite State Automata that scans and accepts or rejects input strings (sequences of characters) that may be considered as:
#     b/ octal constants (C/C++ notation);


def octal_constants_acceptor():
    '''
        TRANSITION TABLE
                q0  | q1
                ________
            0 | q1 | q1
        [0-7] | F  | q1
            # | F  | qf
    '''

    # BUILD THE TRANSITION TABLE
    TRANSITION_TABLE = {}
    TRANSITION_TABLE['q0'] = {} # Initialize the columns
    TRANSITION_TABLE['q1'] = {} # Initialize the columns

    # FILL THE CELLS FOR TRANSITION TABLE
    TRANSITION_TABLE['q0']['0'] = 'q1'
    TRANSITION_TABLE['q0']['D'] = 'F'
    TRANSITION_TABLE['q0']['#'] = 'F'

    TRANSITION_TABLE['q1']['0'] = 'q1'
    TRANSITION_TABLE['q1']['D'] = 'q1'
    TRANSITION_TABLE['q1']['#'] = 'qf'

    # VARIABLES
    q0 = 'q0'
    q1 = 'q1'
    qf = 'qf'
    L = 'L'
    ZERO = '0'
    D = 'D' # DIGIT HERE DENOTES DIGITS IN RANGE [0, 7]

    TERMINATOR = '#'
    CURRENT_STATE = q0
    TYPE = None
    FOUND = False

    PATTERN = '0012#'


    def get_type(char):
        '''
            Returns the type of the char.
            INVALID if no part of our alphabet
        '''
        if char.isdigit():
            if int(char) == 0:
                return ZERO
            if int(char) >= 0 and int(char) <= 7:
                return D
            else:
                return 'INVALID'
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
        print(f' > {PATTERN} is a valid octal constant! \n')

    else:
        print(f' > Terminating char was not found!')




def main():
	octal_constants_acceptor()


if __name__ == "__main__":
   main()