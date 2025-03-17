#usage: runScript.sh flist_SingleNeutrino.txt 3 /eos/user/t/therwig/jtfi/240621_myOutDir_v1/
#echo beginning runscript 
startTime=`date +%s`
fileList="$1"
fileIndex=$(($2+1)) # files indexed from 1, but job index runs from 0
outDir="$3"
isData="$4"

runDir=`pwd`
source /cvmfs/cms.cern.ch/cmsset_default.sh
dir=/afs/cern.ch/user/t/therwig/workspace/jtfi/CMSSW_10_6_30/src/
cd $dir
eval $(scramv1 runtime -sh) #cmsenv
cd Test/MiniAnalyzer/python
inFile=`head -n $fileIndex batch/$fileList | tail -n 1`
cp myConfig.py $runDir/cfg.py
cd $runDir
outFile="output_${fileIndex}.root"
cat >> cfg.py <<_EOF_

#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000000) )
process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring(
    'file:${inFile}'
        )
)
#process.TFileService = cms.Service("TFileService", fileName=cms.string("${outFile}"))
_EOF_

# "process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )"
# process.source = cms.Source("PoolSource", fileNames = cms.untracked.vstring(
#     'file:/eos/opendata/cms/mc/RunIIFall15MiniAODv2/SingleNeutrino/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/00000/E6DAAEBB-E5BB-E511-A93D-E4115BCE00BE.root'
#         )
# )
# process.TFileService = cms.Service("TFileService", fileName=cms.string("myoutput.root"))

cmsRun cfg.py $isData
ls -lth
mv ntuple.root ${outFile}
ls -lth ${outFile}

mkdir -p $outDir/
mv ${outFile} $outDir/

endTime=`date +%s`
runtime=$((endTime-startTime))
echo RUNTIME IS $runtime

