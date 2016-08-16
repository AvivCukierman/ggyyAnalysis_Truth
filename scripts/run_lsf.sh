#!/bin/bash
python MyA/scripts/Run.py \
    --submitDir "LSF_VBF_a30" \
    -w \
    --inputFiles "/nfs/slac/g/atlas/u01/users/acukierm/GridGeneration/user.acukierm.13TeV.360003.VBFHa30a30gamgamgg.eZZ3_EXT0.TRUTH_EXT0/" \
    --mode "class" \
    --driver "lsf"
exit 0
#--inputDQ2 \
#--inputFiles "user.acukierm.303727.Sherpa_CT10_2DP20_myy_0_55.TRUTH_EXT0" \
#--inputFiles "user.acukierm.303728.Sherpa_CT10_2DP20_myy_55_100.TRUTH_EXT0" \
#--inputFiles "user.acukierm.36003.VBFHa30a30gamgamgg.eXX1_EXT0.TRUTH_EXT0" \
