import json
import os
import re
import struct
import subprocess

# CONFIGURATION CODE BEGIN

# predefined source code goes into this multi-line string
PREDEFINED_CODE = r"""
"""

# These two variables define the code that must be present and the code that cannot be present in the student answer
# Each is a list of tuples where each tuple has the following elements:
#   - first element is the regex expression
#   - second element represents flags used for that expression, if no flags are used write 0
#   - third element is a message that will be written to the student if the condition is not met
REQUIRED_CODE = [

]
FORBIDDEN_CODE = [

]

# test points, a list of tuples, each tuple has the following elements:
#   - first element is a relative score for a certain file
#   - second element is a list of points for lines within a file
TEST_POINTS = [
    (100, [100])
]

# flags for compilation
FLAGS = ["-lm", "-g"]

# hidden test numbers, starting from 0
HIDDEN_TESTS = [

]

# memory allocation failure chance, must a value between 0 and 1
MEMORY_ALLOCATION_FAILURE_CHANCE      = 0
MEMORY_ALLOCATION_FAILURE_RETURN_CODE = 200

# file allocation failure chance, must a value between 0 and 1
FILE_OPEN_FAILURE_CHANCE      = 0
FILE_OPEN_FAILURE_RETURN_CODE = 201

# point deduction for memory leak, percentage
MEMORY_LEAK_PENALTY = 0.1

# point deduction for memory overuse, percentage
MEMORY_OVERUSED_PENALTY = 0.1

# point deduction for file misuse, percentage
FILE_OPEN_PENALTY = 0.1

# These two variables represent the header file type.h
TYPE_H_EXISTS   = False
TYPE_H_FILENAME = "type.h"
TYPE_H_CONTENT  = """
"""

# Timeout in seconds
TIMEOUT_IN_SECONDS = 3

# CONFIGURATION CODE END

def fillTestParameters ( testMarks, testInputs, testCodes, expectedTestResults ):
    numberOfTests = 0
    testMark = float ( """1.000""" )
    testInput = """Vlada, popravka slica, 0, 07.05., 1
Vida, bluza, 1, 10.05., 4
Dalija, suknja, 0, 10.05., 3
Isak, skracenje pantalona, 0, 06.05., 3

09.05.
"""
    testCode = """"""
    expectedTestResult = """Isak, skracenje pantalona, 0, 06.05., 3
Dalija, suknja, 0, 10.05., 3
Vida, bluza, 1, 10.05., 4
Vlada, popravka slica, 0, 07.05., 1
Vlada, popravka slica, 0, 07.05., 1
Isak, skracenje pantalona, 0, 06.05., 3
"""

    testMarks.append ( testMark )
    testInputs.append ( testInput )
    testCodes.append ( testCode )
    expectedTestResults.append ( expectedTestResult )
    numberOfTests = numberOfTests + 1
    testMark = float ( """1.000""" )
    testInput = """Nebojsa, pantalone, 0, 26.05., 5
Nemanja, skracenje rukava, 1, 11.06., 3
Marta, haljina, 0, 25.06., 10
Petra, haljina, 0, 15.06., 7

01.07.
"""
    testCode = """"""
    expectedTestResult = """Petra, haljina, 0, 15.06., 7
Marta, haljina, 0, 25.06., 10
Nemanja, skracenje rukava, 1, 11.06., 3
Nebojsa, pantalone, 0, 26.05., 5
Nebojsa, pantalone, 0, 26.05., 5
Petra, haljina, 0, 15.06., 7
"""

    testMarks.append ( testMark )
    testInputs.append ( testInput )
    testCodes.append ( testCode )
    expectedTestResults.append ( expectedTestResult )
    numberOfTests = numberOfTests + 1
    testMark = float ( """1.000""" )
    testInput = """Petra, haljina, 0, 25.05., 7
Petra, suknja, 0, 25.05., 7

01.06.
"""
    testCode = """"""
    expectedTestResult = """Petra, suknja, 0, 25.05., 7
Petra, haljina, 0, 25.05., 7
Petra, suknja, 0, 25.05., 7
Petra, haljina, 0, 25.05., 7
"""

    testMarks.append ( testMark )
    testInputs.append ( testInput )
    testCodes.append ( testCode )
    expectedTestResults.append ( expectedTestResult )
    numberOfTests = numberOfTests + 1
    return  numberOfTests

def commentRemover ( code ):
    def replacer ( match ):
        s = match.group ( 0 )
        if s.startswith ( '/' ):
            return "\n" * s.count ( "\n" )
        else:
            return s

    pattern = re.compile (
        r'//.*?$|/\*.*?\*/|\'(?:\\.|[^\\\'])*\'|"(?:\\.|[^\\"])*"',
        re.DOTALL | re.MULTILINE
    )
    return re.sub ( pattern, replacer, code )

def findBlockEnd ( start, code ):
    level = 1
    i     = start + 1
    while ( level != 0 ):
        if ( code[i] == "{" ):
            level = level + 1
        elif ( code[i] == "}" ):
            level = level - 1
        i = i + 1
    return i

