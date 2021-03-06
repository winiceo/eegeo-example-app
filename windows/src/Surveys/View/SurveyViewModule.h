// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "ISurveyViewModule.h"
#include "Types.h"

#include "BidirectionalBus.h"
#include "Metrics.h"

namespace ExampleApp
{
    namespace Surveys
    {
        namespace View
        {
            class SurveyViewModule : public ISurveyViewModule, private Eegeo::NonCopyable
            {
            private:
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Metrics::IMetricsService& m_metricsService;

                std::string m_currentSurveyUrl;
                std::string m_currentSurveyMetricName;

                //Eegeo::Helpers::TCallback1<SurveyViewInterop, const StartSearchSurveyMessage&> m_startSearchSurveyCallback;
                //Eegeo::Helpers::TCallback1<SurveyViewInterop, const StartUxSurveyMessage&> m_startUxSurveyCallback;

                //Eegeo::Helpers::TCallback0<SurveyViewInterop> m_onSurveyAccepted;
                //Eegeo::Helpers::TCallback0<SurveyViewInterop> m_onSurveyRejected;

                void StartSearchSurveyCallback(const StartSearchSurveyMessage& message);
                void StartUxSurveyCallback(const StartUxSurveyMessage& message);

                void OnSurveyAccepted();
                void OnSurveyRejected();
                
            public:
                SurveyViewModule(ExampleAppMessaging::TMessageBus& messageBus,
                                 Metrics::IMetricsService& metricsService);
                
                ~SurveyViewModule();
            };
        }
    }
}
