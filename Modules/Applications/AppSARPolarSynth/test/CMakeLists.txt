#
# Copyright (C) 2005-2017 Centre National d'Etudes Spatiales (CNES)
#
# This file is part of Orfeo Toolbox
#
#     https://www.orfeo-toolbox.org/
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

otb_module_test()
#----------- PolarSynth TESTS ----------------

otb_test_application(NAME  apTvSARPolarSynth
                     APP  SARPolarSynth
                     OPTIONS -in ${INPUTDATA}/RSAT2_AltonaExtract_1000_1000_100_100.hdr
               	             -out ${TEMP}/resApMultiPolarimetricSynthesis1.tif
                             -psii 10.0 
                             -khii 0.0
                             -psir 0.0
                             -khir 0.0
                     )
                             