def resourceCheckAddins ( code, pattern, checkFunction ):
    found = re.search (
        pattern = pattern,
        string  = code
    )

    if ( not found ):
        return ( code, False )

    code = re.sub (
        pattern = pattern,
        repl    = r"m_\1",
        string  = code
    )

    main = re.search (
        pattern = "(void|int)\s*main\s*\(.*\)\s*{",
        string  = code
    )

    mainStart = main.end ( ) - 1
    mainEnd   = findBlockEnd ( mainStart, code )
    mainCode  = code[mainStart : mainEnd]

    returnFound = re.search (
        pattern = "return",
        string  = mainCode
    )

    if ( returnFound ):
        mainCode = re.sub (
            pattern = "return(.*);",
            repl    = "{ " + checkFunction + r"return \1; }",
            string  = mainCode
        )
    else:
        length   = len ( mainCode )
        mainCode = mainCode[:length - 1] + "\n" + checkFunction + "\n" + mainCode[length - 1:]

    code = code[:mainStart] + mainCode + code[mainEnd:]
    return ( code, True )

def memoryCheckAddins ( code, memoryLeakMessage, memoryOverusedMessage, maximumMemorySize, memoryAllocationFailureChance, memoryAllocationFailureMessage ):
    MEMORY_CHECK_PATTERN                          = "((c|m|re)alloc|free)"
    MEMORY_CHECK_FUNCTION                         = "memoryCheck ( " + maximumMemorySize + " );"
    MEMORY_LEAK_MESSAGE_PLACEHOLDER               = "<MEMORY_LEAK_MESSAGE>"
    MEMORY_OVERUSED_MESSAGE_PLACEHOLDER           = "<MEMORY_OVERUSED_MESSAGE>"
    MEMORY_ALLOCATION_FAILURE_CHANCE_PLACEHOLDER  = "<MEMORY_ALLOCATION_FAILURE_CHANCE_PLACEHOLDER>"
    MEMORY_ALLOCATION_FAILURE_MESSAGE_PLACEHOLDER = "<MEMORY_ALLOCATION_FAILURE_MESSAGE_PLACEHOLDER>"

    memoryCheckCode = r"""#include <stdlib.h>
#include <stdio.h>

typedef struct allocationNode {
	void *address;
	size_t size;
	struct allocationNode *next;
} AllocationNode;

AllocationNode *head = NULL,
			   *tail = NULL;

size_t totalSize = 0;
double memoryAllocationFailureChance = <MEMORY_ALLOCATION_FAILURE_CHANCE_PLACEHOLDER>; 

void addNewAllocationNode ( void *address, size_t size ) {
	AllocationNode *newNode = ( AllocationNode* ) malloc ( sizeof ( AllocationNode ) );  

	newNode->address = address;
	newNode->size    = size;
	newNode->next	 = NULL;

	if ( head == NULL ) {
		head = tail = newNode;
	} else {
		tail->next = newNode;
		tail       = newNode;
	}
	
	totalSize += size;
}

int updateAllocationNode ( void *oldAddress, void *newAddress, size_t newSize ) {
    int updated = 0;
	AllocationNode *current = head;

	while ( current != NULL ) {
		if ( current->address == oldAddress ) {
			break;
		} else {
			current = current->next;
		}
	}

	if ( current != NULL ) {
		totalSize        += newSize - current->size;
		current->address = newAddress;
		current->size    = newSize;
		updated          = 1;
	}
    
    return updated;
}

int amIMemoryLucky ( ) {
    double randomValue = ( double ) rand ( ) / RAND_MAX;

    if ( randomValue < memoryAllocationFailureChance ) { 
        printf ( "\n<MEMORY_ALLOCATION_FAILURE_MESSAGE_PLACEHOLDER>" );
        return 0;
    } else {
        return 1;
    }
}

void *m_malloc ( size_t size ) {
    if ( amIMemoryLucky ( ) == 0 ) {
        return NULL;
    }
	void *p = malloc ( size );

	if ( p != NULL ) {
		addNewAllocationNode ( p, size );
	}

	return p;
}

void *m_calloc ( size_t numberOfItems, size_t size ) { 
	if ( amIMemoryLucky ( ) == 0 ) {
        return NULL;
    }
    void *p = calloc ( numberOfItems, size );

	if ( p != NULL ) {
		addNewAllocationNode ( p, numberOfItems * size );
	}

	return p;
}

void *m_realloc ( void *address, size_t newSize ) {
	if ( amIMemoryLucky ( ) == 0 ) {
        return NULL;
    }
    void *p = realloc ( address, newSize );

	if ( p != NULL ) {
		if ( updateAllocationNode ( address, p, newSize ) == 0 ) {
		    addNewAllocationNode ( p, newSize );
		}
	}

	return p;
}

void m_free ( void *address ) {
	AllocationNode *current  = head,
				   *previous = NULL;

	while ( current != NULL ) {
		if ( current->address == address ) {
			AllocationNode *old = current;
			current             = current->next;

			if ( previous == NULL ) {
				head = current;
			} else {
				if ( old == tail ) {
					tail = previous;
				}

				previous->next = current;
			}

			free ( old );
		} else {
			previous = current;
			current  = current->next;
		}
	}
}

void memoryCheck ( size_t maximumSize ) {
    int memoryLeak = 0;
    
	if ( totalSize > maximumSize ) {
		printf ( "\n<MEMORY_OVERUSED_MESSAGE>" );
	}
	
	if ( head != NULL ) {
		while ( head != NULL ) {
			AllocationNode *old = head;

			if ( head->size != 0 ) {
			    memoryLeak = 1;
			}
			
			head = head->next;

			free ( old );
		}
	}
	
	if ( memoryLeak == 1 ) {
        printf ( "\n<MEMORY_LEAK_MESSAGE>" );
	}
}
    """

    ( code, changed ) = resourceCheckAddins (
        code          = code,
        pattern       = MEMORY_CHECK_PATTERN,
        checkFunction = MEMORY_CHECK_FUNCTION
    )

    if ( changed ):
        memoryCheckCode = re.sub (
            pattern = MEMORY_LEAK_MESSAGE_PLACEHOLDER,
            repl    = memoryLeakMessage,
            string  = memoryCheckCode
        )
        memoryCheckCode = re.sub (
            pattern = MEMORY_OVERUSED_MESSAGE_PLACEHOLDER,
            repl    = memoryOverusedMessage,
            string  = memoryCheckCode
        )

        memoryCheckCode = re.sub (
                pattern = MEMORY_ALLOCATION_FAILURE_CHANCE_PLACEHOLDER,
                repl    = memoryAllocationFailureChance,
                string  = memoryCheckCode
        )

        memoryCheckCode = re.sub (
                pattern = MEMORY_ALLOCATION_FAILURE_MESSAGE_PLACEHOLDER,
                repl    = memoryAllocationFailureMessage,
                string  = memoryCheckCode
        )

        code = memoryCheckCode + "\n" + code

    return code

