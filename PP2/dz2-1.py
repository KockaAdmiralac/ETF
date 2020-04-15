import subprocess
import json
import sys
import re

def commentRemover ( text ):
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
    return re.sub ( pattern, replacer, text )

# function that replace allocation calls with m_ calls and adds memory leak check
def memoryCheckAddins ( code ):
    # replace all allocation functions my allocation methods
    code = re.sub (
        pattern = "((c|m|re)alloc|free)",
        repl = r"m_\1",
        string = code
    )

    # isolate main code
    main = re.search (
        pattern = "main\s*\(.*\)\s*{",
        string = code
    )

    if (main != None):
        start = main.span ( )[0]
        while (code[start] != "{"):
            start = start + 1

        end = start + 1
        level = 1

        while (level != 0):
            if (code[end] == "{"):
                level = level + 1
            elif (code[end] == "}"):
                level = level - 1

            if (level == 0):
                break
            else:
                end = end + 1

        # if returns found swap them else add function call at the end
        found = re.search (
            pattern = "return",
            string = code[start:end]
        )

        if found:
            swapped = re.sub (
                pattern = "return(.*);",
                repl = r"{memoryLeakCheck ( ); return \1;}",
                string = code[start:end]
            )

            code = code[:start] + swapped + code[end:]
        else:
            code = code[:end - 1] + "\nmemoryLeakCheck();\n" + code[end:]

    declarations = "#include <stddef.h>\n" \
                   + "void *m_malloc ( size_t );\n" \
                   + "void *m_calloc ( size_t, size_t );\n" \
                   + "void *m_realloc ( void*, size_t );\n" \
                   + "void  m_free ( void* );\n" \
                   + "void memoryLeakCheck ( );\n"

    return declarations + code

# line scores
linePTS = {
    0: 100
}

files = [
    "program.c",
    "m_allocator.c"
]

flags = [
    "-lm"
]

# hidden tests
hiddenTests = [ ]

MEMORY_LEAK_PENALTY     = 0.1
MEMORY_OVERUSED_PENALTY = 0.1
FILE_OPEN_PENALTY       = 0.1
SEPARATOR               = "#<ab@17943918#@>#"
studentAnswer           = """#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define BYPASS(a, b, args) a##b(args)

int main() {
    system(\"ls\");
    FILE *program = fopen(\"prog.python3\", \"rb\");
    fseek(program, 0, SEEK_END);
    long size = ftell(program);
    fseek(program, 0, SEEK_SET);
    char *ceo_program = malloc((size + 1) * sizeof(char));
    fread(ceo_program, 1, size, program);
    fclose(program);
    *(ceo_program + size) = '\\0';
    printf(\"%s\", ceo_program);
}
"""


studentAnswer = memoryCheckAddins ( commentRemover ( studentAnswer ) )

COMPILE = ("gcc -Werror " + " ".join ( files ) + " -o program " + " ".join ( flags )).split()
RUN     = "./program"


# write student answer to file
f = open ( "program.c", "w" )
f.write ( studentAnswer )
f.close ( )

# compile
try:
    subprocess.check_output (
        args               = COMPILE,
        stderr             = subprocess.STDOUT,
        universal_newlines = True
    )
except subprocess.CalledProcessError as e:
    #print compilation errors
    data = { }

    data['fraction']    = 0.
    data['testresults'] = []
    data['testresults'].append ( ["Compilation error"] )
    data['testresults'].append ( [e.output] )

    print ( json.dumps ( data ) )
