#/usr/bin/python

#setup argument parser
import argparse

parser = argparse.ArgumentParser(description='A script to plot several timing histograms on top of one another. Pass it arguments for files, runs, and, if needed process names (assumes HLTX by default). For more than one file the arguments should be comma separated lists ordered respectively. Makes an output file called validation_plot.pdf Usage: python validation_plot.py --inputfiles INPUTFILES --runs RUNNUMBERS --processes PROCESSNAMES --log')


parser.add_argument("--inputfiles", type=str, help='The list of input files, comma separated if more than one file',required=True,nargs=1)
parser.add_argument("--runs",type=str,help='the corresponding run numbers, set to 1 by default',nargs=1)
parser.add_argument("--processes",type=str,help='the corresponding process names, set to HLTX by default',nargs=1)
parser.add_argument("--log",dest='log',action='store_true',help='specify to set log scale on the plot')
parser.add_argument("--ext",dest='ext',action='store_true',help='specify to set extended x-axis')
parser.add_argument("--outfile",type=str,help='optional outfile name',nargs=1)
args=parser.parse_args()


#import root libraries
from ROOT import gROOT, TCanvas, TH1F, TFile, TLegend, gStyle

#remove stat box
gStyle.SetOptStat(False)

#deal with parsing arguments correctly
multi=False
if args.inputfiles[0].find(","):
    files=args.inputfiles[0].split(",")
    if args.runs:
        runs=args.runs[0].split(",")
    else:
        j=0
        runs=[]
        while j<len(files):
            runs.append("1")
            j+=1
    if args.processes:
        processes=args.processes[0].split(",")
    else:
        k=0
        processes=[]
        while k < len(files):
            processes.append("HLTX")
            k+=1
    multi=True
else:
    files=args.inputfiles[0]
    if args.runs:
        runs=args.runs[0]
    else:
        runs=['1']
    if args.processes:
        processes=args.processes[0]
    else:
        processes=['HLTX']

#clear memory 
gROOT.Reset()
#make canvas to save plots to
c1 = TCanvas('c1','c1',10,10,2500,1500)
if args.log:
    c1.SetLogy()

i=0
Tfiles=[]
while i<len(files):
    print "Adding file: %s to list of files to run with Run Number: %s and Process Name: %s" % (files[i],runs[i],processes[i])
    Tfiles.append(TFile(files[i]))
    i+=1

j=0
Thists=[]
while j<len(Tfiles):
    #dirname="DQMData/Run %s/HLT/Run summary/TimerService/Running 1 processes/process %s/all_paths" % (runs[j],processes[j])
    dirname="DQMData/Run %s/HLT/Run summary/TimerService/event time_real" % (runs[j])
    print dirname
    hist=Tfiles[j].Get(dirname)
    print "type is ",type(hist)
    Thists.append(hist)
    j+=1

k=0
leg = TLegend(0.4,0.6,0.9,0.9,"")
leg.SetFillStyle(0)
leg.SetBorderSize(0)

while k< len(Thists):
    #work to get nice entry name
    name=''
    if not files[k].find("PU")==-1:
        pu='PU'+(files[k].split("PU")[1]).split("_")[0]
    else:
        pu=''
    if not files[k].find("Frozen")==-1:
        menu=''
        menu='Frozen'+(files[k].split('Frozen')[1]).split('_')[0]
    elif not files[k].find("GRun")==-1:
        menu=''
        menu='GRun'+(files[k].split('GRun')[1]).split('_')[0]
    else:
        menu=''
    #now do release
    if not files[k].find("CMSSW")==-1:
        release='CMSSW_'+(files[k].split("CMSSW")[1]).split(".")[0]
    else:
        release=''
    #now work on data/mc
    type=''
    if not files[k].find("MC")==-1:
        type='Spring15MC'
    elif files[k].find("Run")>-1:
        type="Run"+(files[k].split("_Run")[1]).split("_")[0]
    if k==0:
        #Thists[k].Scale( 1.0 / Thists[k].Integral() )
        Thists[k].GetYaxis().SetRangeUser(0.15,10000)
        print "lower bound of bin 100: %i" % Thists[k].GetBinCenter(100)
        print "percentage of events running particle flow: %i " % Thists[k].Integral(100,500)
        Thists[k].SetLineWidth(3)
        Thists[k].SetLineColor(k+4)
        #write name in full
        name += type+' '+pu+' '+menu+' '+release+" Mean: %3.2f ms" % Thists[k].GetMean()
        if args.ext:
            Thists[k].GetXaxis().SetRangeUser(0,2000)
        else:
            Thists[k].GetXaxis().SetRangeUser(0,400)
        Thists[k].Draw()
        leg.AddEntry(Thists[k],name,"l")
    else:
        Thists[k].Scale( 1.0 / Thists[k].Integral() )
        Thists[k].SetLineWidth(3)
        Thists[k].SetLineColor(k+4)
        Thists[k].Draw("same")
        #write name in full
        name += type+' '+pu+' '+menu+' '+release+" Mean: %3.2f ms" % Thists[k].GetMean()
        if args.ext:
            Thists[k].GetXaxis().SetRangeUser(0,2000)
        else:
            Thists[k].GetXaxis().SetRangeUser(0,400)
  
        leg.AddEntry(Thists[k],name,"l")
    k+=1

leg.Draw("same")

if args.outfile:
    filename=args.outfile[0]
else:
    filename='HLT_Validation_Plot.png'
c1.Print(filename)
 
