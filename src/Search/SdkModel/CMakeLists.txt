set(headers ${headers} ../src/Search/SdkModel
)
set(currsources
  ../src/Search/SdkModel/CMakeLists.txt
  ../src/Search/SdkModel/IdentitySearchCallbackData.h
  ../src/Search/SdkModel/ISearchModule.h
  ../src/Search/SdkModel/ISearchQueryPerformer.h
  ../src/Search/SdkModel/ISearchRefreshService.h
  ../src/Search/SdkModel/ISearchResultParser.h
  ../src/Search/SdkModel/ISearchResultRepository.h
  ../src/Search/SdkModel/ISearchService.h
  ../src/Search/SdkModel/ISearchServiceModule.h
  ../src/Search/SdkModel/SearchJsonParser.cpp
  ../src/Search/SdkModel/SearchJsonParser.h
  ../src/Search/SdkModel/SearchModule.cpp
  ../src/Search/SdkModel/SearchModule.h
  ../src/Search/SdkModel/SearchQuery.cpp
  ../src/Search/SdkModel/SearchQuery.h
  ../src/Search/SdkModel/SearchQueryObserver.cpp
  ../src/Search/SdkModel/SearchQueryObserver.h
  ../src/Search/SdkModel/SearchQueryPerformer.cpp
  ../src/Search/SdkModel/SearchQueryPerformer.h
  ../src/Search/SdkModel/SearchRefreshService.cpp
  ../src/Search/SdkModel/SearchRefreshService.h
  ../src/Search/SdkModel/SearchResultModel.cpp
  ../src/Search/SdkModel/SearchResultModel.h
  ../src/Search/SdkModel/SearchResultRepository.cpp
  ../src/Search/SdkModel/SearchResultRepository.h
  ../src/Search/SdkModel/SearchServiceBase.cpp
  ../src/Search/SdkModel/SearchServiceBase.h
  ../src/Search/SdkModel/SerializeSearchResultModelToJson.cpp
)
set(sources ${sources} ${currsources})
source_group(\\src\\Search\\SdkModel FILES ${currsources})
include(../src/Search/SdkModel/MyPins/CMakeLists.txt)
