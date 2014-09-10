#pragma once

#include <wrl\client.h>
#include <memory>
#include "Direct3DBase.h"
#include <DirectXMath.h>
#include "SpriteBatch.h"
#include "Ball.h"
using namespace Windows::Devices::Sensors;
// This class renders a simple spinning cube.
ref class CubeRenderer sealed : public Direct3DBase
{
public:
	CubeRenderer();

	// Direct3DBase methods.
	virtual void CreateDeviceResources() override;
	virtual void CreateWindowSizeDependentResources() override;
	virtual void Render() override;
	
	// Method for updating time-dependent objects.
	void Update(float timeTotal, float timeDelta);

private:
	bool m_loadingComplete;
	uint32 m_indexCount;
	unique_ptr<SpriteBatch> m_spriteBatch;
	Accelerometer^ m_accelerometer;
	AccelerometerReading^ m_accReading;
	float scale;
	Ball* m_ball;
};