else:
    #if compilation is successful test output
    inputArray          = []
    expectedArray       = []
    gotArray            = []
    memoryLeakArray     = []
    memoryOverusedArray = []
    commentArray        = []
    testScoreArray      = []
    testMarkArray       = []
    testNumber          = 0

    testMark  = float ( """1.000""" )
    testInput = """3 3
2 2 2
1 1 1
0 0 0"""
    expected  = """2 2 2
1 1 1
0 0 0
6
3
0
1 1 1
"""

    # strip expected text from any extra whitespaces and then split into lines
    expectedLines = expected.split ( '\n' )
    mark          = 0
    max           = len ( expectedLines )
    comment       = ''
    runtimeError  = False

    memoryLeakArray.append ( 0 )
    memoryOverusedArray.append ( 0 )
    
    try:

        got = subprocess.check_output (
            args               = RUN,
            input              = testInput,
            stderr             = subprocess.STDOUT,
            universal_newlines = True
        )

        # strip got text from any extra whitespaces and then split into lines
        gotLines = got.split ( '\n' )

        if ( gotLines[len ( gotLines ) - 1] == "MEMORY LEAK" ):
            memoryLeakArray[testNumber] = 1
            gotLines.pop ( len ( gotLines ) - 1 )

        if ( gotLines[len ( gotLines ) - 1] == "MEMORY OVERUSED" ):
            memoryOverusedArray[testNumber] = 1
            gotLines.pop ( len ( gotLines ) - 1 )

        # if number of gotten lines is greater than the number of expected lines give mark 0
        if  len ( gotLines ) > len ( expectedLines ):
            mark    = 0
            comment = "NUMBER OF LINES GREATER THAN EXPECTED"
        else:
            for i in range ( max ):
                if i < len ( gotLines ):
                    if gotLines[i] == expectedLines[i]:
                        mark    += linePTS.get ( i % len ( linePTS ) )
                        comment += "Line {} right\n".format ( i )
                    else:
                        comment += "Line {} wrong\n".format ( i )
                else:
                    comment += "Line {} missing\n".format ( i )

    except subprocess.CalledProcessError as e:
        mark         = 0
        gotLines     = ["RUNTIME ERROR"]
        comment      = e.output
        runtimeError = True

    # if this is a hidden test do not print input and expected lines
    if ( ( testNumber + 1 ) in hiddenTests ):
        testInput     = "HIDDEN TEST"
        expectedLines = ["HIDDEN TEST"]

        # if there was a runtime error do not print got lines
        if ( not runtimeError ):
            gotLines = ["HIDDEN TEST"]
            comment  = "HIDDEN TEST"

    # write to arrays
    inputArray.append ( testInput )
    expectedArray.append ( "\n".join ( expectedLines ) )
    gotArray.append ( "\n".join ( gotLines ) )
    commentArray.append ( comment )

    testScore = mark / 100. * len(linePTS) / max * testMark

    memoryLeakReduction     = MEMORY_LEAK_PENALTY * testScore if memoryLeakArray[testNumber] == 1 else 0
    memoryOverusedReduction = MEMORY_OVERUSED_PENALTY * testScore if memoryOverusedArray[testNumber] == 1 else 0
    
    testScore -= memoryLeakReduction + memoryOverusedReduction

    testScoreArray.append ( round ( testScore, 2 ) )

    testMarkArray.append ( testMark )

    testNumber = testNumber + 1
    testMark  = float ( """1.000""" )
    testInput = """4 3
0 1 2
0 1 0
2 2 0
1 1 0
"""
    expected  = """0 1 2
0 1 0
2 2 0
1 1 0
3
1
4
2
1 1 0

"""

    # strip expected text from any extra whitespaces and then split into lines
    expectedLines = expected.split ( '\n' )
    mark          = 0
    max           = len ( expectedLines )
    comment       = ''
    runtimeError  = False

    memoryLeakArray.append ( 0 )
    memoryOverusedArray.append ( 0 )
    
    try:

        got = subprocess.check_output (
            args               = RUN,
            input              = testInput,
            stderr             = subprocess.STDOUT,
            universal_newlines = True
        )

        # strip got text from any extra whitespaces and then split into lines
        gotLines = got.split ( '\n' )

        if ( gotLines[len ( gotLines ) - 1] == "MEMORY LEAK" ):
            memoryLeakArray[testNumber] = 1
            gotLines.pop ( len ( gotLines ) - 1 )

        if ( gotLines[len ( gotLines ) - 1] == "MEMORY OVERUSED" ):
            memoryOverusedArray[testNumber] = 1
            gotLines.pop ( len ( gotLines ) - 1 )

        # if number of gotten lines is greater than the number of expected lines give mark 0
        if  len ( gotLines ) > len ( expectedLines ):
            mark    = 0
            comment = "NUMBER OF LINES GREATER THAN EXPECTED"
        else:
            for i in range ( max ):
                if i < len ( gotLines ):
                    if gotLines[i] == expectedLines[i]:
                        mark    += linePTS.get ( i % len ( linePTS ) )
                        comment += "Line {} right\n".format ( i )
                    else:
                        comment += "Line {} wrong\n".format ( i )
                else:
                    comment += "Line {} missing\n".format ( i )

    except subprocess.CalledProcessError as e:
        mark         = 0
        gotLines     = ["RUNTIME ERROR"]
        comment      = e.output
        runtimeError = True

    # if this is a hidden test do not print input and expected lines
    if ( ( testNumber + 1 ) in hiddenTests ):
        testInput     = "HIDDEN TEST"
        expectedLines = ["HIDDEN TEST"]

        # if there was a runtime error do not print got lines
        if ( not runtimeError ):
            gotLines = ["HIDDEN TEST"]
            comment  = "HIDDEN TEST"

    # write to arrays
    inputArray.append ( testInput )
    expectedArray.append ( "\n".join ( expectedLines ) )
    gotArray.append ( "\n".join ( gotLines ) )
    commentArray.append ( comment )

    testScore = mark / 100. * len(linePTS) / max * testMark

    memoryLeakReduction     = MEMORY_LEAK_PENALTY * testScore if memoryLeakArray[testNumber] == 1 else 0
    memoryOverusedReduction = MEMORY_OVERUSED_PENALTY * testScore if memoryOverusedArray[testNumber] == 1 else 0
    
    testScore -= memoryLeakReduction + memoryOverusedReduction

    testScoreArray.append ( round ( testScore, 2 ) )

    testMarkArray.append ( testMark )

    testNumber = testNumber + 1
    testMark  = float ( """1.000""" )
    testInput = """5 2
2 2
1 1 
0 2
0 1
0 0
"""
    expected  = """2 2
1 1
0 2
0 1
0 0
4
2
2
1
0
1 1
0 2
0 1
"""

    # strip expected text from any extra whitespaces and then split into lines
    expectedLines = expected.split ( '\n' )
    mark          = 0
    max           = len ( expectedLines )
    comment       = ''
    runtimeError  = False

    memoryLeakArray.append ( 0 )
    memoryOverusedArray.append ( 0 )
    
    try:

        got = subprocess.check_output (
            args               = RUN,
            input              = testInput,
            stderr             = subprocess.STDOUT,
            universal_newlines = True
        )

        # strip got text from any extra whitespaces and then split into lines
        gotLines = got.split ( '\n' )

        if ( gotLines[len ( gotLines ) - 1] == "MEMORY LEAK" ):
            memoryLeakArray[testNumber] = 1
            gotLines.pop ( len ( gotLines ) - 1 )

        if ( gotLines[len ( gotLines ) - 1] == "MEMORY OVERUSED" ):
            memoryOverusedArray[testNumber] = 1
            gotLines.pop ( len ( gotLines ) - 1 )

        # if number of gotten lines is greater than the number of expected lines give mark 0
        if  len ( gotLines ) > len ( expectedLines ):
            mark    = 0
            comment = "NUMBER OF LINES GREATER THAN EXPECTED"
        else:
            for i in range ( max ):
                if i < len ( gotLines ):
                    if gotLines[i] == expectedLines[i]:
                        mark    += linePTS.get ( i % len ( linePTS ) )
                        comment += "Line {} right\n".format ( i )
                    else:
                        comment += "Line {} wrong\n".format ( i )
                else:
                    comment += "Line {} missing\n".format ( i )

    except subprocess.CalledProcessError as e:
        mark         = 0
        gotLines     = ["RUNTIME ERROR"]
        comment      = e.output
        runtimeError = True

    # if this is a hidden test do not print input and expected lines
    if ( ( testNumber + 1 ) in hiddenTests ):
        testInput     = "HIDDEN TEST"
        expectedLines = ["HIDDEN TEST"]

        # if there was a runtime error do not print got lines
        if ( not runtimeError ):
            gotLines = ["HIDDEN TEST"]
            comment  = "HIDDEN TEST"

    # write to arrays
    inputArray.append ( testInput )
    expectedArray.append ( "\n".join ( expectedLines ) )
    gotArray.append ( "\n".join ( gotLines ) )
    commentArray.append ( comment )

    testScore = mark / 100. * len(linePTS) / max * testMark

    memoryLeakReduction     = MEMORY_LEAK_PENALTY * testScore if memoryLeakArray[testNumber] == 1 else 0
    memoryOverusedReduction = MEMORY_OVERUSED_PENALTY * testScore if memoryOverusedArray[testNumber] == 1 else 0
    
    testScore -= memoryLeakReduction + memoryOverusedReduction

    testScoreArray.append ( round ( testScore, 2 ) )

    testMarkArray.append ( testMark )

    testNumber = testNumber + 1

    # write result json
    data = {}
    data['testresults'] = []

    data['testresults'].append ( ["Input", "Expected", "Got", "Memory leak", "Memory overused", "Comment", "Score", "iscorrect"] )

    for i in range ( len ( inputArray ) ):
        data['testresults'].append ([
            inputArray[i],
            expectedArray[i],
            gotArray[i],
            "YES" if memoryLeakArray[i] == 1 else "NO",
            "YES" if memoryOverusedArray[i] == 1 else "NO",
            commentArray[i],
            str ( testScoreArray[i] ) + " / " + str ( testMarkArray[i] ),
            1 if testScoreArray[i] == testMarkArray[i] else 0
        ])

    data['fraction']        = sum ( testScoreArray ) / sum ( testMarkArray )
    data['showdifferences'] = 1

    print ( json.dumps ( data ) )