def fileCheckAddins ( code, fileOpenMessage, fileOpenFailureChance, fileOpenFailureMessage ):
    FILE_CHECK_PATTERN                    = "(f(open|close))"
    FILE_CHECK_FUNCTION                   = "fileOpenCheck ( );"
    FILE_OPEN_MESSAGE_PLACEHOLDER         = "<FILE_OPEN_MESSAGE_PLACEHOLDER>"
    FILE_OPEN_FAILURE_CHANCE_PLACEHOLDER  = "<FILE_OPEN_FAILURE_CHANCE_PLACEHOLDER>"
    FILE_OPEN_FAILURE_MESSAGE_PLACEHOLDER = "<FILE_OPEN_FAILURE_MESSAGE_PLACEHOLDER>"

    fileCheckCode = r"""#include <stdio.h>
#include <stdlib.h>
#pragma pack(1)

typedef struct fileNode {
    FILE *file;
    struct fileNode *next;
} FileNode;

typedef struct fileNodeList {
    FileNode *head, *last;
} FileNodeList;

FileNodeList fileList = { NULL, NULL };

double fileOpenFailureChance = <FILE_OPEN_FAILURE_CHANCE_PLACEHOLDER>; 

void addFile ( FILE *file ) {
    FileNode *node = ( FileNode* ) malloc ( sizeof ( FileNode ) );
    
    if ( node == NULL ) {
        exit ( 1 );
    }
    
    node->file = file;
    node->next = NULL;
    
    if ( fileList.head == NULL ) {
        fileList.head = node;
    } else {
        fileList.last->next = node;
    }
    
    fileList.last = node;
}

void removeFile ( FILE *file ) {
    FileNode *current = fileList.head, *previous = NULL;
    
    while ( current != NULL ) {
        if ( current->file == file ) {
            FileNode *old = current;
            
            current = current->next;
            
            if ( previous == NULL ) {
                fileList.head = current;
            } else {
                previous->next = current;
                if ( current == NULL ) {
                    fileList.last = previous;
                }
            }
            
            free ( old );
        } else {
            previous = current;
            current = current->next;
        }
    }
}

int amIFileLucky ( ) {
    double randomValue = ( double ) rand ( ) / RAND_MAX;

    if ( randomValue < fileOpenFailureChance ) { 
        printf ( "\n<FILE_OPEN_FAILURE_MESSAGE_PLACEHOLDER>" );
        return 0;
    } else {
        return 1;
    }
}


FILE* m_fopen ( const char *filename, const char *mode ) {
    if ( amIFileLucky ( ) == 0 ) {
        return NULL;
    }
    FILE *file = fopen ( filename, mode );
    
    if ( file != NULL ) {
        addFile ( file );
    }
    
    return file;
}

int m_fclose ( FILE *file ) {
    removeFile ( file );
    return fclose ( file );
}

void fileOpenCheck ( ) {
    int fileOpen = 0;
   
    if ( fileList.head != NULL ) {
        fileOpen = 1;
        
        FileNode *current = fileList.head;
    
        while ( current != NULL ) {
            FileNode *old = current;
            
            current = current->next;
            
            free ( old );
        }
    }
    
    if ( fileOpen == 1 ) {
        printf ( "\n<FILE_OPEN_MESSAGE_PLACEHOLDER>" );
    }
}
    """

    ( code, changed ) = resourceCheckAddins (
        code          = code,
        pattern       = FILE_CHECK_PATTERN,
        checkFunction = FILE_CHECK_FUNCTION
    )

    if ( changed ):
        fileCheckCode = re.sub (
            pattern = FILE_OPEN_MESSAGE_PLACEHOLDER,
            repl    = fileOpenMessage,
            string  = fileCheckCode
        )

        fileCheckCode = re.sub (
                pattern = FILE_OPEN_FAILURE_CHANCE_PLACEHOLDER,
                repl    = fileOpenFailureChance,
                string  = fileCheckCode
        )

        fileCheckCode = re.sub (
                pattern = FILE_OPEN_FAILURE_MESSAGE_PLACEHOLDER,
                repl    = fileOpenFailureMessage,
                string  = fileCheckCode
        )

        code = fileCheckCode + "\n" + code

    return code

