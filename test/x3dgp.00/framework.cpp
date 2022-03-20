#include "framework.h"

framework::framework(HWND hwnd) : hwnd(hwnd)
{
}

bool framework::initialize()
{

	//디바이스, 디바이스 콘텍스트, 스왑체인 생성
	HRESULT hr{ S_OK };

	UINT create_device_flags{ 0 };
#ifdef _DEBUG
	create_device_flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL feature_levels{ D3D_FEATURE_LEVEL_11_0 };
	
	DXGI_SWAP_CHAIN_DESC swap_chain_desc{};
	swap_chain_desc.BufferCount = 1;
	swap_chain_desc.BufferDesc.Width = SCREEN_WIDTH;
	swap_chain_desc.BufferDesc.Height = SCREEN_HEIGHT;
	swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swap_chain_desc.BufferDesc.RefreshRate.Numerator = 60;
	swap_chain_desc.BufferDesc.RefreshRate.Denominator = 1;
	swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swap_chain_desc.OutputWindow = hwnd;
	swap_chain_desc.SampleDesc.Count = 1;
	swap_chain_desc.SampleDesc.Quality = 0;
	swap_chain_desc.Windowed = !FULLSCREEN;
	hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, create_device_flags,
										&feature_levels, 1, D3D11_SDK_VERSION, &swap_chain_desc,
										&swap_chain, &device, NULL, &immediate_context);
	 _ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));

	 //렌더 타켓 뷰 생성

	 ID3D11Texture2D* back_buffer{};
	 hr = swap_chain -> GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&back_buffer));
	 _ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));

	 hr = device->CreateRenderTargetView(back_buffer, NULL, &render_target_view);
	 _ASSERT_EXPR(SUCCEEDED(hr), hr_trace(hr));

	 back_buffer->Release();

	return true;
}

void framework::update(float elapsed_time/*Elapsed seconds from last frame*/)
{
#ifdef USE_IMGUI
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
#endif


#ifdef USE_IMGUI
	ImGui::Begin("ImGUI");


	ImGui::End();
#endif
}
void framework::render(float elapsed_time/*Elapsed seconds from last frame*/)
{


#ifdef USE_IMGUI
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
#endif


}

bool framework::uninitialize()
{



	return true;
}

framework::~framework()
{

}