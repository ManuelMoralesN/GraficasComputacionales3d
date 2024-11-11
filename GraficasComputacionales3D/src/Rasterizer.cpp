/*#include "Rasterizer.h"

void Rasterizer::init(ID3D11Device* device) {
    D3D11_RASTERIZER_DESC rasterizerDesc = {};
    rasterizerDesc.FillMode = D3D11_FILL_SOLID;
    rasterizerDesc.CullMode = D3D11_CULL_BACK;
    rasterizerDesc.FrontCounterClockwise = false;
    rasterizerDesc.DepthBias = 0;
    rasterizerDesc.SlopeScaledDepthBias = 0.0f;
    rasterizerDesc.DepthBiasClamp = 0.0f;
    rasterizerDesc.DepthClipEnable = true;
    rasterizerDesc.ScissorEnable = false;
    rasterizerDesc.MultisampleEnable = false;
    rasterizerDesc.AntialiasedLineEnable = false;

    HRESULT hr = S_OK;

    hr = device->CreateRasterizerState(&rasterizerDesc, &m_rasterizerState);

    if (FAILED(hr)) {
        std::cout << "Error creating the Rasterizer State" << std::endl;
    }
}

void 
Rasterizer::render(ID3D11DeviceContext* deviceContext) {
    deviceContext->RSSetState(m_rasterizerState);
}
void 
Rasterizer::destroy() {
    if (m_rasterizerState) m_rasterizerState->Release();
}*/