def compile ( code, flags, outputFileName ):
    FILE_NAME = "program.c"
    isCorrect = True

    with open ( FILE_NAME, "w" ) as file:
        file.write ( code )

    COMPILE_COMMAND = ( "gcc " + FILE_NAME + " -o " + outputFileName + " " + " ".join ( flags ) ).split ( )

    try:
        subprocess.check_output (
            args               = COMPILE_COMMAND,
            stderr             = subprocess.STDOUT,
            universal_newlines = True
        )
    except subprocess.CalledProcessError as e:
        data = { }
        data['fraction'] = 0.
        data['testresults'] = []
        data['testresults'].append ( ["Compilation error"] )
        data['testresults'].append ( [ e.output ] )
        print ( json.dumps ( data ) )
        isCorrect = False

    os.remove ( FILE_NAME )

    return isCorrect

def checkSyntax ( code, flags ):
    flags = flags + ["-c"]

    outputFileName = "code.o"

    isCorrect = compile (
        code           = code,
        flags          = flags,
        outputFileName = outputFileName
    )

    if ( isCorrect ):
        os.remove ( outputFileName )

    return isCorrect

def checkAdditionalRequirements ( code, requiredCode, forbiddenCode ):
    isCorrect = True
    messages  = []

    for item in requiredCode:
        result = re.findall (
            pattern = item[0],
            string  = code,
            flags   = item[1],
        )
        if ( len ( result ) == 0 ):
            isCorrect = False
            messages.append ( item[2] )

    for item in forbiddenCode:
        result = re.findall (
            pattern = item[0],
            string  = code,
            flags   = item[1]
        )
        if (len ( result ) != 0):
            isCorrect = False
            messages.append ( item[2] )

    if ( not isCorrect ):
        data = { }
        data['fraction'] = 0.
        data['testresults'] = []
        data['testresults'].append ( ["Additional requirements error"] )
        data['testresults'].append ( [ "\n".join ( messages ) ] )
        print ( json.dumps ( data ) )

    return isCorrect

# this function separates the input/output text into sections
def separateInSections ( text ):
    # this separates all directives into tuples with three elements, begin directive, content and end directive
    directiveTuples = re.findall (
        pattern = "//(.*)BEGIN\n([\s\S]*?)\n//(.*)END",
        string  = text
    )

    result = []
    for item in directiveTuples:
        beginDirective = item[0].strip ( )
        content        = item[1]
        endDirective   = item[2].strip ( )

        # remove all unnecessary white spaces in directives
        beginDirective = re.sub (
            pattern = "\s+",
            string  = beginDirective,
            repl    = " "
        )

        endDirective = re.sub (
            pattern = "\s+",
            string  = endDirective,
            repl    = " "
        )

        if ( beginDirective != endDirective ):
            raise Exception ( "Directive pair doesn't match: " + beginDirective + ", " + endDirective )

        result.append ( (beginDirective, content) )

    return result

# The data is is split by // directives, each directive has a start and an end directive,
# the content of the directive is every line in between the end and start, possible options are:
# 1) // STDIN, represents the standard input
# 2) // COMMAND_LINE_PARAMETERS parameter0 parameter1 ...., used to indicate command line parameters for the program, parameters are separated with a single white space
# 2) // MAXIMUM_MEMORY_SIZE expression, limits the memory use, size is expected to be a valid C expression
# 3) // TEXT_FILE fileName, represents a text file named fileName, the content of the file is every line after this until the next directive
# 4) // BINARY_FILE fileName, represents a binary file named fileName, before the content a format must specified as a list of types, each type is separated by a coma
#    Valid types are:
#       - char
#       - signed char
#       - unsigned char
#       - short
#       - unsigned short
#       - int
#       - unsigned int
#       - long
#       - unsigned long
#       - long long
#       - unsigned long long
#       - float
#       - double
#       - string[length], length is the length of the string including the null character
#   The data is specified in the following lines, each value is separated by a coma

