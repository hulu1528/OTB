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

set(OTBMathParserTests
otbMathParserTestDriver.cxx
otbMaskMuParserFilterNew.cxx
otbMaskMuParserFilterTest.cxx
otbParserConditionDataNodeFeatureFunction.cxx
otbParserTest.cxx
otbImageListToSingleImageFilterTest.cxx
otbBandMathImageFilter.cxx
)

add_executable(otbMathParserTestDriver ${OTBMathParserTests})
target_link_libraries(otbMathParserTestDriver ${OTBMathParser-Test_LIBRARIES})
otb_module_target_label(otbMathParserTestDriver)

# Tests Declaration



otb_add_test(NAME bfTuMaskMuParserFilterNew COMMAND otbMathParserTestDriver
  otbMaskMuParserFilterNew
  )

otb_add_test(NAME bfTvMaskMuParserFilterTest COMMAND otbMathParserTestDriver
  --compare-image ${NOTOL}
  ${BASELINE}/bfTvMaskMuParserFilterTest.tif
  ${TEMP}/bfTvMaskMuParserFilterTest.tif
  otbMaskMuParserFilterTest
  ${INPUTDATA}/ROI_QB_MUL_4.tif
  ${TEMP}/bfTvMaskMuParserFilterTest.tif
  "(b1>100)*(b2>120)"
  )

otb_add_test(NAME bfTvParserConditionDataNodeFeatureFunction_Line_NDVI COMMAND otbMathParserTestDriver
  --compare-ogr ${NOTOL}
  ${BASELINE_FILES}/bfTvNDVIDataNodeFeatureFunctionOutput_Line.shp
  ${TEMP}/bfTvParserConditionDataNodeFeatureFunction_Line_NDVI.shp
  otbParserConditionDataNodeFeatureFunction
  ${INPUTDATA}/Dempster-Shafer/ROI_QB_TOULOUSE_ROADS.shp
  ${INPUTDATA}/Dempster-Shafer/ROI_QB_TOULOUSE.TIF
  ${INPUTDATA}/DEM/srtm_directory
  ${TEMP}/bfTvParserConditionDataNodeFeatureFunction_Line_NDVI.shp
  "ndvi(b3,b4) > 0.047"
  0
  )

otb_add_test(NAME bfTvParserConditionDataNodeFeatureFunction_Polygon_NDVI COMMAND otbMathParserTestDriver
  --compare-ogr ${NOTOL}
  ${BASELINE_FILES}/bfTvNDVIDataNodeFeatureFunctionOutput_Polygon.shp
  ${TEMP}/bfTvParserConditionDataNodeFeatureFunction_Polygon_NDVI.shp
  otbParserConditionDataNodeFeatureFunction
  ${INPUTDATA}/Dempster-Shafer/ROI_QB_TOULOUSE_BUILDINGS.shp
  ${INPUTDATA}/Dempster-Shafer/ROI_QB_TOULOUSE.TIF
  ${INPUTDATA}/DEM/srtm_directory
  ${TEMP}/bfTvParserConditionDataNodeFeatureFunction_Polygon_NDVI.shp
  "ndvi(b3,b4) > 0.047"
  0
  )

otb_add_test(NAME coTvParser COMMAND otbMathParserTestDriver
  otbParserTest
  )

otb_add_test(NAME coTuParser COMMAND otbMathParserTestDriver
  otbParserTestNew
  )

otb_add_test(NAME bfTuImageListToSingleImageFilterNew COMMAND otbMathParserTestDriver
  otbImageListToSingleImageFilterNew)

otb_add_test(NAME bfTvImageListToSingleImageFilter COMMAND otbMathParserTestDriver
  --compare-image ${NOTOL}
  ${BASELINE}/bfTvImageListToSingleImageFilter.tif
  ${TEMP}/bfTvImageListToSingleImageFilterOut.tif
  otbImageListToSingleImageFilter
  ${INPUTDATA}/poupees.png
  ${TEMP}/bfTvImageListToSingleImageFilterOut.tif
  )






otb_add_test(NAME bfTvBandMathImageFilterWithIdx COMMAND otbMathParserTestDriver
  otbBandMathImageFilterWithIdx
  ${TEMP}/bfTvBandMathImageFilterWithIdx1.tif
  ${TEMP}/bfTvBandMathImageFilterWithIdx2.tif
  )

otb_add_test(NAME bfTuBandMathImageFilter COMMAND otbMathParserTestDriver
  otbBandMathImageFilterNew)

otb_add_test(NAME bfTvBandMathImageFilter COMMAND otbMathParserTestDriver
  otbBandMathImageFilter)

