#!/bin/bash
python MyA/scripts/Run.py \
    --submitDir "test" \
    -w \
    --inputFiles "/nfs/slac/g/atlas/u01/users/acukierm/GridGeneration/user.acukierm.13TeV.360003.VBFHa30a30gamgamgg.eZZ3_EXT0.TRUTH_EXT0/" \
    --nevents -1 \
    --mode "class" \
    --driver "direct"
exit 0

#--inputFiles "/atlas/dq2/user/bnachman/" \
    #--inputFiles "/nfs/slac/g/atlas/u01/users/acukierm/VBF/mc_sample/" \
