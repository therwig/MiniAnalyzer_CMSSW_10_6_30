import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'root://eospublic.cern.ch//eos/opendata/cms/Run2016G/SingleElectron/MINIAOD/UL2016_MiniAODv2-v2/120000/FF99404A-8F07-444E-B931-7B2AE327070B.root'
    )
)

process.demo = cms.EDAnalyzer('MiniAnalyzer'
)


process.p = cms.Path(process.demo)