def prepareInputData ( input ):
    STDIN                         = "STDIN"
    COMMAND_LINE_PARAMETERS       = "COMMAND_LINE_PARAMETERS"
    MAXIMUM_MEMORY_SIZE_DIRECTIVE = "MAXIMUM_MEMORY_SIZE"
    TEXT_FILE_DIRECTIVE           = "TEXT_FILE"
    BINARY_FILE_DIRECTIVE         = "BINARY_FILE"

    sections = separateInSections ( input )
    if ( len ( sections ) == 0 ):
        sections = [
                ( STDIN, input )
        ]

    stdin                 = ""
    commandLineParameters = ""
    maximumMemorySize     = "~0"
    files                 = []

    for section in sections:
        if ( STDIN in section[0] ):
            stdin = section[1]
        elif ( COMMAND_LINE_PARAMETERS in section[0] ):
            commandLineParameters = section[1].strip ( )
        elif ( MAXIMUM_MEMORY_SIZE_DIRECTIVE in section[0] ):
            maximumMemorySize = section[1].strip ( )
        elif ( TEXT_FILE_DIRECTIVE in section[0] ):
            fileName = section[0][len ( TEXT_FILE_DIRECTIVE ):].strip ( )
            content  = section[1]

            with open ( fileName, "w" ) as file:
                file.write ( content )

            files.append ( fileName )
        elif ( BINARY_FILE_DIRECTIVE in section[0] ):
            fileName = section[0][len ( BINARY_FILE_DIRECTIVE ):].strip ( )
            lines    = section[1].split ( "\n" )

            cTypes     = [
                "char",
                "signed char",
                "unsigned char",
                "short",
                "unsigned short",
                "int",
                "unsigned int",
                "long",
                "unsigned long",
                "long long",
                "unsigned long long",
                "float",
                "double",
                "string"
            ]
            formats    = [
                lambda value: "c",
                lambda value: "b",
                lambda value: "B",
                lambda value: "h",
                lambda value: "H",
                lambda value: "i",
                lambda value: "I",
                lambda value: "l",
                lambda value: "L",
                lambda value: "q",
                lambda value: "Q",
                lambda value: "f",
                lambda value: "d",
                lambda value: value[value.find ( "[" ) + 1: value.find ( "]" )].strip ( ) + "s"
            ]
            converters = [
                lambda value: value[0].encode ( "ascii" ),
                lambda value: int ( value ),
                lambda value: int ( value ),
                lambda value: int ( value ),
                lambda value: int ( value ),
                lambda value: int ( value ),
                lambda value: int ( value ),
                lambda value: int ( value ),
                lambda value: int ( value ),
                lambda value: int ( value ),
                lambda value: int ( value ),
                lambda value: float ( value ),
                lambda value: float ( value ),
                lambda value: value.encode ( "ascii" ),
            ]

            structFormat = "="
            types   = [type.strip ( ) for type in lines[0].split ( "," )]
            indices = []
            for type in types:
                try:
                    searchType = type
                    # check if string is the type, if so eliminate the length
                    if ( cTypes[len ( cTypes ) - 1] in type ):
                        searchType = searchType[:type.index("[")].strip ( )
                    index = cTypes.index ( searchType )
                    structFormat = structFormat + formats[index] ( type )
                    indices.append ( index )
                except ValueError:
                    raise Exception ( "Type " + type + " not supported!" )

            with ( open ( fileName, "wb" ) ) as file:
                counter = 0
                for line in lines[1:]:
                    counter   += 1
                    textValues = [value.strip ( ) for value in line.split ( "," )]
                    if ( len ( textValues ) != len ( indices ) ):
                        raise Exception ( "Number of values and types doesn't match for binary file: " + fileName + ", line " + str ( counter ) + ", text: " + line )
                    else:
                        values = [converters[i] ( value ) for i, value in zip ( indices, textValues )]
                        file.write ( struct.pack ( structFormat, *values ) )
            files.append ( fileName )
        else:
            raise Exception ( "Unknown directive: " + section[0] )

    return ( stdin, commandLineParameters, maximumMemorySize, files )

