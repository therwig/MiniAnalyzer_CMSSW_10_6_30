import FWCore.ParameterSet.Config as cms
from FWCore.ParameterSet.VarParsing import VarParsing
import sys

options = VarParsing ('analysis')
isData = False
if len(sys.argv) > 2:
    try:
        isData = eval(sys.argv[2])
        sys.argv.pop( 2 )
        print "isData is set to ",isData
    except:
        pass
options.parseArguments()
isMC = True
if isData: isMC = False

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        'root://eospublic.cern.ch//eos/opendata/cms/mc/RunIISummer20UL16MiniAODv2/SingleNeutrino/MINIAODSIM/106X_mcRun2_asymptotic_v17-v2/230000/3FE9EEC3-4758-3542-A44B-0DF6DC678873.root'
    )
)
if isData:
    import FWCore.PythonUtilities.LumiList as LumiList
    jdir='/afs/cern.ch/user/t/therwig/workspace/jtfi/CMSSW_10_6_30/src/Test/MiniAnalyzer/data/'
    goodJSON = jdir+'Cert_271036-284044_13TeV_Legacy2016_Collisions16_JSON.txt'
    myLumis = LumiList.LumiList(filename = goodJSON).getCMSSWString().split(',')
    process.source.fileNames = cms.untracked.vstring(
        'root://eospublic.cern.ch//eos/opendata/cms/Run2016H/ZeroBias/MINIAOD/UL2016_MiniAODv2-v1/50000/108B0791-2B35-4441-B26D-3E251516F4D6.root'
    )
    process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange()
    process.source.lumisToProcess.extend(myLumis)

process.myl1 = cms.EDAnalyzer('L1TriggerAnalyzer',
			      isData = cms.bool(isData),
                              vertices=cms.InputTag("offlineSlimmedPrimaryVertices"), 
                              beams=cms.InputTag("offlineBeamSpot"),
                              jet=cms.InputTag("Central")
                              )

process.p = cms.Path(process.myl1)
