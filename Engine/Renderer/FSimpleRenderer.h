/*
 * FSimpleRenderer.h
 *
 *  Created on: Feb 7, 2017
 *      Author: root
 */

#ifndef ENGINE_RENDERER_FSIMPLERENDERER_H_
#define ENGINE_RENDERER_FSIMPLERENDERER_H_

#include "../Window/FWindow.h"

#define VK_USE_PLATFORM_XCB_KHR
#include <vulkan/vulkan.h>
#include <memory>
#include <vector>


class FSimpleRenderer {
public:
	FSimpleRenderer( FWindow& window );
	virtual ~FSimpleRenderer();

private:
	void createInstance();
	void selectGPU();
	void createLogicalDevice();
	void createSurface();
	void createSwapChain();
	void createImageViews();
	void createGraphicPipelines();

	VkInstance						_instance				= VK_NULL_HANDLE;
	VkPhysicalDevice				_physical_device		= VK_NULL_HANDLE;
	VkDevice						_device					= VK_NULL_HANDLE;
	VkSurfaceKHR					_surface				= VK_NULL_HANDLE;
	VkSurfaceFormatKHR				_surface_format			= {};
	VkSwapchainKHR					_swapchain				= VK_NULL_HANDLE;
	std::vector<VkImage>			_swapchain_images;
	VkExtent2D						_swapchain_extent;
	std::vector<VkImageView>		_image_views;

	FWindow& 						_window;
};

#endif /* ENGINE_RENDERER_FSIMPLERENDERER_H_ */
