// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IOptionsView.h"
#include "WindowsNativeState.h"
#include "ICallback.h"
#include "CallbackCollection.h"
#include "ReflectionHelpers.h"

namespace ExampleApp
{
    namespace Options
    {
        namespace View
        {
            class OptionsView : public IOptionsView, private Eegeo::NonCopyable
            {
            private:
                WindowsNativeState& m_nativeState;
                
                gcroot<System::Type^> m_uiViewClass;
                gcroot<System::Object^> m_uiView;

                Helpers::ReflectionHelpers::Method<void> mDestroy;
                Helpers::ReflectionHelpers::Method<void> mIsCacheEnabledSelected;
                Helpers::ReflectionHelpers::Method<void> mOpenOptions;
                Helpers::ReflectionHelpers::Method<void> mCloseOptions;
                Helpers::ReflectionHelpers::Method<void> mConcludeCacheClearCeremony;
                Helpers::ReflectionHelpers::Method<bool> mSetCacheEnabledSelected;
                
                Eegeo::Helpers::CallbackCollection0 m_closeCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_wifiOnlyCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_cacheEnabledCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_clearCacheCallbacks;

            public:
                OptionsView(WindowsNativeState& nativeState);

                ~OptionsView();

                bool IsStreamOverWifiOnlySelected() const;

                bool IsCacheEnabledSelected() const;

                void SetStreamOverWifiOnlySelected(bool isStreamOverWifiOnlySelected);

                void SetCacheEnabledSelected(bool isCacheEnabledSelected);

                void Open();

                void Close();

                void ConcludeCacheClearCeremony();

                void HandleCloseSelected();

                void HandleStreamOverWifiOnlySelectionStateChanged();

                void HandleCacheEnabledSelectionStateChanged();

                void HandleClearCacheSelected();

                void InsertCloseSelectedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveCloseSelectedCallback(Eegeo::Helpers::ICallback0& callback);

                void InsertStreamOverWifiOnlySelectionChangedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveStreamOverWifiOnlySelectionChangedCallback(Eegeo::Helpers::ICallback0& callback);

                void InsertCacheEnabledSelectionCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveCacheEnabledSelectionCallback(Eegeo::Helpers::ICallback0& callback);

                void InsertClearCacheSelectedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveClearCacheSelectedCallback(Eegeo::Helpers::ICallback0& callback);
            };
        }
    }
}
