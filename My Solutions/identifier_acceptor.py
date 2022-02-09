
# Build a program that simulates the Finite State Automata operating as an acceptor of 
# identifiers, i.e. strings of alphanumeric characters preceded by an alphabetic character 
# are accepted. All other strings are rejected as invalid input. The simulator operates on
# all input sequences up to the end of file indicator



def identifier_acceptor():
    '''
        TRANSITION TABLE
                q0  | q1
                ________
            L | q1 | q1
            D | F  | q1
            # | F  | qf
    '''

    # BUILD THE TRANSITION TABLE
    TRANSITION_TABLE = {}
    TRANSITION_TABLE['q0'] = {} # Initialize the columns
    TRANSITION_TABLE['q1'] = {} # Initialize the columns

    # FILL THE CELLS FOR TRANSITION TABLE
    TRANSITION_TABLE['q0']['L'] = 'q1'
    TRANSITION_TABLE['q0']['D'] = 'F'
    TRANSITION_TABLE['q0']['#'] = 'F'
    TRANSITION_TABLE['q1']['L'] = 'q1'
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

    PATTERN = 'f212#'


    def get_type(char):
        '''
            Returns the type of the char.
            INVALID if no part of our alphabet
        '''

        if char.isalpha():
            return L
        elif char.isdigit():
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
	identifier_acceptor()


if __name__ == "__main__":
   main()