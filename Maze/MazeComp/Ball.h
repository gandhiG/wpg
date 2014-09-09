#pragma once

#include "SpriteBatch.h"
#include "DDSTextureLoader.h"
#include <D3D11.h>

using namespace DirectX;
using namespace std;

class Ball
{
public:
	Ball();
	Ball(float x, float y, Windows::Foundation::Rect* windowBounds);
	void Draw(SpriteBatch* sb);
	void loadTexture(ID3D11Device* d3dDevice);
	float posX;
	float posY;
	float diameter;

private:
	ID3D11ShaderResourceView* m_Texture;

	float scale;
};