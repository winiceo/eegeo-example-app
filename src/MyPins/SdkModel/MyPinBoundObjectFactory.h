// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MyPins.h"
#include "IMyPinBoundObjectFactory.h"
#include "Types.h"
#include "BidirectionalBus.h"
#include "SdkModelDomainEventBus.h"
#include "CategorySearch.h"
#include "Search.h"
#include "Web.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            class MyPinBoundObjectFactory : public IMyPinBoundObjectFactory, private Eegeo::NonCopyable
            {
                ExampleAppMessaging::TMessageBus& m_messageBus;
                ExampleAppMessaging::TSdkModelDomainEventBus& m_sdkModelDomainEventBus;
                CategorySearch::View::ICategorySearchRepository& m_categorySearchRepository;
                Search::SdkModel::MyPins::IMyPinsSearchResultRefreshService& m_myPinsSearchResultRefreshService;
                Eegeo::Web::IWebLoadRequestFactory& m_webLoadRequestFactory;
                
            public:
                MyPinBoundObjectFactory(ExampleAppMessaging::TMessageBus& messageBus,
                                        ExampleAppMessaging::TSdkModelDomainEventBus& sdkModelDomainEventBus,
                                        CategorySearch::View::ICategorySearchRepository& categorySearchRepository,
                                        Search::SdkModel::MyPins::IMyPinsSearchResultRefreshService& myPinsSearchResultRefreshService,
                                        Eegeo::Web::IWebLoadRequestFactory& webLoadRequestFactory);
                
                ~MyPinBoundObjectFactory();
                
                IMyPinBoundObject* CreateUserCreatedPinBoundObject(MyPinsFileIO& myPinsFileIO,
                                                                   MyPinModel::TPinIdType pinId,
                                                                   Byte* imageData,
                                                                   size_t imageSize,
                                                                   bool share);
                
                IMyPinBoundObject* CreateSearchResultPinBoundObject(MyPinsFileIO& myPinsFileIO,
                                                                    MyPinModel::TPinIdType pinId,
                                                                    const Search::SdkModel::SearchResultModel& searchResult);
                
                IMyPinBoundObject* CreatePinBoundObjectFromSerialized(MyPinsFileIO& myPinsFileIO,
                                                                      MyPinModel::TPinIdType pinId,
                                                                      const MyPinsSemanticPinType& semanticPinType,
                                                                      const std::string& serializedData);
            };
        }
    }
}
