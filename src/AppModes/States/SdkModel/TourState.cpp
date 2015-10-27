// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TourState.h"
#include "IAppCameraController.h"
#include "TourService.h"
#include "IAppModeModel.h"
#include "InteriorSelectionModel.h"
#include "CameraHelpers.h"
#include "CameraState.h"
#include "RenderCamera.h"
#include "GlobeCameraController.h"
#include "GpsGlobeCameraController.h"
#include "InteriorsExplorerCameraController.h"
#include "MathFunc.h"

namespace ExampleApp
{
    namespace AppModes
    {
        namespace States
        {
            namespace SdkModel
            {
                TourState::TourState(AppCamera::SdkModel::IAppCameraController& cameraController,
                                     int tourCameraHandle,
                                     Tours::SdkModel::ITourService& tourService,
                                     Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                     AppModes::SdkModel::IAppModeModel& appModeModel,
                                     Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& worldCameraController,
                                     ExampleApp::InteriorsExplorer::SdkModel::InteriorsExplorerCameraController& interiorsCameraController)
                : m_cameraController(cameraController)
                , m_tourCameraHandle(tourCameraHandle)
                , m_tourService(tourService)
                , m_tourStartedCallback(this, &TourState::OnTourEnded)
                , m_interiorSelectionModel(interiorSelectionModel)
                , m_appModeModel(appModeModel)
                , m_worldCameraController(worldCameraController)
                , m_interiorsCameraController(interiorsCameraController)
                {
                }
                
                TourState::~TourState()
                {
                }
                
                void TourState::Enter()
                {
                    m_cameraController.TransitionToCameraWithHandle(m_tourCameraHandle);
                    m_tourService.RegisterTourEndedCallback(m_tourStartedCallback);
                }
                
                void TourState::Update(float dt)
                {
                }
                
                void TourState::Exit()
                {
                    m_tourService.UnregisterTourEndedCallback(m_tourStartedCallback);
                    
                    float headingRadians = Eegeo::Camera::CameraHelpers::GetAbsoluteBearingRadians(m_cameraController.GetCameraState().InterestPointEcef(),
                                                                                                   m_cameraController.GetRenderCamera().GetModelMatrix().GetRow(2));
                    
                    const float interestDistance = m_appModeModel.GetAppMode() == AppModes::SdkModel::WorldMode ? 500.0f : 150.0f;
                    
                    if(m_appModeModel.GetAppMode() == AppModes::SdkModel::WorldMode)
                    {
                        Eegeo::Space::LatLongAltitude latLong = Eegeo::Space::LatLongAltitude::FromECEF(m_cameraController.GetCameraState().InterestPointEcef());
                        
                        m_worldCameraController.SetView(latLong.GetLatitudeInDegrees(), latLong.GetLongitudeInDegrees(),
                                                        Eegeo::Math::Rad2Deg(headingRadians),
                                                        interestDistance);
                        m_worldCameraController.GetGlobeCameraController().ApplyTilt(0.0f);
                    }
                    else if(m_appModeModel.GetAppMode() == AppModes::SdkModel::InteriorMode)
                    {
                        m_interiorsCameraController.SetDistanceToInterest(interestDistance);
                        m_interiorsCameraController.SetHeading(Eegeo::Math::Rad2Deg(headingRadians));
                        m_interiorsCameraController.SetInterestLocation(m_cameraController.GetCameraState().InterestPointEcef());
                    }
                }

                
                void TourState::OnTourEnded()
                {
                    const ExampleApp::AppModes::SdkModel::AppMode mode = m_interiorSelectionModel.IsInteriorSelected() ?
                                ExampleApp::AppModes::SdkModel::InteriorMode : ExampleApp::AppModes::SdkModel::WorldMode;
                    
                    m_appModeModel.SetAppMode(mode);
                }
                
            }
        }
    }
}