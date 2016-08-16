#!/bin/bash
python MyA/scripts/Run.py \
    --submitDir "LSF_VBF_a2" \
    -w \
    --inputFiles "/nfs/slac/g/atlas/u01/users/acukierm/GridGeneration/user.acukierm.13TeV.360000.VBFHa2a2gamgamgg.eZZ5_EXT0.TRUTH_EXT0/" \
    --mode "class" \
    --driver "lsf"

python MyA/scripts/Run.py \
    --submitDir "LSF_VBF_a10" \
    -w \
    --inputFiles "/nfs/slac/g/atlas/u01/users/acukierm/GridGeneration/user.acukierm.13TeV.360001.VBFHa10a10gamgamgg.eZZ3_EXT0.TRUTH_EXT0/" \
    --mode "class" \
    --driver "lsf"

python MyA/scripts/Run.py \
    --submitDir "LSF_VBF_a20" \
    -w \
    --inputFiles "/nfs/slac/g/atlas/u01/users/acukierm/GridGeneration/user.acukierm.13TeV.360002.VBFHa20a20gamgamgg.eZZ3_EXT0.TRUTH_EXT0/" \
    --mode "class" \
    --driver "lsf"

python MyA/scripts/Run.py \
    --submitDir "LSF_VBF_a40" \
    -w \
    --inputFiles "/nfs/slac/g/atlas/u01/users/acukierm/GridGeneration/user.acukierm.13TeV.360004.VBFHa40a40gamgamgg.eZZ5_EXT0.TRUTH_EXT0/" \
    --mode "class" \
    --driver "lsf"

python MyA/scripts/Run.py \
    --submitDir "LSF_VBF_a50" \
    -w \
    --inputFiles "/nfs/slac/g/atlas/u01/users/acukierm/GridGeneration/user.acukierm.13TeV.360005.VBFHa50a50gamgamgg.eZZ3_EXT0.TRUTH_EXT0/" \
    --mode "class" \
    --driver "lsf"

python MyA/scripts/Run.py \
    --submitDir "LSF_VBF_a60" \
    -w \
    --inputFiles "/nfs/slac/g/atlas/u01/users/acukierm/GridGeneration/user.acukierm.13TeV.360006.VBFHa60a60gamgamgg.eZZ5_EXT0.TRUTH_EXT0/" \
    --mode "class" \
    --driver "lsf"

python MyA/scripts/Run.py \
    --submitDir "GGH_VBF_a2" \
    -w \
    --inputFiles "/nfs/slac/g/atlas/u01/users/acukierm/GridGeneration/user.acukierm.13TeV.360100.ggHa2a2gamgamgg.eZZ3_EXT0.TRUTH_EXT0/" \
    --mode "class" \
    --driver "lsf"

python MyA/scripts/Run.py \
    --submitDir "GGH_VBF_a10" \
    -w \
    --inputFiles "/nfs/slac/g/atlas/u01/users/acukierm/GridGeneration/user.acukierm.13TeV.360101.ggHa10a10gamgamgg.eZZ3_EXT0.TRUTH_EXT0/" \
    --mode "class" \
    --driver "lsf"

python MyA/scripts/Run.py \
    --submitDir "GGH_VBF_a20" \
    -w \
    --inputFiles "/nfs/slac/g/atlas/u01/users/acukierm/GridGeneration/user.acukierm.13TeV.360102.ggHa20a20gamgamgg.eZZ3_EXT0.TRUTH_EXT0/" \
    --mode "class" \
    --driver "lsf"

python MyA/scripts/Run.py \
    --submitDir "GGH_VBF_a40" \
    -w \
    --inputFiles "/nfs/slac/g/atlas/u01/users/acukierm/GridGeneration/user.acukierm.13TeV.360104.ggHa40a40gamgamgg.eZZ3_EXT0.TRUTH_EXT0/" \
    --mode "class" \
    --driver "lsf"

python MyA/scripts/Run.py \
    --submitDir "GGH_VBF_a50" \
    -w \
    --inputFiles "/nfs/slac/g/atlas/u01/users/acukierm/GridGeneration/user.acukierm.13TeV.360105.ggHa50a50gamgamgg.eZZ3_EXT0.TRUTH_EXT0/" \
    --mode "class" \
    --driver "lsf"

python MyA/scripts/Run.py \
    --submitDir "GGH_VBF_a60" \
    -w \
    --inputFiles "/nfs/slac/g/atlas/u01/users/acukierm/GridGeneration/user.acukierm.13TeV.360106.ggHa60a60gamgamgg.eZZ3_EXT0.TRUTH_EXT0/" \
    --mode "class" \
    --driver "lsf"
