#include "pch.h"
#include "Ball.h"

using namespace Windows::Graphics::Display;
Ball :: Ball(){}
Ball::Ball(float x, float y, Windows::Foundation::Rect* windowBounds)
{
	posX = x;
	posY = y;
	scale = DisplayProperties::LogicalDpi / 96.0f;
	diameter = windowBounds->Width*scale / 5.0f;
	m_Texture = nullptr;
}
void Ball::loadTexture(ID3D11Device* d3dDevice)
{
	CreateDDSTextureFromFile(d3dDevice, L"Assets/ball.dds", nullptr, &m_Texture, MAXSIZE_T);
}
void Ball::Draw(SpriteBatch* sb)
{
	sb->Draw(m_Texture, XMFLOAT2(posX, posY), nullptr, Colors::White, 0.0f, XMFLOAT2(250.0f, 250.0f), XMFLOAT2(diameter / 500.0f, diameter / 500.0f), DirectX::SpriteEffects_None, 0.0f);
}