def compare ( stdout, output, linePoints ):
    STDOUT      = "STDOUT"
    TEXT_FILE   = "TEXT_FILE"
    BINARY_FILE = "BINARY_FILE"
    BEGIN       = "BEGIN"
    END         = "END"
    LINE_START  = "//"

    onlyStdout = False

    sections = separateInSections ( output )
    if ( len ( sections ) == 0 ):
        sections = [
                ( STDOUT, output )
        ]
        onlyStdout = True

    files          = []
    gotColumn      = ""
    expectedColumn = ""
    commentComlumn = ""
    max            = 0
    points         = []

    for section in sections:
        expected          = section[1].split ( "\n" )
        got               = [ ]
        fileNotFound      = False
        beginDirective    = None
        endDirective      = None
        sectionLinePoints = linePoints[sections.index ( section ) % len ( linePoints )][1]
        sectionPoints     = linePoints[sections.index ( section ) % len ( linePoints )][0]
        max              += sectionPoints

        if ( STDOUT in section[0] ):
            got            = stdout.split ( "\n" )
            beginDirective = " ".join ( [LINE_START, STDOUT, BEGIN] )
            endDirective   = " ".join ( [LINE_START, STDOUT, END] )
        elif ( TEXT_FILE in section[0] ):
            fileName       = section[0][len ( TEXT_FILE ):].strip ( )
            beginDirective = " ".join ( [LINE_START, TEXT_FILE, fileName, BEGIN] )
            endDirective   = " ".join ( [LINE_START, TEXT_FILE, fileName, END] )
            try:
                with open ( fileName, "r" ) as file:
                    got = file.read ( ).split ( "\n" )
                files.append ( fileName )
            except FileNotFoundError:
                fileNotFound = True
        elif ( BINARY_FILE in section[0] ):
            fileName       = section[0][len ( BINARY_FILE ):].strip ( )
            beginDirective = " ".join ( [LINE_START, BINARY_FILE, fileName, BEGIN] )
            endDirective   = " ".join ( [LINE_START, BINARY_FILE, fileName, END] )

            cTypes     = [
                "char",
                "signed char",
                "unsigned char",
                "short",
                "unsigned short",
                "int",
                "unsigned int",
                "long",
                "unsigned long",
                "long long",
                "unsigned long long",
                "float",
                "double",
                "string"
            ]
            formats    = [
                lambda value: "c",
                lambda value: "b",
                lambda value: "B",
                lambda value: "h",
                lambda value: "H",
                lambda value: "i",
                lambda value: "I",
                lambda value: "l",
                lambda value: "L",
                lambda value: "q",
                lambda value: "Q",
                lambda value: "f",
                lambda value: "d",
                lambda value: value[value.find ( "[" ) + 1: value.find ( "]" )].strip ( ) + "s"
            ]
            converters = [
                lambda value: str ( value.decode ( "ascii" ).rstrip ( "\x00" ) ),
                lambda value: str ( int ( value ) ),
                lambda value: str ( int ( value ) ),
                lambda value: str ( int ( value ) ),
                lambda value: str ( int ( value ) ),
                lambda value: str ( int ( value ) ),
                lambda value: str ( int ( value ) ),
                lambda value: str ( int ( value ) ),
                lambda value: str ( int ( value ) ),
                lambda value: str ( int ( value ) ),
                lambda value: str ( int ( value ) ),
                lambda value: str ( float ( value ) ),
                lambda value: str ( float ( value ) ),
                lambda value: str ( value.decode ( "ascii" ).rstrip ( "\x00" ) ),
            ]

            lines = section[1].split ( "\n" )

            structFormat = "="

            types = [type.strip ( ) for type in lines[0].split ( "," )]

            beginDirective = beginDirective + "\n" + lines[0]
            expected = lines[1:]

            indices = [ ]
            for type in types:
                try:
                    searchType = type
                    # check if string is the type, if so eliminate the length
                    if ( cTypes[len ( cTypes ) - 1] in type ):
                        searchType = searchType[:type.index("[")].strip ( )
                    index = cTypes.index ( searchType )
                    structFormat = structFormat + formats[index] ( type )

                    indices.append ( index )
                except ValueError:
                    raise Exception ( "Type " + type + " not supported!" )

            try:
                with ( open ( fileName, "rb" ) ) as file:
                    got = [ ]
                    for tuple in struct.iter_unpack ( structFormat, file.read ( ) ):
                        values = [converters[i] ( item ) for i, item in zip ( indices, tuple )]
                        got.append ( ", ".join ( values ) )
                    files.append ( fileName )
            except FileNotFoundError:
                fileNotFound = True
        else:
            raise Exception ( "Unsupported directive: " + section[0] )

        sectionMark = 0
        sectionMax  = 0

        comment = [ ]

        if ( fileNotFound ):
            comment = [ "FILE NOT FOUND" ] * len ( expected )
        elif len ( got ) > len ( expected ):
            comment = [ "NUMBER OF LINES GREATER THAN EXPECTED" ] * len ( got )
        else:
            for i in range ( len ( expected ) ):
                sectionMax += sectionLinePoints[i % len ( sectionLinePoints )]
                if i < len ( got ):
                    if got[i] == expected[i]:
                        sectionMark += sectionLinePoints[i % len ( sectionLinePoints )]
                        comment.append ( "Line {} right".format ( i ) )
                    else:
                        comment.append ( "Line {} wrong".format ( i ) )
                else:
                    comment.append ( "Line {} missing".format ( i ) )

        if ( onlyStdout == True ):
            expectedColumn = "\n".join ( expected )
            gotColumn      = "\n".join ( got )
            commentComlumn = "\n".join ( comment )
        else:
            beginDirectiveLength = len ( beginDirective.split ( "\n" ) )

            lengthDifference = len ( got ) - len ( expected )
            gotPadding = ""
            expectedPadding = ""
            if ( lengthDifference > 0 ):
                expectedPadding = "\n" * lengthDifference
            elif ( lengthDifference < 0 ):
                gotPadding = "\n" * -lengthDifference

            expected = [ "" ] + expected
            got = [ "" ] + got
            expectedColumn += beginDirective + "\n".join ( expected ) + "\n" + endDirective + "\n" + expectedPadding
            gotColumn      += beginDirective + "\n".join ( got ) + "\n" + endDirective + "\n" + gotPadding
            commentComlumn += "\n" * beginDirectiveLength + "\n".join ( comment ) + "\n\n"

        sectionTotal = 0
        if ( sectionMax != 0 ):
            sectionTotal = sectionMark / sectionMax * sectionPoints
        points.append ( sectionTotal )


    total = sum ( points ) / max
    return ( expectedColumn, gotColumn, commentComlumn, total, files )

