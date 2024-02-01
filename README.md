# MiniAnalyzer_CMSSW_10_6_30
EDAnalyzer example for MiniAOD processing in CMSSW_10_6_30. The code in this repository replicates the output of 
`mkedanlzr` in earlier CMSSW releases. 

### Install

This code is intended for use with the CMS Open Data [docker container](https://opendata.cern.ch/docs/cms-guide-docker) or [virtual machine](https://opendata.cern.ch/docs/cms-virtual-machine-2016-2018) for CMSSW_10_6_30. Follow the instructions on those websites to install this computing environment. 

Download this repository: 

```
$ cd CMSSW_10_6_30/src/  # not needed in the docker container
$ cmsenv
$ git clone https://github.com/cms-opendata-analyses/MiniAnalyzer_CMSSW_10_6_30 Test/MiniAnalyzer
```

### Compile and run

The contents of the new `MiniAnalyzer` directory form an `EDAnalyzer` package in CMSSW. Compile this analyzer:

```
$ scram b
```

The analyzer's source code is found in `plugins/MiniAnalyzer.cc` and the CMSSW packages that must be referenced are listed in `plugins/BuildFile.xml`.
The configuration file for the analyze is found in `python/ConfFile_cfg.py`. This configuration file already has an example 2016 Open Data MiniAOD file
and is set to run a short test of only 10 events. Process these 10 events through the analyzer using `cmsRun`:

```
$ cd Test/MiniAnalyzer/
$ cmsRun python/ConfFile_cfg.py
```

More information, including an expansion of this example analyzer, can be found in the [MiniAOD Getting Started page](https://opendata.cern.ch/docs/cms-getting-started-miniaod).
