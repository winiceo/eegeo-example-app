// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "AppRunner.h"
#include "Graphics.h"
#include "App.h"

AppRunner::AppRunner
(
    ViewController& viewController,
    UIView* pView
)
	: m_viewController(viewController)
	, m_pView(pView)
	, m_pAppHost(NULL)
{
	ReleaseDisplay();
	bool displayBound = TryBindDisplay();
	Eegeo_ASSERT(displayBound);
	CreateAppHost();
}

AppRunner::~AppRunner()
{
	m_displayService.ReleaseDisplay();

	if(m_pAppHost != NULL)
	{
		Eegeo_DELETE(m_pAppHost);
	}
}

void AppRunner::CreateAppHost()
{
    if (m_pAppHost == NULL && m_displayService.IsDisplayAvailable())
    {
        const Eegeo::Rendering::ScreenProperties& screenProperties =
        Eegeo::Rendering::ScreenProperties::Make(
                                                 m_displayService.GetDisplayWidth(),
                                                 m_displayService.GetDisplayHeight(),
                                                 m_displayService.GetPixelScale(),
                                                 m_displayService.GetDisplayDpi());
        
        m_pAppHost = Eegeo_NEW(AppHost)
        (
            m_viewController,
            m_pView,
            screenProperties
        );
    }
}

void AppRunner::Pause()
{
	if(m_pAppHost != NULL)
	{
		m_pAppHost->OnPause();
	}
}

void AppRunner::Resume()
{
	if(m_pAppHost != NULL)
	{
		m_pAppHost->OnResume();
	}
}

void AppRunner::ReleaseDisplay()
{
	if(m_displayService.IsDisplayAvailable())
	{
		m_displayService.ReleaseDisplay();
	}
}

bool AppRunner::TryBindDisplay()
{
	return m_displayService.TryBindDisplay((GLKView&)*[&m_viewController view]);
}

void AppRunner::Update(float deltaSeconds)
{
	if(m_pAppHost != NULL && m_displayService.IsDisplayAvailable())
	{
		m_pAppHost->Update(deltaSeconds);

		Eegeo_GL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));

		m_pAppHost->Draw(deltaSeconds);
	}
}

void AppRunner::NotifyViewLayoutChanged()
{
    if (m_displayService.IsDisplayAvailable())
    {
        m_displayService.UpdateDisplayDimensions();
        
        const Eegeo::Rendering::ScreenProperties& screenProperties =
        Eegeo::Rendering::ScreenProperties::Make(
                                                 m_displayService.GetDisplayWidth(),
                                                 m_displayService.GetDisplayHeight(),
                                                 m_displayService.GetPixelScale(),
                                                 m_displayService.GetDisplayDpi());
        
        m_pAppHost->NotifyScreenPropertiesChanged(screenProperties);
    }
}

bool AppRunner::IsRunning()
{
	if(m_pAppHost == NULL)
	{
		return false;
	}

	return m_pAppHost->IsRunning();
}

bool AppRunner::ShouldAutoRotateToInterfaceOrientation(UIInterfaceOrientation interfaceOrientation)
{
    return true;
}