def checkLastLineAndPop ( lines, text ):
    if ( lines[len ( lines ) - 1] == text):
        lines.pop ( len ( lines ) - 1 )
        return 1
    else:
        return 0


studentAnswer = """#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *program = fopen(\"prog.python3\", \"rb\");
    fseek(program, 0, SEEK_END);
    long size = ftell(program);
    fseek(program, 0, SEEK_SET);
    char *ceo_program = malloc((size + 1) * sizeof(char));
    fread(ceo_program, 1, size, program);
    fclose(program);
    *(ceo_program + size) = '\\0';
    printf(\"%s\", ceo_program);
    return 0;
}"""

if ( checkSyntax ( studentAnswer, FLAGS ) and checkAdditionalRequirements ( studentAnswer, REQUIRED_CODE, FORBIDDEN_CODE )):
    MEMORY_LEAK_MESSAGE               = "MEMORY|LEAK"
    MEMORY_OVERUSED_MESSAGE           = "MEMORY|OVERUSED"
    MEMORY_ALLOCATION_FAILURE_MESSAGE = "MEMORY|ALLOCATION|FAILURE"
    FILE_OPEN_MESSAGE                 = "FILE|OPEN"
    FILE_OPEN_FAILURE_MESSAGE         = "FILE|OPEN|FAILURE"
    OUTPUT_FILE_NAME                  = "program"
    RUN                               = "./program"

    studentAnswer = PREDEFINED_CODE + studentAnswer
    isCorrect = True

    testMarks           = [ ]
    testInputs          = [ ]
    testCodes           = [ ]
    expectedTestResults = [ ]
    numberOfTests       = fillTestParameters ( testMarks, testInputs, testCodes, expectedTestResults )

    testCodeCells       = [ ]
    inputCells          = [ ]
    expectedResultCells = [ ]
    gotCells            = [ ]
    commentCells        = [ ]
    testScoreCells      = [ ]
    testMarkCells       = [ ]
    testNumber          = 0
    fileOpenCells       = [ ]
    memoryOverusedCells = [ ]
    memoryLeakCells     = [ ]

    if ( TYPE_H_EXISTS ):
        with open ( TYPE_H_FILENAME, "w" ) as file:
            file.write ( TYPE_H_CONTENT )

    for i in range ( numberOfTests ):
        testMark           = testMarks[i]
        input              = testInputs[i]
        testCode           = testCodes[i]
        expectedTestResult = expectedTestResults[i]

        runtimeError  = False
        testTotal     = 0
        commentColumn = ""

        fileOpenCells.append ( 0 )
        memoryOverusedCells.append ( 0 )
        memoryLeakCells.append ( 0 )

        # prepare test data
        ( stdin, commandLineParameters, maximumMemorySize, files ) = prepareInputData ( input )

        # preprocess student answer with provided code
        code = studentAnswer + "\n" + testCode
        code = commentRemover (
            code = code
        )
        code = memoryCheckAddins (
            code                           = code,
            memoryLeakMessage              = MEMORY_LEAK_MESSAGE,
            memoryOverusedMessage          = MEMORY_OVERUSED_MESSAGE,
            maximumMemorySize              = maximumMemorySize,
            memoryAllocationFailureChance  = str ( MEMORY_ALLOCATION_FAILURE_CHANCE ),
            memoryAllocationFailureMessage = MEMORY_ALLOCATION_FAILURE_MESSAGE
        )
        code = fileCheckAddins (
            code                   = code,
            fileOpenMessage        = FILE_OPEN_MESSAGE,
            fileOpenFailureChance  = str ( FILE_OPEN_FAILURE_CHANCE ),
            fileOpenFailureMessage = FILE_OPEN_FAILURE_MESSAGE
        )

        isCorrect = compile (
            code           = code,
            flags          = FLAGS,
            outputFileName = OUTPUT_FILE_NAME
        )
        if ( not isCorrect ):
            break
        else:
            expectedColumn = ""
            gotColumn      = ""
            commentColumn  = ""

            try:
                stdout = subprocess.check_output (
                    args               = ( RUN + " " + commandLineParameters ).strip ( ),
                    input              = stdin,
                    stderr             = subprocess.STDOUT,
                    universal_newlines = True,
                    timeout            = TIMEOUT_IN_SECONDS
                )

                # first check for resource misuse
                stdoutLines                     = stdout.split ( "\n" )
                fileOpenCells[testNumber]       = checkLastLineAndPop( stdoutLines, FILE_OPEN_MESSAGE )
                memoryLeakCells[testNumber]     = checkLastLineAndPop ( stdoutLines, MEMORY_LEAK_MESSAGE )
                memoryOverusedCells[testNumber] = checkLastLineAndPop ( stdoutLines, MEMORY_OVERUSED_MESSAGE )
                stdout                          = "\n".join ( stdoutLines )

                ( expectedColumn, gotColumn, commentColumn, testTotal, createdFiles ) = compare ( stdout, expectedTestResult, TEST_POINTS )
                files.extend ( createdFiles )
            except subprocess.CalledProcessError as e:
                eStdoutLines = e.stdout.split ( "\n" )
                if ( e.returncode == MEMORY_ALLOCATION_FAILURE_RETURN_CODE and checkLastLineAndPop ( eStdoutLines, MEMORY_ALLOCATION_FAILURE_MESSAGE ) == 1 ):
                    testTotal      = 1
                    expectedColumn = ""
                    gotColumn      = ""
                    commentColumn  = "MEMORY ALLOCATION FAILURE HANDLED"
                elif ( e.returncode == FILE_OPEN_FAILURE_RETURN_CODE and checkLastLineAndPop ( eStdoutLines, FILE_OPEN_FAILURE_MESSAGE ) == 1 ):
                    testTotal      = 1
                    expectedColumn = ""
                    gotColumn      = ""
                    commentColumn  = "FILE OPEN FAILURE HANDLED"
                else:
                    testTotal      = 0
                    expectedColumn = expectedTestResult
                    gotColumn      = "RUNTIME ERROR"
                    commentColumn  = "RUNTIME ERROR"
                    runtimeError   = True
            except UnicodeDecodeError as e:
                testTotal      = 0
                expectedColumn = expectedTestResult
                gotColumn      = "RUNTIME ERROR"
                commentColumn  = "RUNTIME ERROR"
                runtimeError   = True
            except subprocess.TimeoutExpired as e:
                testTotal      = 0
                expectedColumn = expectedTestResult
                gotColumn      = "TIMEOUT ERROR"
                commentColumn  = "TIMEOUT ERROR"
                runtimeError   = True
            finally:
                os.remove ( OUTPUT_FILE_NAME )
                for file in files:
                    os.remove ( file )

            # write to arrays
            testCodeCells.append ( testCode )
            inputCells.append ( input )
            expectedResultCells.append ( expectedColumn )
            gotCells.append ( gotColumn )
            commentCells.append ( commentColumn )

            testTotal = testTotal * testMark
            memoryLeakReduction = MEMORY_LEAK_PENALTY * testTotal if memoryLeakCells[testNumber] == 1 else 0
            memoryOverusedReduction = MEMORY_OVERUSED_PENALTY * testTotal if memoryOverusedCells[testNumber] == 1 else 0
            fileOPenReduction = FILE_OPEN_PENALTY * testTotal if fileOpenCells[testNumber] == 1 else 0
            testTotal -= memoryLeakReduction + memoryOverusedReduction + fileOPenReduction

            testScoreCells.append ( round ( testTotal, 2 ) )
            testMarkCells.append ( testMark )

            testNumber = testNumber + 1

    if (TYPE_H_EXISTS):
        os.remove ( TYPE_H_FILENAME )

    # write result json
    if ( isCorrect ):
        data = { }
        data['testresults'] = []

        memoryLeakPresent     = sum ( memoryLeakCells ) != 0
        memoryOverusedPresent = sum ( memoryOverusedCells ) != 0
        fileOpenPresent       = sum ( fileOpenCells ) != 0

        headers = ["Test code", "Input", "Expected", "Got" ]
        if ( memoryLeakPresent ):
            headers.append ( "Memory leak" )
        if ( memoryOverusedPresent ):
            headers.append ( "Memory overused" )
        if ( fileOpenPresent ):
            headers.append ( "File open" )
        headers.extend ( [ "Comment", "Score", "iscorrect", "ishidden" ] )

        data['testresults'].append ( headers )

        for i in range ( numberOfTests ):
            row = [ testCodeCells[i], inputCells[i], expectedResultCells[i], gotCells[i] ]
            if ( memoryLeakPresent ):
               row.append ( "YES" if memoryLeakCells[i] == 1 else "NO" )
            if ( memoryOverusedPresent ):
                row.append ( "YES" if memoryOverusedCells[i] == 1 else "NO" )
            if ( fileOpenPresent ):
                row.append ( "YES" if fileOpenCells[i] == 1 else "NO" )

            row.append ( commentCells[i] )
            row.append ( str ( testScoreCells[i] ) + " / " + str ( testMarkCells[i] ) )
            row.append ( 1 if testScoreCells[i] == testMarkCells[i] else 0 )
            row.append ( 1 if i in HIDDEN_TESTS else 0 )

            data['testresults'].append ( row )

        data['fraction'] = sum ( testScoreCells ) / sum ( testMarkCells )
        data['showdifferences'] = 1

        print ( json.dumps ( data ) )
