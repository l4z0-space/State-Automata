
# Build a program that simulates the Finite State Automata that scans and accepts or rejects input strings (sequences of characters) that may be considered as:
#   a/ unsigned integer decimal constants;



def real_decimal_fractional_acceptor():
    '''
        TRANSITION TABLE
                q0      | q1 | q2 | q3 | q4 | q5 | q6 | q7 | q8 | q9  | q10 | q11
                ____________________________________________________________
            D  | F      | q2 | q2 | q4 | q4 | q6 | q6 | q8 | q8 | q11 | q11 | q11
            .  | F      | q3 | q3 | F  | F  | F  | F  | F  | F  | F   | F   | F
         (E|e) | F      | F  | F  | F  | q9 | F  | F  | F  | q9 | F   | F   | F
    (+|-| eps) | F      | F  | F  | F  | F  | F  | F  | F  | F  | q10 | F   | F
            #  | F      | F  | F  | F  | F  | F  | F  | F  | F  | F   | F   | qf
          eps  | q1, q2 | F  | F  | F  | F  | F  | F  | F  | F  | F   | F   | qf

    '''

    # BUILD THE TRANSITION TABLE
    TRANSITION_TABLE = {}
    TRANSITION_TABLE['q0'] = {} # Initialize the columns
    TRANSITION_TABLE['q1'] = {} # Initialize the columns
    TRANSITION_TABLE['q2'] = {} # Initialize the columns
    TRANSITION_TABLE['q3'] = {} # Initialize the columns
    TRANSITION_TABLE['q4'] = {} # Initialize the columns
    TRANSITION_TABLE['q5'] = {} # Initialize the columns
    TRANSITION_TABLE['q6'] = {} # Initialize the columns
    TRANSITION_TABLE['q7'] = {} # Initialize the columns
    TRANSITION_TABLE['q8'] = {} # Initialize the columns
    TRANSITION_TABLE['q9'] = {} # Initialize the columns
    TRANSITION_TABLE['q10'] = {} # Initialize the columns
    TRANSITION_TABLE['q11'] = {} # Initialize the columns

    # FILL THE CELLS FOR TRANSITION TABLE
    TRANSITION_TABLE['q0']['e'] = 'q1' # or TRANSITION_TABLE['q0']['e'] = 'q2'

    TRANSITION_TABLE['q1']['D'] = 'q2'
    TRANSITION_TABLE['q1']['.'] = 'q3'
    
    TRANSITION_TABLE['q2']['D'] = 'q2'
    TRANSITION_TABLE['q2']['.'] = 'q3'

    TRANSITION_TABLE['q3']['D'] = 'q4'


    TRANSITION_TABLE['q4']['D'] = 'q4'
    TRANSITION_TABLE['q4']['e'] = 'q9'
    TRANSITION_TABLE['q4']['E'] = 'q9'
    

    TRANSITION_TABLE['q5']['D'] = 'q6'


    TRANSITION_TABLE['q6']['D'] = 'q6'
    TRANSITION_TABLE['q6']['.'] = 'q7'

    TRANSITION_TABLE['q7']['D'] = 'q8'

    TRANSITION_TABLE['q8']['D'] = 'q8'
    TRANSITION_TABLE['q8']['e'] = 'q9'
    TRANSITION_TABLE['q8']['E'] = 'q9'

    TRANSITION_TABLE['q9']['+'] = 'q9'
    TRANSITION_TABLE['q9']['-'] = 'q9'
    TRANSITION_TABLE['q9']['D'] = 'q11'

    TRANSITION_TABLE['q10']['D'] = 'q11'

    TRANSITION_TABLE['q11']['D'] = 'q11'
    TRANSITION_TABLE['q11']['#'] = 'qf'


    # VARIABLES
    q0 = 'q0'
    q1 = 'q1'
    qf = 'qf'
    L = 'L'
    D = 'D'
    DOT = '.'
    E = 'E'
    e = 'e'
    PLUS = '+'
    MINUS = '-'
    TERMINATOR = '#'
    CURRENT_STATE = q0
    TYPE = None
    FOUND = False

    PATTERN = '12.2#'


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

        NEW_STATE = None
        try:
            NEW_STATE = TRANSITION_TABLE[CURRENT_STATE][TYPE]
        except KeyError:
            NEW_STATE = 'F'
    
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
	real_decimal_fractional_acceptor()


if __name__ == "__main__":
   main()