# CSCI 1430 - james_tompkin@brown.edu
#
# Students, hark! 
# Run this script from this directory to create an appropriate zip file to submit to Gradescope.

import os, zipfile

# Function from https://stackoverflow.com/questions/1724693/find-a-file-in-python 
def find(name, path):
    for root, dirs, files in os.walk(path):
        if name in files:
            return os.path.join(root, name)


# Function adapted from https://www.geeksforgeeks.org/working-zip-files-python/
def get_all_file_paths( directory, ext ): 
  
    # Initializing empty file paths list 
    file_paths = []
  
    # Crawling through directory and subdirectories 
    for root, directories, files in os.walk(directory):
        for filename in files:
            if filename.endswith(ext):
                # Join the two strings in order to form the full filepath. 
                filepath = os.path.join(root, filename)
                file_paths.append(filepath) 
  
    # Returning all file paths 
    return file_paths 


def main():

    # Files we wish to include
    # - Everything in 'code'
    # - writeup/writeup.pdf

    # Some of you will end up in a pickle and run this 
    # from the wrong directory.
    # So, let's work out whether we're in the right directory
    # to execute, e.g., one below 'code'
    curdir = os.getcwd()
    (head, tail) = os.path.split( curdir )

    if tail == 'code' or tail == 'data' or tail == 'questions' or tail == 'writeup':
        print( 'Executing from the wrong directory; going up a directory...' )
        os.chdir('..')

    # If we don't find this file (given the expected filename) in the current folder, 
    # then we are clueless as to where we are.
    elif find( 'createSubmissionZip.py', curdir ) == None:
        # We haven't found this file, and 
        # any other potential place is too complex for us to track
        print( 'Are you sure you''re executing this script from the right place?' )
        print( 'Please make sure the python execution folder contains createSubimssionZip.py')


    # Compile the writeup report PDF if it doesn't exist
    writeupFile = 'writeup' + os.sep + 'writeup.pdf'
    if not os.path.exists( writeupFile ):
        os.chdir('writeup')
        command1 = 'pdflatex writeup.tex'
        command2 = 'bibtex'
        # LaTeX assured compile sequence if bibtex is used
        os.system( command1 )
        os.system( command2 )
        os.system( command1 )
        os.system( command1 )
        os.chdir( '..' )


    # Zip the files we need
    with zipfile.ZipFile( '1430submission.zip', 'w' ) as zip:
        # Write report
        if os.path.exists( writeupFile ):
            zip.write( writeupFile )
        # Write code .py files
        for file in get_all_file_paths( "code" + os.sep, ".py" ):
            zip.write( file )

    # Done!

if __name__ == "__main__":
    main()