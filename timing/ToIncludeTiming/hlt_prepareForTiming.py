#!/usr/bin/env python
############################################################################
#
# Edgar Carrera
# ecarrera@cern.ch
#
# This script takes an hlt.py template (gotten with hltGetConfiguration) and
# prepares it for timing studies: hltTiming.py
# It adds a bunch of needed configuration lines
# and dump a list of files from a give txt file
###########################################################################

"""
   usage: %prog [options]
   -f, --files = FILES: text file with root data/mc files.
"""


import os,sys
import subprocess
import string, re
import fileinput
import commands
from time import gmtime, localtime, strftime


# _____________________OPTIONS_______________________________________________

############################################################################
# Code taken from http://code.activestate.com/recipes/278844/
############################################################################
import optparse
USAGE = re.compile(r'(?s)\s*usage: (.*?)(\n[ \t]*\n|$)')
def nonzero(self): # will become the nonzero method of optparse.Values
    "True if options were given"
    for v in self.__dict__.itervalues():
        if v is not None: return True
    return False

optparse.Values.__nonzero__ = nonzero # dynamically fix optparse.Values

class ParsingError(Exception): pass

optionstring=""

def exit(msg=""):
    raise SystemExit(msg or optionstring.replace("%prog",sys.argv[0]))

def parse(docstring, arglist=None):
    global optionstring
    optionstring = docstring
    match = USAGE.search(optionstring)
    if not match: raise ParsingError("Cannot find the option string")
    optlines = match.group(1).splitlines()
    try:
        p = optparse.OptionParser(optlines[0])
        for line in optlines[1:]:
            opt, help=line.split(':')[:2]
            short,long=opt.split(',')[:2]
            if '=' in opt:
                action='store'
                long=long.split('=')[0]
            else:
                action='store_true'
            p.add_option(short.strip(),long.strip(),
                         action = action, help = help.strip())
    except (IndexError,ValueError):
        raise ParsingError("Cannot parse the option string correctly")
    return p.parse_args(arglist)


#_________________________________________________________________________

#######################################################
def prepare_for_timing(dicOpt):
#######################################################
    datafile = dicOpt['files']
    #clear config and copy template
    os.system("rm -f hltTiming.py")
    os.system("cp -p hlt.py hltTiming.py")
    #open a config file to append
    cfg = open("hltTiming.py","a")

    cfg.write(
    """
# remove any instance of the FastTimerService
if 'FastTimerService' in process.__dict__:
        del process.FastTimerService

        # instrument the menu with the FastTimerService
        process.load( "HLTrigger.Timer.FastTimerService_cfi" )

        # print a text summary at the end of the job
        process.FastTimerService.printEventSummary        = False
        process.FastTimerService.printRunSummary          = False
        process.FastTimerService.printJobSummary          = True

        # enable DQM plots
        process.FastTimerService.enableDQM                = True

        # enable per-path DQM plots (starting with CMSSW 9.2.3-patch2)
        process.FastTimerService.enableDQMbyPath          = True

        # enable per-module DQM plots
        process.FastTimerService.enableDQMbyModule        = True

        # enable DQM plots vs lumisection
        process.FastTimerService.enableDQMbyLumiSection   = True
        process.FastTimerService.dqmLumiSectionsRange     = 2500    # lumisections (23.31 s)

        # set the time resolution of the DQM plots
#        process.FastTimerService.dqmTimeRange             = 1000.   # ms        
        process.FastTimerService.dqmTimeRange             = 5000.   # ms
        process.FastTimerService.dqmTimeResolution        =    5.   # ms
#        process.FastTimerService.dqmPathTimeRange         = 100.   # ms
        process.FastTimerService.dqmPathTimeRange         = 2000.   # ms
        process.FastTimerService.dqmPathTimeResolution    =    0.5  # ms
#        process.FastTimerService.dqmModuleTimeRange       =   40.   # ms
        process.FastTimerService.dqmModuleTimeRange       = 800.   # ms
        process.FastTimerService.dqmModuleTimeResolution  =    0.2  # ms

        # set the base DQM folder for the plots
        process.FastTimerService.dqmPath                  = "HLT/TimerService"
        process.FastTimerService.enableDQMbyProcesses     = False
        
        # save the DQM plots in the DQMIO format
        process.dqmOutput = cms.OutputModule("DQMRootOutputModule",
                                                 fileName = cms.untracked.string("DQM.root")
                                             )
        process.FastTimerOutput = cms.EndPath( process.dqmOutput )

"""
        )

    #read the filelist and make a string to replace the 'myroot.root'
    _file = open(datafile,"r")
    mystring = ""
    for fline in _file.readlines():
        mystring = mystring+fline.rstrip()

    with open('hltTiming.py','r') as myfile:
        filedata = myfile.read()

    filedata = filedata.replace("['myroot.root']","["+mystring+"]")

    with open('hltTiming.py','w') as myfile:
        myfile.write(filedata)

    #prepare string to execute in system
#    str_sed = "sed -e 's#'myroot.root'#"+mystring+"#g' hltTiming.py"
    



#######################################################
def get_default_options(option):
#######################################################
    dicOpt = {}

    dicOpt['files']= str(option.files)
  
    return dicOpt

#######################################################
if __name__ =='__main__':
#######################################################

    #import optionparser
    option,args = parse(__doc__)
    if not args and not option:
        exit()
    
    
    #set default options
    dicOpt = get_default_options(option)

    #print configuration
    for k in dicOpt:
        print str(k)+" = "+str(dicOpt[k])
    
    #transform the file
    prepare_for_timing(dicOpt)

    
