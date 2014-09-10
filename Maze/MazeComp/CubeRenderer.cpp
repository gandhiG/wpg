#include "pch.h"
#include "CubeRenderer.h"
using namespace DirectX;
using namespace Microsoft::WRL;
using namespace Windows::Foundation;
using namespace Windows::UI::Core;

using namespace Windows::Graphics::Display;

CubeRenderer::CubeRenderer() :
	m_loadingComplete(false),
	m_indexCount(0)
{
	m_accelerometer = Windows::Devices::Sensors::Accelerometer::GetDefault();
	scale = DisplayProperties::LogicalDpi / 96.0f;
}

void CubeRenderer::CreateDeviceResources()
{
	Direct3DBase::CreateDeviceResources();
	m_spriteBatch = unique_ptr<SpriteBatch>(new DirectX::SpriteBatch(m_d3dContext.Get()));
}

void CubeRenderer::CreateWindowSizeDependentResources()
{
	Direct3DBase::CreateWindowSizeDependentResources();
	m_ball = new Ball(0.0f, 0.0f, &m_windowBounds);
	m_ball->loadTexture(m_d3dDevice.Get());

	
}

void CubeRenderer::Update(float timeTotal, float timeDelta)
{
	if (m_accelerometer != nullptr)
	{
		m_accReading = m_accelerometer->GetCurrentReading();
	}
	m_ball->posX += (float)m_accReading->AccelerationX*4.0f*scale;
	m_ball->posY += (float)m_accReading->AccelerationY * 4.0f * scale *(-1);
	if (m_ball->posX > m_windowBounds.Width*scale - m_ball->diameter / 2.0f)
	{
		m_ball->posX = m_windowBounds.Width * scale - m_ball->diameter / 2.0f;
	}
	else if (m_ball->posX < m_ball->diameter / 2.0f)
	{
		m_ball->posX = m_ball->diameter / 2.0f;
	}
	if (m_ball->posY > m_windowBounds.Height * scale - m_ball->diameter / 2.0f)
	{
		m_ball->posY = m_windowBounds.Height * scale - m_ball->diameter / 2.0f;
	}
	else if (m_ball->posY < m_ball->diameter / 2.0f)
	{
		m_ball->posY = m_ball->diameter / 2.0f;
	}
}

void CubeRenderer::Render()
{
	const float bg_color[] = { 245.0f / 255.0f, 241.0f / 255.0f, 196.0f / 255.0f, 1.000f };
	m_d3dContext->ClearRenderTargetView(
		m_renderTargetView.Get(),
		bg_color
		);

	m_d3dContext->ClearDepthStencilView(
		m_depthStencilView.Get(),
		D3D11_CLEAR_DEPTH,
		1.0f,
		0
		);

	m_d3dContext->OMSetRenderTargets(
		1,
		m_renderTargetView.GetAddressOf(),
		m_depthStencilView.Get()
		);

	m_spriteBatch->Begin();
	m_ball->Draw(m_spriteBatch.get());
	m_spriteBatch->End();
	
}